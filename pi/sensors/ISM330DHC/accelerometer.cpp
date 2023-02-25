#include "accelerometer.hpp"

using std::vector;


Accelerometer::Accelerometer():fd{-1}, adr{ISM330DHC_ADDRESS} {
  reset();
}

Accelerometer::Accelerometer(int fd): adr{ISM330DHC_ADDRESS} {
  reset();
}

Accelerometer::Accelerometer(int fd, location) {
  adr = (location == 0 ? ISM330DHC_ADDRESS : ISM330DHC_ADDRESS2);
  reset();
}

Accelerometer::~Accelerometer() {
}






void Accelerometer::reset() {
  /* TODO */
  //enable ?
  i2c_write(fd, adr, 0x10, stoi("10100000", nullptr, 2));
  return;
}

vector<double> Accelerometer::read() {
  /* TODO */
  vector<double> data = vector<double>();

  vector<uint8_t> buf = i2c_bulk_read(accel_adr, 0x28, 6);


  data[0] = static_cast<int16_t>(static_cast<uint16_t>(buf[1]) << 8 | static_cast<uint16_t>(buf[0]));
	data[1] = static_cast<int16_t>(static_cast<uint16_t>(buf[3]) << 8 | static_cast<uint16_t>(buf[2]));
	data[2] = static_cast<int16_t>(static_cast<uint16_t>(buf[5]) << 8 | static_cast<uint16_t>(buf[4]));
  return data;
}



