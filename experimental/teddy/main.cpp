#include "./i2c_dev.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::vector;
using std::stoi;


int main(/*int argc, char* argv[]*/) {

  int fd = open("/dev/i2c-6", O_RDWR);
  if (fd < 0) {
    char err[200];
    return 1;
  }

  int adr = 0x1C; //the address of the chip
  uint8_t* read = NULL; //buffer to store read stuff into

  //register 0x0F is the WHO_AM_I register
  i2c_read(fd, adr, 0x0F, read);
  cout << *read << endl;

  //0x22 is the register address for Control Register 3
  i2c_write(fd, adr, 0x22, stoi("00000000", nullptr, 2));

  //Control Register 2, set to +/- 4 gauss
  i2c_write(fd, adr, 0x21, stoi("00000000", nullptr, 2));

  //Control Register 1 +/- 1000 hZ
  i2c_write(fd, adr, 0x20, stoi("10000010", nullptr, 2));

  //just a read
  i2c_read(fd, adr, 0x28, read);
  cout << (uint8_t)(*read) << endl;

  uint8_t* x_h;
  uint8_t* x_l;
  i2c_read(fd, adr, 0x28, x_l); //X-axis data output as 2's comlement
  i2c_read(fd, adr, 0x29, x_h); //X-axis data output as 2's comlement

  cout << static_cast<int16_t>(static_cast<uint16_t>(*x_h) << 8 | static_cast<uint16_t>(*x_l)) << endl;
  
  close(fd);
  return 0;
}