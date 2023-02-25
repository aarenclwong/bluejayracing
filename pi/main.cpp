#include "sensors/ISM330DHC/accelerometer.hpp"
#include "sensors/ISM330DHC/gyro.hpp"
#include "sensors/ADS1115/adc.hpp"
#include "sensors/MTK3339/gps.hpp"
#include <iostream>

using std::cout;
using std::endl;



int main(int argc, char* argv[]) {

  fd = open("/dev/i2c-2", O_RDWR);
  if (fd < 0) {
    char err[200];
    sprintf(err, "Failed to open i2c bus (%s) ", BUS_NAME);
  }

  Accelerometer accel = Accelerometer(fd);
  Gyro gyro = Gyro(fd);
  ADC adc = ADC(fd);
  GPS gps = GPS();

  accel.read();
  gyro.read();
  adc.read();
  gps.read();


  close(fd);
  return 0;
}