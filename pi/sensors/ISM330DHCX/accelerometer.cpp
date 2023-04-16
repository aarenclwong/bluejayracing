#include "accelerometer.hpp"
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

Accelerometer::Accelerometer(): adr{ISM330DHCX_ADDRESS}, fd{-1} {
  reset();
}

Accelerometer::Accelerometer(int fd): adr{ISM330DHCX_ADDRESS}, fd{fd} {
  reset();
}

Accelerometer::Accelerometer(int fd, int location): adr{ISM330DHCX_ADDRESS}, fd{fd} {
  adr = (location == 0 ? adr : ISM330DHCX_ADDRESS2);
  reset();
}

Accelerometer::~Accelerometer() {
}

void Accelerometer::reset() {
  i2c_write(fd, adr, 0x10, std::stoi("10100000", nullptr, 2));
  return;
}

vector<double> Accelerometer::read() {
  vector<double> data = vector<double>();
  
  vector<uint8_t> buf = i2c_bulk_read(fd, adr, this->DATA_REGISTER, this->READ_LENGTH);

  data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[1]) << 8 | static_cast<uint16_t>(buf[0]))*.000061);
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[3]) << 8 | static_cast<uint16_t>(buf[2]))*.000061);
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[5]) << 8 | static_cast<uint16_t>(buf[4]))*.000061);
  return data;
}



