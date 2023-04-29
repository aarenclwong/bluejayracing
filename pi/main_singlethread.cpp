#include <chrono>
#include "sensors/ISM330DHCX/imu.hpp"
#include "sensors/ADS1115/adc.hpp"
#include "sensors/MTK3339/gps.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <stdlib.h>


using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::string;
using std::to_string;
using std::exception;



// TODO: Added definition for BUS_NAME as place holder

string outvec(vector<double> v) {
  string out = "";
  for (int i = 0; i < (int)v.size()-1; i++) {
    out += to_string(v[i]) + ",";
  }

  if (v.size() > 0) out += to_string(v[v.size()-1]);
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
    temp.open(file + to_string(iter));
    for(int i = 0; i < log_num; i++) {
      vector<double> r = func();
      temp << outvec(r);
    }
    temp.close();
  }
}

void front() {
  auto begin = std::chrono::high_resolution_clock::now();
  int fd2 = open("/dev/i2c-6", O_RDWR);
  if (fd2 < 0) {
    cerr << "Failed to open i2c bus 6" << endl;
    return;
  }
  
  ADC a2 = ADC(fd2, 0, false);
  ADC a3 = ADC(fd2, 1, false);
  ADC a4 = ADC(fd2, 2, true);
  ADC a5 = ADC(fd2, 3, true);

  const static int log_num = 860*60*5;
  const static string file = "vtech_front_";
  int iter = 0;
  while(1) {
    std::ofstream temp;
    temp.open(file + to_string(iter));
    for(int i = 0; i < log_num; i++) {
      
      auto log = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff = log - begin;
      try {
        temp << diff.count() << "," << outvec(a2.read()) << ",";
        temp << outvec(a3.read()) << ","<< outvec(a4.read()) << ",";
        temp << outvec(a5.read()) << "\n";
      } catch (exception &e) {
        try{
          a2.reset();
          a3.reset();
          a4.reset();
          a5.reset();
        } catch (exception &e) {

        }
        temp << diff.count() << "x,x,x,x" << endl;
      }
    }
    temp.close();
  }
  
}

void imu() {
  //auto begin = std::chrono::high_resolution_clock::now();
  const int pi = pigpio_start(NULL, NULL);
  if (pi < 0) {
    cout << "bad daemon" << endl;
    return;
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
    return;
  }

  Imu I = Imu(spi_d(pi, spi_handle));
}

void center() {
  //auto begin = std::chrono::high_resolution_clock::now();
  int fd1 = open("/dev/i2c-1", O_RDWR);
  if (fd1 < 0) {
    cerr << "Failed to open i2c bus 1" << endl;
    return;
  }
  ADC a0 = ADC(fd1, 0, true);
  ADC a1 = ADC(fd1, 1, true);

}

void gps() {
  
  gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
  GPS gps = GPS();

}




int main(/*int argc, char* argv[]*/) {
  auto begin = std::chrono::high_resolution_clock::now();

  const int pi = pigpio_start(NULL, NULL);
  if (pi < 0) {
    cout << "bad daemon" << endl;
    return -1;
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
    return -1;
  }

  gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);

  int fd1 = open("/dev/i2c-1", O_RDWR);
  if (fd1 < 0) {
    cerr << "Failed to open i2c bus 1" << endl;
    return -1;
  }

  int fd2 = open("/dev/i2c-6", O_RDWR);
  if (fd2 < 0) {
    cerr << "Failed to open i2c bus 6" << endl;
    return -1;
  }
  
  /*
  Imu I;
  ADC a0, a1, a2, a3, a4, a5;
  GPS gps;
  
  try {Imu I = Imu(spi_d(pi, spi_handle));}
  catch(exception &e) {}
  
  try {ADC a0 = ADC(fd1, 0, true);} 
  catch(exception &e) {}
  
  try {ADC a1 = ADC(fd1, 1, true);} 
  catch(exception &e) {}
  
  try {ADC a2 = ADC(fd2, 0, false);} 
  catch(exception &e) {}
  
  try {ADC a3 = ADC(fd2, 1, false);} 
  catch(exception &e) {}
  
  try {ADC a4 = ADC(fd2, 2, true);} 
  catch(exception &e) {}
  
  try {ADC a5 = ADC(fd2, 3, true);} 
  catch(exception &e) {}
  
  try {GPS gps = GPS();} 
  catch(exception &e) {}
  */
  Imu I = Imu(spi_d(pi, spi_handle));
  ADC a0 = ADC(fd1, 0, true);
  ADC a1 = ADC(fd1, 1, true);
  ADC a2 = ADC(fd2, 0, false);
  ADC a3 = ADC(fd2, 1, false);
  ADC a4 = ADC(fd2, 2, true);
  ADC a5 = ADC(fd2, 3, true);
  GPS gps = GPS();
  
  
  const static int log_num = (860*60*5);
  const static string file = "vtech_script_";
  int iter = 0;
  while(1) {
    std::ofstream temp;
    temp.open(file + to_string(iter++));
    for(int i = 0; i < log_num; i++) {
      
      auto end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff = end - begin;
      temp << diff.count() << ",";
      
      try {
        temp << outvec(I.read()) << ",";
      } catch(exception &e) {
        temp << outvec(vector<double>(0,7)) << ",";
      }
      //cout << "imu" << endl;
      /*
      try {
        a0.read();
        temp << outvec(a0.read()) << ",";
      } catch(exception &e) {
        temp << outvec(vector<double>(0,1)) << ",";
      }
      
      try {
        temp << outvec(a1.read()) << ",";
      } catch(exception &e) {
        cout << e.what();
        temp << outvec(vector<double>(0,1)) << ",";
      }
  
      try {
        temp << outvec(a2.read()) << ",";
      } catch(exception &e) {
        temp << outvec(vector<double>(0,1)) << ",";
      }
  
      try {
        temp << outvec(a3.read()) << ",";
      } catch(exception &e) {
        temp << outvec(vector<double>(0,1)) << ",";
      }

  
      try {
        temp << outvec(a4.read()) << ",";
      } catch(exception &e) {
        temp << outvec(vector<double>(0,1)) << ",";
      }
  
      try {
        temp << outvec(a5.read()) << ",";
      } catch(exception &e) {
        temp << outvec(vector<double>(0,1)) << ",";
      }
      */
      try {
        temp << outvec(gps.read()) << endl;
      } catch(exception &e) {
        temp << outvec(vector<double>(0,3)) << endl;
      }
      
    }
    temp.close();
  }

  
  
  //std::cout << "Time to poll"  << " ints : " << diff.count() << " s\n";

  //poll(860, vector<SensorInterface*>({&a0}));

  // close(fd2);
  // close(fd1);

  // spi_close(pi, spi_handle);

  // pigpio_stop(pi);

  
  // temp.close();
  return 0;
}