#ifndef ISM330DHCX_ACCELEROMETER_HPP
#define ISM330DHCX_ACCELEROMETER_HPP

#include "../../communication/spi_pigpio.hpp"
#include "../../communication/spi_d.hpp"
#include "../interfaces/sensor_interface.hpp"
#include "ISM330DHCX.hpp"

class Imu: public SensorInterface {
public:
  Imu();
  Imu(spi_d sd);
  ~Imu();
  
  void reset() override;
  std::vector<double> read() override;

private:
  static const int DATA_REGISTER = 0x20;
  static const int READ_LENGTH = 14;
  
  spi_d sd;
};

#endif
