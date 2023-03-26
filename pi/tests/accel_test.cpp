#include "../sensors/ISM330DHCX/accelerometer.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

// TODO: Added definition for BUS_NAME as place holder
int BUS_NAME = 0x0;


int main(/*int argc, char* argv[]*/) {
  int fd = open("/dev/i2c-1", O_RDWR);
  if (fd < 0) {
    char err[200];
    sprintf(err, "Failed to open i2c bus (%c) ", BUS_NAME);
  }
  Accelerometer a = Accelerometer(fd, 1);

  vector<double> data = a.read();
  
  for (int i = 0; i < 100; i++) {
    vector<double> data = a.read();
    cout << data[0] << ", " << data[1] << ", " << data[2] << endl;
  }
  

  close(fd);
  return 0;
}