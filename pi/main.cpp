#include <chrono>
#include "sensors/ISM330DHCX/imu.hpp"
#include "sensors/ADS1115/adc.hpp"
#include "sensors/MTK3339/gps.hpp"
#include "ui/lcd2004/lcd.hpp"
#include "concurrency/realtime.hpp"
#include <iostream>
#include <cstdio>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <stdlib.h>
#include <iomanip>

const double ADC_RATE = 860.0;
const int ADC_LOG_LENGTH = ADC_RATE*60*5;

const double IMU_RATE = 2000.0;
const int IMU_LOG_LENGTH = IMU_RATE*60*5;


using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::string;
using std::to_string;
using std::exception;
using std::thread;
using std::ofstream;

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

void fn_open(ofstream& f, string name, int num) {
  string file_name = name + "_";
  if (num > 99) {
    file_name += to_string(num);
  } else if(num > 9) {
    file_name += "0" + to_string(num);
  } else {
    file_name += "00" + to_string(num);
  }
  f.open(file_name);
  f << std::fixed << std::showpoint << std::setprecision(6);
}







void front_worker(string file_prefix,std::chrono::high_resolution_clock::time_point begin) {
  cout << "Front worker has started." << endl;
  
  int fd6 = open("/dev/i2c-6", O_RDWR);
  if (fd6 < 0) {
    cerr << "Failed to open i2c bus 6" << endl;
    return;
  }
  
  Realtime::setup();

  //Steering
  ADC a3 = ADC(fd6, 1, false);

  // Differential Analog - Reluctance
  ADC a4 = ADC(fd6, 2, true);
  ADC a5 = ADC(fd6, 3, true);
  
  int iter = 0;

  while(1) {
    ofstream temp;
    fn_open(temp, file_prefix, iter);

    auto iter_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ADC_LOG_LENGTH; i++) {      
      auto log = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff = log - begin;
      try {
        temp << diff.count() << "," ;
        temp << outvec(a3.read()) << ",";
        temp << outvec(a4.read()) << ",";
        temp << outvec(a5.read()) << "\n";
      } catch (exception &e) {
        try{
          //a2.reset();
          a3.reset();
          a4.reset();
          a5.reset();
        } catch (exception &e) {

        }
        temp << diff.count() << ",x,x,x" << endl;
      }
      std::this_thread::sleep_until(iter_start + i * std::chrono::duration<double, std::milli>((1000.0/ADC_RATE)));

    }
    temp.close();
    iter++;
  }
  close(fd6);
}

void imu_worker(string file_prefix, std::chrono::high_resolution_clock::time_point begin) {
  cout << "Imu worker has started." << endl;
  
  const int pi = pigpio_start(NULL, NULL);
  if (pi < 0) {
    cout << "bad daemon" << endl;
    return;
  }
  // Open a SPI device with a frequency of 1 MHz
  const int spi_channel = 0;
  const int spi_frequency = 5000000; // 1 MHz
  const int spi_handle = spi_open(pi, spi_channel, spi_frequency, 0);

  if (spi_handle < 0){
    cerr << "Failed to open SPI device ";
    cerr << spi_handle << endl;
    spi_close(pi, spi_handle);
    pigpio_stop(pi);
    return;
  }

  // Realtime::setup();

  Imu I = Imu(spi_d(pi, spi_handle));

  int iter = 0;

  while(1) {
    ofstream temp;
    fn_open(temp, file_prefix, iter);

    auto iter_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < IMU_LOG_LENGTH; i++) {      
      auto log = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff = log - begin;
      try {
        temp << diff.count() << "," << outvec(I.read()) << "\n";
      } catch (exception &e) {
        try{
          I.reset();
        } catch (exception &e) {

        }
        temp << diff.count() << ",x,x,x,x,x,x,x" << endl;
      }
      std::this_thread::sleep_until(iter_start + i * std::chrono::duration<double, std::milli>((1000.0/IMU_RATE)));

    }
    temp.close();
    iter++;
  }
  spi_close(pi, spi_handle);
  pigpio_stop(pi);
}

void center_worker(string file_prefix, std::chrono::high_resolution_clock::time_point begin) {
  cout << "Center worker has started." << endl;
  
  int fd1 = open("/dev/i2c-1", O_RDWR);
  if (fd1 < 0) {
    cerr << "Failed to open i2c bus 1" << endl;
    return;
  }

  // Realtime::setup();


  ADC a2 = ADC(fd1, 2, true);

  int iter = 0;

  while(1) {
    ofstream temp;
    fn_open(temp, file_prefix, iter);

    temp << std::fixed << std::showpoint << std::setprecision(6);
    auto iter_start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ADC_LOG_LENGTH; i++) {      
      auto log = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff = log - begin;
      try {
        temp << diff.count() << "," ;
        temp << outvec(a2.read()) << "\n";
      } catch (exception &e) {
        try{
          a2.reset();
        } catch (exception &e) {

        }
        temp << diff.count() << ",x" << endl;
      }
      std::this_thread::sleep_until(iter_start + i * std::chrono::duration<double, std::milli>((1000.0/ADC_RATE)));

    }
    temp.close();
    iter++;
  }
  close(fd1);
}

void gps_worker(string file_prefix, std::chrono::high_resolution_clock::time_point begin) {
  cout << "GPS worker has started." << endl;
  
  // Commenting out to test threading
  gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
  GPS gps = GPS();

  int iter = 0;

  while(1) {
    ofstream temp;
    fn_open(temp, file_prefix, iter);
    temp << std::setprecision(9);

    temp << std::fixed << std::showpoint << std::setprecision(6);
    auto iter_start = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> iter_diff = std::chrono::duration<double, std::milli>(0);
    while(iter_diff.count() < 300) {
      cout << iter_diff.count() << endl;
      auto log = std::chrono::high_resolution_clock::now();
      iter_diff = log - iter_start;
      std::chrono::duration<double> diff = log - begin;
      try {
        vector<double> r = gps.read();
        temp << diff.count() << "," ;
        temp << outvec(r) << "\n";
      } catch (exception &e) {
        try{
          gps.reset();
        } catch (exception &e) {

        }
        temp << diff.count() << ",x,x,x" << endl;
      }
    }
    temp.close();
    iter++;
  }

}

int main(/*int argc, char* argv[]*/) {

  std::ios_base::sync_with_stdio(false);

  string comp = "OSH";
  int log = 0;
  string gps_file = comp + "_gps_"+to_string(log);
  string front_file = comp + "_front_"+to_string(log);
  string center_file = comp + "_center_"+to_string(log);
  string imu_file = comp + "_imu_"+to_string(log);

  // Synchronized epoch
  auto begin = std::chrono::high_resolution_clock::now();

  // Start up all the threads
  thread gps(gps_worker, gps_file , begin);
  thread front(front_worker, front_file, begin);
  thread center(center_worker, center_file, begin);
  thread imu(imu_worker, imu_file, begin);



  int fd4 = open("/dev/i2c-4", O_RDWR);
  if (fd4 < 0) {
    cerr << "Failed to open i2c bus 4" << endl;
    return -1;
  }

  LCD lcd = LCD(fd4);
  
  // Indefinite blocking. Workers will be runing in infinite loops
  gps.join();
  front.join();
  center.join();
  imu.join();
  return 0;
}
