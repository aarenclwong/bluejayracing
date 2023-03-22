#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <bitset>
#include <unistd.h>
#include <fcntl.h>
#include <array>
#include <vector>
#include <deque>
#include <exception>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::bitset;
using std::stoi;
using std::array;
using std::deque;
using std::vector;
using std::exception;


int fd = 0;

int i2c_read(uint8_t slave_addr, uint8_t reg, uint8_t* &result) {
  uint8_t outbuf[1], inbuf[1];
  struct i2c_msg msgs[2];
  struct i2c_rdwr_ioctl_data msgset[1];
  msgs[0].addr = slave_addr;
  msgs[0].flags = 0;
  msgs[0].len = 1;
  msgs[0].buf = outbuf;
  msgs[1].addr = slave_addr;
  msgs[1].flags = I2C_M_RD | I2C_M_NOSTART;
  msgs[1].len = 1;
  msgs[1].buf = inbuf;
  msgset[0].msgs = msgs;
  msgset[0].nmsgs = 2;
  outbuf[0] = reg;
  inbuf[0] = 0;
  if (ioctl(fd, I2C_RDWR, &msgset) < 0) {
    cout << "ioctl" << endl; 
    perror("ioctl(I2C_RDWR) in i2c_read");
    //throw I2CException("i2c read error");
  }
  result = &inbuf[0];
  return 0;
}


int main() {
  return 0;
}
