#include "../sensors/ISM330DHC/accelerometer.hpp"
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

  Accelerometer a = Accelerometer(fd);

  vector<double> data = a.read();

  cout << data[0] << ", " << data[1] << ", " << data[2] << endl;

  close(fd);
  return 0;
}