#include <iostream>
#include <bitset>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

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

int i2c_write(uint8_t slave_addr, uint8_t reg, uint8_t data) {
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
        perror("ioctl(I2C_RDWR) in i2c_write");
        //return -1;
        //exit(-1);
        //throw I2CException("i2c write error");
    }
    
    return 0;
}

std::vector<uint8_t> i2c_bulk_read(uint8_t slave_addr, uint8_t reg, int len) {
  uint8_t outbuf[1];
  uint8_t inbuf[len];
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
    cout << "ioctl" << endl; 
    perror("ioctl(I2C_RDWR) in i2c_read");
    cout << errno << endl;
    //throw I2CException("i2c bulk read error");
  }
  std::vector<uint8_t> ret;
  for (uint8_t i = 0; i<len; i++) {
    ret.push_back(inbuf[i]);
  }
  return ret;
}
