#ifndef I2C_DEV_HPP
#define I2C_DEV_HPP

#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <iostream>



/* Some Example i2c usage code
--READS--------
  uint8_t* read = NULL;
  i2c_read(fd, accel_adr, DEVICE_ID_0_REG, read);
  if (*read != DEVICE_ID_0_VAL) {
    cerr << "Device ID 0 does not match specification." << endl;
    exit(1);
  }
  i2c_read(fd, accel_adr, DEVICE_ID_1_REG, read);
  if (*read != DEVICE_ID_1_VAL) {
    cerr << "Device ID 1 does not match specification." << endl;
    exit(1);
  }
  i2c_read(fd, accel_adr, PART_ID_REG, read);
  if (*read != ADXL313_PART_ID_VAL) {
    cerr << "Part ID does not match specification." << endl;
    exit(1);
  }


--WRITES---------
  //standby mode
  i2c_write(fd, adr, 0x2D, 0x0000);
  //soft reset
  i2c_write(fd, adr, 0x18, 0x52);
  
  // Set device configuration
  // +-2g resolution
  i2c_write(fd, adr, DATA_FORMAT_REG, stoi("00000010", nullptr, 2));
  // 400hz data rate - needs 800khz com rate which is under 1mhz rated i2c
  //i2c_write(fd, adr, DATA_RATE_REG, stoi("00001100", nullptr, 2));
  // 200hz data rate - needs 800khz com rate which is under 1mhz rated i2c
  i2c_write(fd, adr, DATA_RATE_REG, stoi("00001011", nullptr, 2));
  // set fifo to stream
  i2c_write(fd, _adr, FIFO_CTR_REG, stoi("10000000", nullptr, 2));
  
  //measure mode
  i2c_write(accel_adr, 0x2D, 0x0008);

*/




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
    perror("ioctl(I2C_RDWR) in i2c_write");
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
    perror("ioctl(I2C_RDWR) in i2c_read");
  }
  result = &inbuf[0];
  return 0;
}


std::vector<uint8_t> i2c_bulk_read(int fd, uint8_t slave_addr, uint8_t reg, int len) {
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
    perror("ioctl(I2C_RDWR) in i2c_read");
  }
  std::vector<uint8_t> ret;
  for (uint8_t i = 0; i<len; i++) {
    ret.push_back(inbuf[i]);
  }
  return ret;
}