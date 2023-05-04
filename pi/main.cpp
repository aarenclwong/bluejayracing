#include <chrono>
#include "sensors/ISM330DHCX/imu.hpp"
#include "sensors/ADS1115/adc.hpp"
#include "sensors/MTK3339/gps.hpp"
#include "ui/lcd2004/lcd.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <stdlib.h>
#include <iomanip>

const int LOG_LENGTH = 860*60*5;

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

void front_worker() {
  cout << "Front worker has started." << endl;
  
  auto begin = std::chrono::high_resolution_clock::now();
  int fd6 = open("/dev/i2c-6", O_RDWR);
  if (fd6 < 0) {
    cerr << "Failed to open i2c bus 6" << endl;
    return;
  }
  
  // Single Analog
  //ADC a2 = ADC(fd6, 0, false);
  //ADC a3 = ADC(fd6, 1, false);

  // Differential Analog - Reluctance
  ADC a4 = ADC(fd6, 2, true);
  ADC a5 = ADC(fd6, 3, true);
  
  const static string file_prefix = "front_";
  int iter = 0;

  while(1) {
    std::ofstream temp;
    string file_name = file_prefix;
    if (iter > 99) {
      file_name += to_string(iter);
    } else if(iter > 9) {
      file_name += "0" + to_string(iter);
    } else {
      file_name += "00" + to_string(iter);
    }
    temp.open(file_name);

    temp << std::fixed << std::showpoint << std::setprecision(6);
    for (int i = 0; i < LOG_LENGTH; i++) {      
      auto log = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff = log - begin;
      try {
        temp << diff.count() << "," << outvec(a2.read()) << ",";
        temp << outvec(a3.read()) << ","<< outvec(a4.read()) << ",";
        temp << outvec(a5.read()) << "\n";
      } catch (exception &e) {
        try{
          //a2.reset();
          //a3.reset();
          a4.reset();
          a5.reset();
        } catch (exception &e) {

        }
        temp << diff.count() << "x,x,x,x" << endl;
      }
      std::this_thread::sleep_until(log+std::chrono::duration<double, std::millis>((1000.0/860.0)));

    }
    temp.close();
    iter++;
  }
  fd6.close();
}

void imu_worker() {
  cout << "Imu worker has started." << endl;
  
  // THE CODE BELOW LIKELY WORKS. COMMENTING OUT TO TEST THREADING
  
  const int pi = pigpio_start(NULL, NULL);
  if (pi < 0) {
    cout << "bad daemon" << endl;
    return;
  }
  // Open a SPI device with a frequency of 1 MHz
  const int spi_channel = 0;
  const int spi_frequency = 5000000; // 1 MHz
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

void center_worker() {
  cout << "Center worker has started." << endl;
  
  //auto begin = std::chrono::high_resolution_clock::now();
  int fd1 = open("/dev/i2c-1", O_RDWR);
  if (fd1 < 0) {
    cerr << "Failed to open i2c bus 1" << endl;
    return;
  }
  ADC a0 = ADC(fd1, 0, true);
  
  
}

void gps_worker() {
  cout << "GPS worker has started." << endl;
  
  // Commenting out to test threading
  // gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
  // GPS gps = GPS();

}

int main(/*int argc, char* argv[]*/) {
  fd4 = open("/dev/i2c-4", O_RDWR);

  LCD lcd = LCD(fd4);



  thread gps(gps_worker);
  thread front(front_worker);
  thread center(center_worker);
  thread imu(imu_worker);
  
  // Indefinite blocking. Workers will be runing in infinite loops
  gps.join();
  front.join();
  center.join();
  imu.join();
  return 0;
}