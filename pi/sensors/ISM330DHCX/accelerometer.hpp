#ifndef ISM330DHCX_ACCELEROMETER_HPP
#define ISM330DHCX_ACCELEROMETER_HPP

#include "../../communication/i2c_dev.hpp"
#include "../interfaces/sensor_interface.hpp"
#include "ISM330DHCX.hpp"

class Accelerometer: public SensorInterface {
public:
  Accelerometer();
  Accelerometer(int fd);
  Accelerometer(int fd, int location);
  ~Accelerometer();
  
  void reset() override;
  std::vector<double> read() override;

private:
  static const int DATA_REGISTER = 0x28;
  static const int READ_LENGTH = 0x06;
  
  int adr;
  int fd;
};

#endif
