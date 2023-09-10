#include "../sensors/ADS1115/adc.hpp"
#include <iostream>
#include <ios>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <chrono>


using std::cout;
using std::endl;
using std::vector;
using std::to_string;
using std::remove;
using std::rename;

using std::chrono::duration_cast;


// TODO: Added definition for BUS_NAME as place holder
char BUS_NAME = '6';

int main(/*int argc, char* argv[]*/) {

  std::ofstream temp;
  temp.open("torque_cal.txt");
  temp << std::fixed << std::showpoint << std::setprecision(2);

  
  int fd = open("/dev/i2c-6", O_RDWR);
  if (fd < 0) {
    char err[200];
    sprintf(err, "Failed to open i2c bus (%c) ", BUS_NAME);
  }


  ADC a = ADC(fd, 0, false);

  
  auto begin = std::chrono::high_resolution_clock::now();


  //ADC a = ADC(fd, 2, true);

  // ADC a = ADC(fd, 0, false);
  //ADC a = ADC(fd, 3, true);





  
  for (int i = 0; i < 51600; i++) {

    auto log = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = log - begin;

    vector<double> data = a.read();
    // temp << data[0] << endl;
    temp << diff.count() << "," << data[0] << endl;
    cout << diff.count() << "," << data[0] << endl;

    usleep(1000.0*(1.0/860.0));
    
  }

  close(fd);
  return 0;
}
