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

  std::ofstream temp1;
  std::ofstream temp2;
  std::ofstream temp3;
  std::ofstream temp4;
  temp1.open("adc1.txt");
  temp2.open("adc2.txt");
  temp3.open("adc3.txt");
  temp4.open("adc4.txt");
  temp1 << std::fixed << std::showpoint << std::setprecision(6);
  temp2 << std::fixed << std::showpoint << std::setprecision(6);
  temp3 << std::fixed << std::showpoint << std::setprecision(6);
  temp4 << std::fixed << std::showpoint << std::setprecision(6);

  
  int fd = open("/dev/i2c-1", O_RDWR);
  if (fd < 0) {
    char err[200];
    sprintf(err, "Failed to open i2c bus (%c) ", BUS_NAME);
  }

  ADC adc_one = ADC(fd, 0, true);
  ADC adc_two = ADC(fd, 1, true);
  ADC adc_three = ADC(fd, 2, true);
  ADC adc_four = ADC(fd, 3, false);
  
  for (int i = 0; i < 86000; i++) {
    temp1 << adc_one.read()[0] << endl;
    temp2 << adc_two.read()[0] << endl;
    temp3 << adc_three.read()[0] << endl;
    temp4 << adc_four.read()[0] << endl;
    usleep(1);
  }
  
  temp1.close();
  temp2.close();
  temp3.close();
  temp4.close();
  
  close(fd);
  return 0;
}