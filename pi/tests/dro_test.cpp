#include "../sensors/ADS1115/adc.hpp"
#include <iostream>
#include <ios>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include "../ui/lcd2004/lcd.hpp"
#include <vector>

using std::cout;
using std::endl;
using std::vector;
using std::to_string;
using std::remove;
using std::rename;
using std::string;

char BUS_NAME = '2';

int main(/*int argc, char* argv[]*/) {

  int fd = open("/dev/i2c-6", O_RDWR);
  int fd_lcd = open("/dev/i2c-4", O_RDWR);
  if (fd < 0) {
    char err[200];
    sprintf(err, "Failed to open i2c bus (%c) ", BUS_NAME);
  }


  ADC a = ADC(fd, 3, true);
  
  LCD l = LCD(fd_lcd);

  for (int i = 0; i < 100000000; i++) {
     string s = to_string(a.read()[0] / 17500);
    // print
    cout << s << endl;
    l.write(0,0,vector<char>(s.begin(),s.end()));
    usleep(1000.0*(1.0/860.0));
    //usleep(200000);
  }
  
  // temp.close();

  close(fd);
  return 0;
  // 17000
}
