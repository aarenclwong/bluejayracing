#include "../sensors/ADS1115/adc.hpp"
#include <iostream>
#include <ios>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::to_string;
using std::remove;
using std::rename;
using std::string;




int main(/*int argc, char* argv[]*/) {
  std::ofstream temp;
  temp.open("temp.txt");
  temp << std::fixed << std::showpoint << std::setprecision(1);
  

  
  int fd = open("/dev/i2c-6", O_RDWR);
  if (fd < 0) {
    return -1;
  }

  std::cout << "Device opened" << endl;

  ADC a = ADC(fd, 0, false);

  std::cout << "ADC Initialized" << endl;
  for (int i = 0; true ; i++) {
    vector<double> data = a.read();
    temp << data[0] << endl;
    usleep(1000);
  }
  
  temp.close();

  close(fd);
  return 0;
}