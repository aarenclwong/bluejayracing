#include "i2c_dev.hpp"
#include <iostream>

using std::uint8_t;
using std::vector;

int i2c_write_adr(int fd, uint8_t slave_addr, uint8_t data) {
  uint8_t outbuf[1];

  struct i2c_msg msgs[1];
  struct i2c_rdwr_ioctl_data msgset[1];

  outbuf[0] = data;

  msgs[0].addr = slave_addr;
  msgs[0].flags = 0;
  msgs[0].len = 1;
  msgs[0].buf = outbuf;

  msgset[0].msgs = msgs;
  msgset[0].nmsgs = 1;

  if (ioctl(fd, I2C_RDWR, &msgset) < 0) {
    //perror("ioctl(I2C_RDWR) in i2c_write");
  }
    
  return 0;
}

int i2c_write(int fd, uint8_t slave_addr, uint8_t reg, uint8_t data) {
  uint8_t outbuf[2];

  struct i2c_msg msgs[1];
  struct i2c_rdwr_ioctl_data msgset[1];

  outbuf[0] = reg;
  outbuf[1] = data;

  msgs[0].addr = slave_addr;
  msgs[0].flags = 0;
  msgs[0].len = 2;
  msgs[0].buf = outbuf;

  msgset[0].msgs = msgs;
  msgset[0].nmsgs = 1;

  if (ioctl(fd, I2C_RDWR, &msgset) < 0) {
    //perror("ioctl(I2C_RDWR) in i2c_write");
  }
    
  return 0;
}

int i2c_read(int fd, uint8_t slave_addr, uint8_t reg, uint8_t* &result) {
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
    //perror("ioctl(I2C_RDWR) in i2c_read");
  }
  result = &inbuf[0];
  return 0;
}


vector<uint8_t> i2c_bulk_read(int fd, uint8_t slave_addr, uint8_t reg, int len) {
  uint8_t outbuf[1];
  // uint8_t inbuf[len];
  uint8_t *inbuf = (uint8_t*)calloc(len, sizeof(uint8_t));
  struct i2c_msg msgs[2];
  struct i2c_rdwr_ioctl_data msgset[1];
  msgs[0].addr = slave_addr;
  msgs[0].flags = 0;
  msgs[0].len = 1;
  msgs[0].buf = outbuf;
  msgs[1].addr = slave_addr;
  msgs[1].flags = I2C_M_RD | I2C_M_NOSTART;//author recommends removing nostart
  msgs[1].len = len;
  msgs[1].buf = inbuf;
  msgset[0].msgs = msgs;
  msgset[0].nmsgs = 2;
  outbuf[0] = reg;
  if (ioctl(fd, I2C_RDWR, &msgset) < 0) {
    free(inbuf);
    //perror("ioctl(I2C_RDWR) in i2c_bulk_read");
    return vector<uint8_t>({});
  }
  std::vector<uint8_t> ret;
  for (uint8_t i = 0; i<len; i++) {
    ret.push_back(inbuf[i]);
  }
  free(inbuf);
  return ret;
}

int i2c_bulk_write(int fd, uint8_t slave_addr, uint8_t reg, vector<uint8_t> data, int len) {
  // uint8_t outbuf[len+1];
  uint8_t *outbuf = (uint8_t*)calloc(len+1, sizeof(uint8_t));
  outbuf[0] = reg;
  for (int i = 0; i < len; i++) {
    outbuf[i+1] = data[i];
  }
  
  struct i2c_msg msgs[1];
  struct i2c_rdwr_ioctl_data msgset[1];
  msgs[0].addr = slave_addr;
  msgs[0].flags = 0;
  msgs[0].len = len+1;
  msgs[0].buf = outbuf;

  msgset[0].msgs = msgs;
  msgset[0].nmsgs = 1;
  

  if (ioctl(fd, I2C_RDWR, &msgset) < 0) {
    free(outbuf);
    //perror("ioctl(I2C_RDWR) in i2c_bulk_write");
    return -1;
  }
  free(outbuf);
  return 0;
}