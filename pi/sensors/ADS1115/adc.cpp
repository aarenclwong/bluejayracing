#include "adc.hpp"

using std::vector;


ADC::ADC():adr{ADS1115_ADDRESS1}, fd{-1} {
  reset();
}

ADC::ADC(int fd): adr{ADS1115_ADDRESS1}, fd{fd} {
  reset();
}

ADC::ADC(int fd, int location): adr{0x00}, fd{fd} {
  adr = (location == 0 ? ADS1115_ADDRESS1 : adr);
  adr = (location == 1 ? ADS1115_ADDRESS2 : adr);
  adr = (location == 2 ? ADS1115_ADDRESS3 : adr);
  adr = (location == 3 ? ADS1115_ADDRESS4 : adr);
  reset();
}

ADC::~ADC() {
}






void ADC::reset() {
  /* TODO */
  //enable ?

  i2c_write(fd, adr, 0x01, std::stoi("10000100", nullptr, 2));
  i2c_write(fd, adr, 0x02, std::stoi("10000011", nullptr, 2));
  return;
}

vector<double> ADC::read() {
  /* TODO */
  vector<double> data = vector<double>();

  vector<uint8_t> buf = i2c_bulk_read(fd, adr, 0x28, 6);


  data[0] = static_cast<int16_t>(static_cast<uint16_t>(buf[1]) << 8 | static_cast<uint16_t>(buf[0]));
	data[1] = static_cast<int16_t>(static_cast<uint16_t>(buf[3]) << 8 | static_cast<uint16_t>(buf[2]));
	data[2] = static_cast<int16_t>(static_cast<uint16_t>(buf[5]) << 8 | static_cast<uint16_t>(buf[4]));
  return data;
}



