#include "imu.hpp"
#include <iostream>
#include <cstdint>

using std::vector;
using std::cout;
using std::endl;
using std::uint8_t;
using std::uint16_t;
using std::int16_t;

Imu::Imu(): sd{spi_d()} {
  reset();
}

Imu::Imu(spi_d sd): sd{sd} {
  reset();
}


Imu::~Imu() {
}

void Imu::reset() {
  spi_write(sd, 0x10, std::stoi("10100000", nullptr, 2));
  spi_write(sd, 0x11, std::stoi("10100010", nullptr, 2));
  return;
}


vector<double> Imu::read() {
  vector<double> data = vector<double>();
  
  vector<uint8_t> buf = spi_bulk_read(sd, this->DATA_REGISTER, this->READ_LENGTH);

  data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[1]) << 8 | static_cast<uint16_t>(buf[0]))*.000061);
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[3]) << 8 | static_cast<uint16_t>(buf[2]))*.000061);
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[5]) << 8 | static_cast<uint16_t>(buf[4]))*.000061);
  data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[7]) << 8 | static_cast<uint16_t>(buf[6]))*.000061);
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[9]) << 8 | static_cast<uint16_t>(buf[8]))*.000061);
	data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[11]) << 8 | static_cast<uint16_t>(buf[10]))*.000061);
  data.push_back(static_cast<int16_t>(static_cast<uint16_t>(buf[13]) << 8 | static_cast<uint16_t>(buf[12]))*.000061);
  return data;
}



