#include "adc.hpp"
#include <iostream>

using std::vector;
using std::uint8_t;
using std::uint16_t;
using std::int16_t;
using std::cout;
using std::endl;


ADC::ADC():adr{ADS1115_ADDRESS1}, fd{-1}, mux{ADS1X15_REG_CONFIG_MUX_SINGLE_0}, ads{} {
  ads = Adafruit_ADS1115(fd, adr);
  ads.startADCReading(mux, true);
  reset();
}

ADC::ADC(int fd): adr{ADS1115_ADDRESS1}, fd{fd}, mux{ADS1X15_REG_CONFIG_MUX_SINGLE_0}, ads{} {
  ads = Adafruit_ADS1115(fd, adr);
  ads.startADCReading(mux, true);
  reset();
}

ADC::ADC(int fd, int location): adr{0x00}, fd{fd}, mux{ADS1X15_REG_CONFIG_MUX_SINGLE_0}, ads{} {
  adr = (location == 0 ? ADS1115_ADDRESS1 : adr);
  adr = (location == 1 ? ADS1115_ADDRESS2 : adr);
  adr = (location == 2 ? ADS1115_ADDRESS3 : adr);
  adr = (location == 3 ? ADS1115_ADDRESS4 : adr);
  ads = Adafruit_ADS1115(fd, adr);
  ads.startADCReading(mux, true);
  reset();
}

ADC::~ADC() {
  ads.~Adafruit_ADS1115();
}




void ADC::reset() {
  
  return;
}

vector<double> ADC::read() {
  vector<double> data = vector<double>();

  //int16_t r = ads.readADC_SingleEnded(mux);
  int16_t r = ads.getLastConversionResults();
  data.push_back(ads.computeVolts(r));

  return data;
}


void ADC::swap(int channel) {
  ads.startADCReading(channel, true);
  mux = channel;
}
