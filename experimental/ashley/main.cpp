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

  uint8_t adr = 0x1c; // address of chip 

  uint8_t* read = NULL; // buffer to store read stuff into
  i2c_read(fd, adr, 0x0F, read);
  cout << *read << endl;

  i2c_write(fd, adr, 0x20, stoi("10000010", nullptr, 2)); // temp sensor: 1000hz, no self test
  i2c_write(fd, adr, 0x21, stoi("00000000", nullptr, 2)); // control register 2, set to +/- 4 gauss
  i2c_write(fd, adr, 0x22, stoi("00000000", nullptr, 2)); // enable reads

  i2c_read(fd, adr, 0x28, read); // read
  cout << (uint8_t)(*read) << endl;

  uint8_t* x_h;
  uint8_t* x_l;

  i2c_read(fd, adr, 0x28, x_h); // x-axis data output as 2's complement
  i2c_read(fd, adr, 0x29, x_l); // x-axis data output as 2's complement

  cout << static_cast<int16_t>(static_cast<uint16_t>(*x_h) << 8 | static_cast<uint16_t>(*x_l)) << endl;

  close(fd);
  return 0;
}
