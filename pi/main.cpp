#include <chrono>
#include "sensors/ISM330DHCX/imu.hpp"
#include "sensors/ADS1115/adc.hpp"
#include "sensors/MTK3339/gps.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <thread>


using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::string;



// TODO: Added definition for BUS_NAME as place holder

string outvec(vector<double v) {
  string out = "";
  for (int i = 0; i < (int)v.size()-1; i++) {
    out += (string)v[i] << ",";
  }
  out += (string)v[v.size()] +"\n";
  return out;
}

void printvec(vector<double> v) {
  for (int i = 0; i < (int)v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
  return;
}

/*
void poll(int freq, vector<SensorInterface*> si) {
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    auto s = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
    std::chrono::system_clock::time_point next_full_second = std::chrono::system_clock::time_point(++s);

    auto interval = std::chrono::seconds(1); // or milliseconds(500) or whatever
    auto wait_until = next_full_second;

    while (1)
    {
        this_thread::sleep_until(wait_until);
        cout << (std::chrono::system_clock::now()-s).count() << endl;

        // do something
        for (int i = 0; i < (int)si.size(); i++) {
          printvec((*(si[i])).read());
        }

        wait_until += interval;
    }
}
*/
void poll(string file, int log_num, vector<double> (*func)(void) ) {
  int iter = 0;
  while(1) {
    std::ofstream temp;
    temp.open(file + (string)iter);
    for(int i = 0; i < log_num; i++) {
      temp << outvec(func());
    }
    temp.close();
  }
}

void front() {
  auto begin = std::chrono::high_resolution_clock::now();
  int fd2 = open("/dev/i2c-6", O_RDWR);
  if (fd2 < 0) {
    cerr << "Failed to open i2c bus 6" << endl;
    return -1;
  }
  ADC a2 = ADC(fd2, 0, false);
  ADC a3 = ADC(fd2, 1, false);
  ADC a4 = ADC(fd2, 2, true);
  ADC a5 = ADC(fd2, 3, true);

}

void imu() {
  auto begin = std::chrono::high_resolution_clock::now();
  const int pi = pigpio_start(NULL, NULL);
  if (pi < 0) {
    cout << "bad daemon" << endl;
    return 1;
  }
  // Open a SPI device with a frequency of 1 MHz
  const int spi_channel = 0;
  const int spi_frequency = 1000000; // 1 MHz
  // const int spi_handle = spiOpen(spi_channel, spi_frequency, 0);
  const int spi_handle = spi_open(pi, spi_channel, spi_frequency, 0);

  if (spi_handle < 0){
    std::cout << "Failed to open SPI device\n";
    cout << spi_handle << endl;
    spi_close(pi, spi_handle);
    pigpio_stop(pi);
    // gpioTerminate();
    return 1;
  }

  Imu I = Imu(spi_d(pi, spi_handle));
}

void center() {
  auto begin = std::chrono::high_resolution_clock::now();
  int fd1 = open("/dev/i2c-1", O_RDWR);
  if (fd1 < 0) {
    cerr << "Failed to open i2c bus 1" << endl;
    return -1;
  }
  ADC a0 = ADC(fd1, 0, true);
  ADC a1 = ADC(fd1, 1, true);

}

void gps() {
  auto begin = std::chrono::high_resolution_clock::now();
  gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
  GPS gps = GPS();

}


int main(/*int argc, char* argv[]*/) {

  

  


  


  



  


  

  
  


  


  

  printvec(I.read());
  printvec(a0.read());
  printvec(a1.read());


  printvec(a2.read());
  printvec(a3.read());
  printvec(a4.read());
  printvec(a5.read());

  printvec(gps.read());
  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> diff = end - begin;
  //std::cout << "Time to poll"  << " ints : " << diff.count() << " s\n";

  //poll(860, vector<SensorInterface*>({&a0}));

  close(fd2);
  close(fd1);

  spi_close(pi, spi_handle);

  pigpio_stop(pi);


  
  temp.close();
  return 0;
}