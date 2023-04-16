#include "adc.hpp"
#include <iostream>

using std::vector;
using std::uint8_t;
using std::uint16_t;
using std::int16_t;
using std::cout;
using std::cerr;
using std::endl;
using std::exception;

/*'
Store the address, MUX_SINGLE, and MUX_DIFF of each location. This data is
constant, so I can store it somewhere. It should be interfaceble such that
it has all three fields. 
*/ 



ADC::ADC(): const_configs{0}, fd{-1}, ads{} {
  current_mux = const_configs.diff_mux;
  adr = const_configs.address;
  
  ads = Adafruit_ADS1115(fd, adr);
  ads.startADCReading(current_mux, true);
  reset();
}

// Differential ADC at just address 1
ADC::ADC(int fd): const_configs{0}, fd{fd}, ads{} {
  current_mux = const_configs.diff_mux;
  adr = const_configs.address;
  
  ads = Adafruit_ADS1115(fd, adr);
  ads.startADCReading(current_mux, true);
  reset();
}

// Single comparison ADC, where location is address of ADC
ADC::ADC(int fd, int location): const_configs{location}, ads{} {
  current_mux = const_configs.single_mux;
  adr = const_configs.address;
  
  ads = Adafruit_ADS1115(fd, adr);
  ads.startADCReading(const_configs.single_mux, true);
  reset();
}

ADC::ADC(int fd, int location, bool single_channel): const_configs{location}, ads{} {
  adr = const_configs.address;
  if (single_channel) {
    current_mux = const_configs.single_mux;
  } else {
    current_mux = const_configs.diff_mux;
  }
  
  ads = Adafruit_ADS1115(fd, adr);
  ads.startADCReading(current_mux, true);
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

  try {
    int16_t r = ads.getLastConversionResults();
    data.push_back(r);
    //data.push_back(ads.computeVolts(r));

    
  } catch(exception& e) {
    cerr << e.what() << endl;
  }
  return data;
}


void ADC::swap_mux() {
  if (current_mux == const_configs.diff_mux) {
    current_mux = const_configs.single_mux;
  } else {
    current_mux = const_configs.diff_mux;
  }
  
  ads.startADCReading(current_mux, true);
}
