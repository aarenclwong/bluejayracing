//	latency.cc - test timing latency on Raspberry Pi
/*
	Copyright 2018 by Tom Roberts. All rights reserved.
	This code may be redistributed in accordance with the 
	Gnu Public License: https://www.gnu.org/licenses/gpl-3.0.en.html
*/
/*
	Prints histograms of various latencies, once a minute.
	This is very specific to the Raspberry Pi.

	Delay latency:
	Mesurements are made for random delays 1-1100 microseconds; the
	latency is the actual delay minus the requested delay. Note that
	Realtime::delay() calls usleep() for delays >= 100us, so those
	are tallied separately from short delays.

	gettimeofday() latency:
	The latency is just how long the call took.

	empty latency:
	This uses the same method to measure latency as the others, but
	the code being measured is empty. So this shows the latency
	introduced by scheduling other tasks via interrupts. In another
	sense, this shows how long it takes to call Realtime::micros().

	GPIO latency:
	GPIO_OUT and GPIO_IN must be electrically connected together.
	The thread() function is run as a separate thread on another core;
	it generates rising edges at known times so the main thread can
	determine the latency of waiting for the rising edge.

	Latencies greater than NHIST are tallied in the last bin (999).

	All timing measurements use Realtime::micros(), which simply
	reads the CPU hardware's 32-bit counter (increments at 1 MHz).
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>

#include <pigpio.h>

#include "Realtime.h"

const int GPIO_OUT=22;	// pin 15
const int GPIO_IN=23;	// pin 16
const int NHIST=1000;	// histogram size for latency histogram

// thread control variables
static volatile bool running=false;	// indicates thread is running
static volatile uint32_t edgeTime=0;	// value of micros() at rising edge
					// set to 0 if invalid edge
static volatile bool ready=false;	// flag indicating main thread is ready
					// set by main thread, read by thread()

// This thread generates rising edges on GPIO_OUT at known times,
// synchronized to the main thread waiting for the edge on GPIO_IN.
// If the edge's time is not known to within 2us, it is considered invalid.
// Note: the value of the GPIO is used as a mutex between the threads,
// controling access to the shared variable edgeTime.
void* thread(void *unused)
{
	// move this thread to core 2, realtime
	Realtime::cpu2();
	Realtime::realTimeSched();
	running = true;

	// infinite loop
	for(;;) {
		gpioWrite(GPIO_OUT,0);
		// wait until main thread is ready
		if(!ready) {
			Realtime::delay(100); // long enough so it calls usleep
			continue;
		}
		// wait to be sure the main thread is actually ready
		Realtime::delay(100);   // longer than any usual latency
		// output the edge, checking how long the function took
		uint32_t a=Realtime::micros();
		gpioWrite(GPIO_OUT,1);
		uint32_t b=Realtime::micros();
		if(b-a <= 2) {
			edgeTime = a; // function took <= 2us -- OK
		} else {
			edgeTime = 0; // function took too long -- invalid
		}
		// wait until the main thread has caught the edge
		while(ready)
			Realtime::delay(100); // long enough so it calls usleep
	}
}

int main(int argc, char *argv[])
{
	// initialization
	gpioInitialise();
	gpioSetMode(GPIO_IN,PI_INPUT);
	gpioSetMode(GPIO_OUT,PI_OUTPUT);
	gpioWrite(GPIO_OUT,0);
	Realtime::setup();

	// start thread()
	ready = false;
	gpioStartThread(thread,0);
	while(!running)
		Realtime::delay(1000);

	// (first call is slow, so do it here, unmeasured)
	struct timeval tv;
	gettimeofday(&tv,0);

	// test whether GPIO_IN and GPIO_OUT are connected
	bool connected=true;
	for(int i=0; i<5; ++i) {
		gpioWrite(GPIO_OUT,0);
		Realtime::delay(2);
		if(gpioRead(GPIO_IN) != 0) connected = false;
		Realtime::delay(2);
		gpioWrite(GPIO_OUT,1);
		Realtime::delay(2);
		if(gpioRead(GPIO_IN) == 0) connected = false;
		Realtime::delay(2);
	}
	if(!connected)
		printf("**** GPIO %d and GPIO %d are not connected --"
					" no GPIO latency\n",GPIO_IN,GPIO_OUT);

	// histogram variables
	uint64_t shortHist[NHIST], longHist[NHIST], gtodHist[NHIST],
					emptyHist[NHIST], gpioHist[NHIST];
	for(int i=0; i<NHIST; ++i) 
		shortHist[i] = longHist[i] = gtodHist[i] = emptyHist[i] =
								gpioHist[i] = 0;
	int shortMax=0, longMax=0, gtodMax=0, emptyMax=0, gpioMax=0;
	uint64_t samples=0;
	int invalid=0;

	// loop making measurements for 60 seconds. ^C to exit.
	// (limited to 24 hours to avoid overflows in hisogram entries)
	for(int minutes=1; minutes<24*60; ++minutes) {
		sleep(1); // let things settle for 1 sec
		uint32_t start = Realtime::micros();
		while(Realtime::micros()-start < 60000000) {
			++samples;

			// short delay (<50us)
			int delay = random() % 50;
			if(delay == 0) delay = 1;
			uint32_t begin = Realtime::micros();
			Realtime::delay(delay);
			uint32_t end = Realtime::micros();
			uint32_t latency = end - begin - delay;
			if(latency >= NHIST) latency = NHIST-1;
			if(latency > shortMax) shortMax = latency;
			++shortHist[latency];

			// long delay (100us - 1100us)
			delay = random() % 1000 + 100;
			begin = Realtime::micros();
			Realtime::delay(delay);
			end = Realtime::micros();
			latency = end - begin - delay;
			if(latency >= NHIST) latency = NHIST-1;
			if(latency > longMax) longMax = latency;
			++longHist[latency];

			// gettimeofday()
			begin = Realtime::micros();
			gettimeofday(&tv,0);
			end = Realtime::micros();
			latency = end - begin;
			if(latency >= NHIST) latency = NHIST-1;
			if(latency > gtodMax) gtodMax = latency;
			++gtodHist[latency];

			// empty
			begin = Realtime::micros();
			end = Realtime::micros();
			latency = end - begin;
			if(latency >= NHIST) latency = NHIST-1;
			if(latency > emptyMax) emptyMax = latency;
			++emptyHist[latency];

			// GPIO edge 
			if(!connected) continue;
			ready = true;
			uint32_t now = Realtime::micros();
			while(gpioRead(GPIO_IN) == 0 &&
					Realtime::micros()-now < 1000)
				;
			now = Realtime::micros();
			ready = false;
			while(gpioRead(GPIO_IN) != 0 &&
					Realtime::micros()-now < 1000)
				;
			if(edgeTime != 0) {
				uint32_t latency = now - edgeTime; // <0 => huge
				if(latency >= NHIST) latency = NHIST-1;
				if(latency > gpioMax) gpioMax = latency;
				++gpioHist[latency];
			} else {
				++invalid;
			}
		}
		printf("Histograms after %d minutes, %llu samples\n",
						minutes,samples);
		printf("Short delay (< 50us)");
		for(int i=0; i<=shortMax; ++i) {
			if(i%10 == 0) printf("\n%3dus: ",i);
			printf(" %6llu",shortHist[i]);
		}
		printf("\n");
		printf("Long delay (> 100us)");
		for(int i=0; i<=longMax; ++i) {
			if(i%10 == 0) printf("\n%3dus: ",i);
			printf(" %6llu",longHist[i]);
		}
		printf("\n");
		printf("gettimeofday()");
		for(int i=0; i<=gtodMax; ++i) {
			if(i%10 == 0) printf("\n%3dus: ",i);
			printf(" %6llu",gtodHist[i]);
		}
		printf("\n");
		printf("empty");
		for(int i=0; i<=emptyMax; ++i) {
			if(i%10 == 0) printf("\n%3dus: ",i);
			printf(" %6llu",emptyHist[i]);
		}
		printf("\n");
		if(connected) {
			printf("GPIO edge,   %d invalid edges",invalid);
			for(int i=0; i<=gpioMax; ++i) {
				if(i%10 == 0) printf("\n%3dus: ",i);
				printf(" %6llu",gpioHist[i]);
			}
			printf("\n");
		}
		printf("\n");
		fflush(stdout);
	}

	gpioTerminate();
	return 0;
}

