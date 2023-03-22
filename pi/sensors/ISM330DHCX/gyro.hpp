#ifndef ISM330DHCX_GYRO_HPP
#define ISM330DHCX_GYRO_HPP

#include "../../communication/i2c_dev.hpp"
#include "../interfaces/sensor_interface.hpp"
#include "ISM330DHCX.hpp"

class Gyro: public SensorInterface {
public:
  Gyro();
  Gyro(int fd);
  Gyro(int fd, int location);
  ~Gyro();
  
  void reset() override;
  std::vector<double> read();
  
private:
  static const int DATA_REGISTER = 0x22;
  static const int READ_LENGTH = 0x06;
  
  int adr;
  int fd;
};

#endif