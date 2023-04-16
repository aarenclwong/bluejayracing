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
  ADC(int fd, int location, bool single_channel);
  ~ADC();
  
  
  std::vector<double> read();
  void swap_mux();
  void reset();
  
private:
  ADCConstantContainer const_configs;
  int fd;
  int adr;
  int current_mux;
  Adafruit_ADS1115 ads;
};

#endif