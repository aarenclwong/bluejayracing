#include "../sensors/ADS1115/adc.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::vector;



// TODO: Added definition for BUS_NAME as place holder
char BUS_NAME = '2';

int main(/*int argc, char* argv[]*/) {
  
  int fd = open("/dev/i2c-1", O_RDWR);
  if (fd < 0) {
    char err[200];
    sprintf(err, "Failed to open i2c bus (%c) ", BUS_NAME);
  }

  ADC a = ADC(fd);
  for (int i = 0; i < 860; i++) {
    vector<double> data = a.read();
    cout << data[0] << endl;
    a.swap(0);
  }
  

  close(fd);
  return 0;
}