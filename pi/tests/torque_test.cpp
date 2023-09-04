#include "../sensors/ADS1115/adc.hpp"
#include <iostream>
#include <ios>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <array>

using std::cout;
using std::endl;
using std::vector;
using std::to_string;
using std::remove;
using std::rename;
using std::array;



// TODO: Added definition for BUS_NAME as place holder
char BUS_NAME = '2';

int main(/*int argc, char* argv[]*/) {

  std::ofstream perm;
  perm.open("torque_cal.txt");
  perm << std::fixed << std::showpoint << std::setprecision(6);

  
  int fd = open("/dev/i2c-6", O_RDWR);
  if (fd < 0) {
    char err[200];
    sprintf(err, "Failed to open i2c bus (%c) ", BUS_NAME);
  }

  //ADC a = ADC(fd, 2, true);
  // ADC a = ADC(fd, 0, false);

  //ADC a = ADC(fd, 1, false);

  //torque
  ADC a = ADC(fd, 0, false);
  
  for (int i = 0; i < 100000000; i++) {
    std::ofstream temp;
    temp.open("pkg.txt");
    temp << std::fixed << std::showpoint << std::setprecision(1);
    temp << to_string(i++) << endl;

    array<double, 3> data;
    for (int j = 0; j < 2*860; j++) {
      vector<double> data = a.read();
      temp << data[0] << endl;

      //  perm << to_string(i++) << ", " << data[0] << endl;
      usleep(1000.0*(1.0/860.0));
    }
    temp.close();
    remove("cal_pkg.txt");
    rename("pkg.txt", "cal_pkg.txt");


  }

  close(fd);
  return 0;
}
