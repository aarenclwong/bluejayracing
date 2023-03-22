#include "gyro.hpp"

using std::vector;


Gyro::Gyro(): adr{ISM330DHCX_ADDRESS}, fd{-1} {
  reset();
}

Gyro::Gyro(int fd): adr{ISM330DHCX_ADDRESS}, fd{fd} {
  reset();
}

Gyro::Gyro(int fd, int location): adr{ISM330DHCX_ADDRESS}, fd{fd} {
  adr = (location == 0 ? ISM330DHCX_ADDRESS : ISM330DHCX_ADDRESS2);
  reset();
}

Gyro::~Gyro() {
}

void Gyro::reset() {
  /* TODO */


  // Inform chip to start collecting data
  i2c_write(fd, adr, 0x11, std::stoi("11110010", nullptr, 2));
  return;
}

vector<double> Gyro::read() {
  /* TODO */
  vector<double> data = vector<double>();
  
  vector<uint8_t> buf = i2c_bulk_read(fd, adr, this->DATA_REGISTER, this->READ_LENGTH);

  data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[1]) << 8 | static_cast<uint16_t>(buf[0]))*.000061);
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[3]) << 8 | static_cast<uint16_t>(buf[2]))*.000061);
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[5]) << 8 | static_cast<uint16_t>(buf[4]))*.000061);
  return data;
}