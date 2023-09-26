#include "../sensors/ISM330DHCX/imu.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <array>
#include <ios>

using std::cout;
using std::endl;
using std::vector;
using std::to_string;
using std::remove;
using std::rename;
//using std::ofstream;



void printvec(vector<double> v, std::ofstream& file) {
  for (int i = 0; i < (int)v.size(); i++) {
    file << v[i] << " ";
  }
  file << endl;
  return;
}


int main(/*int argc, char* argv[]*/) {

//   //make downloadable file
//   std::ofstream perm;
//   perm.open("rt_accel_pkg.txt");
//   //set downloadable file synatx
//   perm << std::fixed << std::showpoint << std::setprecision(6);

//   //open i2c bus for sensor reading
//   int fd = open("/dev/i2c-6", O_RDWR);
//   if (fd < 0) {
//     char err[200];
//     sprintf(err, "Failed to open i2c bus (%c) ", BUS_NAME);
//   }

  //Connect to pigpio daemon
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

  //create accelerometer object to read data
  Imu I = Imu(spi_d(pi, spi_handle));
  
  while(true) {

    //create writing file
    std::ofstream write;
    write.open("rt_imu_wr.txt");
    //set writing file syntax
    write << std::fixed << std::showpoint << std::setprecision(6);

    //read 10000 data point and write them to the writing file
    for (int i = 0; i < 10000; i++) {
      vector<double> data = I.read();

      printvec(data, write);

      // write << data[0] << ", " << data[1] << ", " << data[2] << endl;
    }
    //close the writing file
    write.close();
    //remove the old downloadable file
    remove("rt_imu_pkg.txt");
    //move the writing file to the downloadable file location
    rename("rt_imu_wr.txt", "rt_imu_pkg.txt");
     
  }

  // close(fd);
  return 0;
}