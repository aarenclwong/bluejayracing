#include "../sensors/ADS1115/adc.hpp"
#include <iostream>
#include <ios>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::vector;
using std::to_string;
using std::remove;
using std::rename;



// TODO: Added definition for BUS_NAME as place holder
char BUS_NAME = '2';

int main(/*int argc, char* argv[]*/) {

  std::ofstream temp;
  temp.open("torque_test.txt");
  temp << std::fixed << std::showpoint << std::setprecision(6);

  
  int fd = open("/dev/i2c-6", O_RDWR);
  if (fd < 0) {
    char err[200];
    sprintf(err, "Failed to open i2c bus (%c) ", BUS_NAME);
  }

  //ADC a = ADC(fd, 2, true);
  // ADC a = ADC(fd, 0, false);

  //ADC a = ADC(fd, 1, false);

  //torque
  ADC a = ADC(fd, 3, false);
  
  for (int i = 0; i < 100000000; i++) {
    vector<double> data = a.read();
    // temp << data[0] << endl;
    temp << data[0] << endl;
    //cout << data[0] << endl;
    usleep(1000.0*(1.0/860.0));
    //usleep(200000);
  }
  
  // temp.close();

  close(fd);
  return 0;
}
