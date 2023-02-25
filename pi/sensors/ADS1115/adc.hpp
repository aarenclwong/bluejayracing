#ifndef ADS1115_HPP
#define ADS1115_HPP

#include "../../communication/i2c_dev.hpp"
#include "../interfaces/sensor_interface.hpp"
#include "ADS1115.hpp"

class ADC: public SensorInterface {
public:
  ADC();
  ADC(int fd);
  ADC(int fd, int location);
  ~ADC();
private:
  int adr;
  int fd;
}

#endif