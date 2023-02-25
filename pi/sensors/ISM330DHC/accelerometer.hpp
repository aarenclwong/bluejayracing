#ifndef ISM330DHC_ACCELEROMETER_HPP
#define ISM330DHC_ACCELEROMETER_HPP

#include "../../communication/i2c_dev.hpp"
#include "../interfaces/sensor_interface.hpp"
#include "ISM330DHC.hpp"

class Accelerometer: public SensorInterface {
public:
  Accelerometer();
  Accelerometer(int fd);
  Accelerometer(int fd, int location);
  ~Accelerometer();
private:
  int adr;
  int fd;
}

#endif