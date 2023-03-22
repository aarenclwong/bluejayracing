//#include "../sensors/ISM330DHCX/accelerometer.hpp"
#include "../communication/spi_pigpio.hpp"
#include "../communication/spi_d.hpp"
#include <iostream>
// #include <pigpiod_if2.h>
#include <pigpio.h>
#include <bitset>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

using std::cout;
using std::endl;
using std::vector;
using std::bitset;

#define LOOPS 10000
#define SPEED 1000000
#define BYTES 3
char  spiMode = SPI_MODE_2;
char  spiBits  = 8;
char* spiBaud = "1000000";
char spiMSB = 0;


// int main(/*int argc, char* argv[]*/) {


//   int spi_handle = open("/dev/spidev0.0", O_RDWR);
//   if (spi_handle < 0) {
//     std::cerr <<"Failed to open spi bus 0.0" << endl;
//     return -1;
//   }

//   if (ioctl(spi_handle, SPI_IOC_WR_MODE, &spiMode) < 0) {
//     close(spi_handle);
//     return -2;
//   }

//   if (ioctl(spi_handle, SPI_IOC_WR_BITS_PER_WORD, &spiBits) < 0) {
//     close(spi_handle);
//     return -3;
//   }

//   if (ioctl(spi_handle, SPI_IOC_WR_MAX_SPEED_HZ, &spiBaud) < 0){
//     close(spi_handle);
//     return -4;
//   }

//   if (ioctl(spi_handle, SPI_IOC_WR_LSB_FIRST, &spiMSB) < 0){
//     close(spi_handle);
//     return -5;
//   }


//   uint8_t	inbuf[1];
//   // inbuf[1] = 0x00;
//   // write(spi_handle, &inbuf, 1);
//   // read(spi_handle,&inbuf, 1);
//   // cout << bitset<8>(inbuf[0]) << endl;
//   // spi_write(spi_handle, 0x10, std::stoi("11111000", nullptr, 2));

//   for (int i = 0; i < 1; i++) {
//     cout << bitset<8>(spi_read(spi_handle, 0x0F)).to_string() << endl;
//   }
//   close(spi_handle);

//   return 0;
// }


int main(/*int argc, char* argv[]*/) {
  int cfg = gpioCfgGetInternals();
  cfg |= PI_CFG_NOSIGHANDLER;  // (1<<10)
  gpioCfgSetInternals(cfg);


  // Initialize pigpio
  int status = gpioInitialise();
  if (status < 0) {
    std::cout << status << "pigpio initialization failed\n";
    return 1;
  }

  gpioSetPullUpDown(8, PI_PUD_OFF);


  //Connect to pigpio daemon
  // const int pi = pigpio_start(NULL, NULL);
  // if (pi < 0) {
  //   cout << "bad daemon" << endl;
  //   return 1;
  // }


  // Open a SPI device with a frequency of 1 MHz
  const int spi_channel = 0;
  const int spi_frequency = 1000000; // 1 MHz
  const int spi_handle = spiOpen(/*pi,*/ spi_channel, spi_frequency, 0);
  

  if (spi_handle < 0){
    std::cout << "Failed to open SPI device\n";
    cout << spi_handle << endl;
    // pigpio_stop(pi);
    gpioTerminate();
    return 1;
  }


  spi_write(/*spi_d(pi, spi_handle)*/spi_handle, 0x10, std::stoi("11111000", nullptr, 2));
  for (int i = 0; i < 10; i++) {
    cout << bitset<8>(spi_read(/*spi_d(pi, spi_handle)*/spi_handle, 0x0F)).to_string() << endl;
  }
  

  // Close the SPI device
  spiClose(/*pi,*/ spi_handle);
  gpioWrite(8, 0);

  // Close connection to daemon
  // pigpio_stop(pi);


  // Cleanup pigpio
  
  gpioTerminate();

  return 0;
}