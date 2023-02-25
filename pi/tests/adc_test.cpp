#include "../sensors/ADS1115/adc.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::array;
using std::vector;


int main(int argc, char* argv[]) {

  fd = open("/dev/i2c-2", O_RDWR);
  if (fd < 0) {
    char err[200];
    sprintf(err, "Failed to open i2c bus (%s) ", BUS_NAME);
  }

  ADC a = ADC(fd);

  vector<double> data = a.read();
  
  cout << data[0] endl;

  close(fd);
  return 0;
}