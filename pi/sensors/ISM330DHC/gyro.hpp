#ifndef ISM330DHC_GYRO_HPP
#define ISM330DHC_GYRO_HPP

#include "../../communication/i2c_dev.hpp"
#include "../interfaces/sensor_interface.hpp"

class Gyro: public SensorInterface {
public:
  Gyro();
  Gyro(int fd);
  Gyro(int fd, int location);
  ~Gyro();
private:
  int adr;
  int fd;
}

#endif