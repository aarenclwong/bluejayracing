#ifndef I2C_DEV_HPP
#define I2C_DEV_HPP

#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <cstdint>



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


int i2c_write(int fd, std::uint8_t slave_addr, std::uint8_t reg, std::uint8_t data);

int i2c_read(int fd, std::uint8_t slave_addr, std::uint8_t reg, std::uint8_t* &result);

std::vector<std::uint8_t> i2c_bulk_read(int fd, std::uint8_t slave_addr, std::uint8_t reg, int len);

int i2c_bulk_write(int fd, std::uint8_t slave_addr, std::uint8_t reg, std::vector<std::uint8_t> data, int len);

#endif