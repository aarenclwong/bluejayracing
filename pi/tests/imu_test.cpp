#include <iostream>
#include "../sensors/ISM330DHCX/imu.hpp"


using std::cout;
using std::endl;
using std::vector;
using std::string;

void printvec(vector<double> v) {
  for (int i = 0; i < (int)v.size(); i++) {
    cout << v[i] << " ";
  }
  cout << endl;
  return;
}

int main(/*int argc, char* argv[]*/) {
  // int cfg = gpioCfgGetInternals();
  // cfg |= PI_CFG_NOSIGHANDLER;  // (1<<10)
  // gpioCfgSetInternals(cfg);


  //Connect to pigpio daemon
  const int pi = pigpio_start(NULL, NULL);
  if (pi < 0) {
    cout << "bad daemon" << endl;
    return 1;
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
    return 1;
  }

  Imu I = Imu(spi_d(pi, spi_handle));

  vector<double> data;
  for (int i = 0; i < 100000; i++) {
    printvec(I.read());
    //cout << I.read()[1] << endl;
  }

  cout << "read" << endl;



  // Close the SPI device
  // spiClose(spi_handle);
  spi_close(pi, spi_handle);

  // Close connection to daemon
  pigpio_stop(pi);



  return 0;
}