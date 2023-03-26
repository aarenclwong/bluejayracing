#ifndef ADC_HPP
#define ADC_HPP

#include "adafruit_ads.hpp"
#include "../../communication/i2c_dev.hpp"
#include "../interfaces/sensor_interface.hpp"
#include "ADS1115.hpp"

class ADC: public SensorInterface {
public:
  ADC();
  ADC(int fd);
  ADC(int fd, int location);
  ~ADC();
  
  std::vector<double> read();
  void swap(int channel);
  void reset();
  
private:
  int adr;
  int fd;
  int mux;
  Adafruit_ADS1115 ads;
};

#endif