//#include "../sensors/ISM330DHCX/accelerometer.hpp"
#include "../communication/spi_pigpio.hpp"
#include "../communication/spi_d.hpp"
#include <iostream>
#include <pigpiod_if2.h>
// #include <pigpio.h>
#include <bitset>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string>
#include <algorithm>


using std::cout;
using std::endl;
using std::vector;
using std::bitset;
using std::uint8_t;
using std::uint16_t;
using std::int16_t;
using std::string;

// #define LOOPS 10000
// #define SPEED 1000000
// #define BYTES 3
// char  spiMode = SPI_MODE_2;
// char  spiBits  = 8;
// char* spiBaud = "1000000";
// char spiMSB = 0;


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


//   // spi_write(spi_handle, 0x10, std::stoi("11111000", nullptr, 2));

//   for (int i = 0; i < 1; i++) {
//     cout << bitset<8>(spi_read(spi_handle, 0x0F)).to_string() << endl;
//   }
//   close(spi_handle);

//   return 0;
// }

int16_t twos(uint16_t v) {
  uint16_t s = 0x8000;
  if ((v & s)==0) {
    return v;
  } else {
    return -(~v +1);
  }
}

int main(/*int argc, char* argv[]*/) {
  // int cfg = gpioCfgGetInternals();
  // cfg |= PI_CFG_NOSIGHANDLER;  // (1<<10)
  // gpioCfgSetInternals(cfg);


  // Initialize pigpio
  // int status = gpioInitialise();
  // if (status < 0) {
  //   std::cout << status << "pigpio initialization failed\n";
  //   return 1;
  // }

  // gpioSetPullUpDown(8, PI_PUD_OFF);
  // gpioWrite(7, 0);


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


  spi_write(spi_d(pi, spi_handle), 0x10, std::stoi("00010000", nullptr, 2));
  

  vector<double> data;
  // vector<uint8_t> buf;
  //   buf.push_back(spi_read(spi_d(pi, spi_handle), 0x28));
  //   buf.push_back(spi_read(spi_d(pi, spi_handle), 0x29));
  //   buf.push_back(spi_read(spi_d(pi, spi_handle), 0x2A));
  //   buf.push_back(spi_read(spi_d(pi, spi_handle), 0x2B));
  //   buf.push_back(spi_read(spi_d(pi, spi_handle), 0x2C));
  //   buf.push_back(spi_read(spi_d(pi, spi_handle), 0x2D));
  // vector<uint8_t> buf = spi_bulk_read(spi_d(pi, spi_handle), 0x28, 6);
  for (int i = 0; i < 100000; i++) {
    // vector<uint8_t> buf;
    // buf.push_back(spi_read(spi_d(pi, spi_handle), 0x28));
    // buf.push_back(spi_read(spi_d(pi, spi_handle), 0x29));
    // buf.push_back(spi_read(spi_d(pi, spi_handle), 0x2A));
    // buf.push_back(spi_read(spi_d(pi, spi_handle), 0x2B));
    // buf.push_back(spi_read(spi_d(pi, spi_handle), 0x2C));
    // buf.push_back(spi_read(spi_d(pi, spi_handle), 0x2D));
    vector<uint8_t> buf = spi_bulk_read(spi_d(pi, spi_handle), 0x28, 6);

    cout << static_cast<int16_t>(static_cast<uint16_t>(buf[1]) << 8 | static_cast<uint16_t>(buf[0]))*.000061 << ",";
    cout << static_cast<int16_t>(static_cast<uint16_t>(buf[3]) << 8 | static_cast<uint16_t>(buf[2]))*.000061 << ",";
    cout << static_cast<int16_t>(static_cast<uint16_t>(buf[5]) << 8 | static_cast<uint16_t>(buf[4]))*.000061 << endl;

    for (int i = 0; i < 6; i++) {
      string s = bitset<8>(buf[i]).to_string();
      std::reverse(s.begin(), s.end());
      buf[i] = bitset<8>(s).to_ulong();
    }

    // cout << (bitset<16>(buf[5]) << 8 | bitset<16>(buf[4])).to_string() << endl;
  }
  
  /*
  // cout << bitset<8>(buf[4]).to_string() << ", " << bitset<8>(buf[5]).to_string() << endl;

  data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[0]) << 8 | static_cast<uint16_t>(buf[1])));
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[2]) << 8 | static_cast<uint16_t>(buf[3])));
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[4]) << 8 | static_cast<uint16_t>(buf[5])));

  cout << (bitset<16>(buf[4]) << 8 | bitset<16>(buf[5])).to_string() << endl;

  data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[1]) << 8 | static_cast<uint16_t>(buf[0])));
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[3]) << 8 | static_cast<uint16_t>(buf[2])));
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[5]) << 8 | static_cast<uint16_t>(buf[4])));

  cout << (bitset<16>(buf[5]) << 8 | bitset<16>(buf[4])).to_string() << endl;


  for (int i = 0; i < 6; i++) {
    string s = bitset<8>(buf[i]).to_string();
    std::reverse(s.begin(), s.end());
    buf[i] = bitset<8>(s).to_ulong();

  }

  // cout << twos(static_cast<uint16_t>(buf[4]) << 8 | static_cast<uint16_t>(buf[5]))*.000061 << endl;

  data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[0]) << 8 | static_cast<uint16_t>(buf[1])));
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[2]) << 8 | static_cast<uint16_t>(buf[3])));
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[4]) << 8 | static_cast<uint16_t>(buf[5])));

  cout << (bitset<16>(buf[4]) << 8 | bitset<16>(buf[5])).to_string() << endl;

  data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[1]) << 8 | static_cast<uint16_t>(buf[0])));
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[3]) << 8 | static_cast<uint16_t>(buf[2])));
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[5]) << 8 | static_cast<uint16_t>(buf[4])));
  
  cout << (bitset<16>(buf[5]) << 8 | bitset<16>(buf[4])).to_string() << endl;
  
  // cout << bitset<8>(buf[1]).to_string() << ", " << bitset<8>(buf[0]).to_string() << endl;
  // cout << bitset<8>(buf[3]).to_string() << ", " << bitset<8>(buf[2]).to_string() << endl;

  // cout << bitset<8>(buf[4]).to_string() << ", " << bitset<8>(buf[5]).to_string() << endl;
  // cout << bitset<16>(bitset<16>(buf[4])<<8 | bitset<16>(buf[5])).to_string() << endl;
  // cout << (double)((int)bitset<16>(bitset<16>(buf[4])<<8 | bitset<16>(buf[5])).to_ulong())*.000061 << endl;

  

  // cout << data[0] << ", " << data[1] << ", " << data[2] << endl;
  cout << data[3] << ", " << data[4] << ", " << data[5] << endl;
  // cout << data[6] << ", " << data[7] << ", " << data[8] << endl;
  // cout << data[9] << ", " << data[10] << ", " << data[11] << endl;
  //*/
  

  // Close the SPI device
  // spiClose(spi_handle);
  spi_close(pi, spi_handle);

  // Close connection to daemon
  pigpio_stop(pi);


  // Cleanup pigpio
  
  // gpioTerminate();

  return 0;
}