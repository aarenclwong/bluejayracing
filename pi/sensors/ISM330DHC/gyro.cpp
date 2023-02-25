#include "gyro.hpp"

using std::vector;


Gyro::Gyro():fd{-1}, adr{ISM330DHC_ADDRESS} {
  reset();
}

Gyro::Gyro(int fd): adr{ISM330DHC_ADDRESS} {
  reset();
}

Gyro::Gyro(int fd, location) {
  adr = (location == 0 ? ISM330DHC_ADDRESS : ISM330DHC_ADDRESS2);
  reset();
}

Gyro::~Gyro() {
}






void Gyro::reset() {
  return;
  /* TODO */
}

vector<double> Gyro::read() {
  return vector<double>();
  /* TODO */
}