#include "../ui/lcd2004/lcd.hpp"
#include "../sensors/ADS1115/adc.hpp"
#include <iostream>
#include <vector>

using std::vector;
using std::string;
using std::cerr;
using std::cout;
using std::endl;
using std::to_string;

string outvec(vector<double> v) {
  string out = "";
  for (int i = 0; i < (int)v.size()-1; i++) {
    out += to_string(v[i]) + ",";
  }

  if (v.size() > 0) out += to_string(v[v.size()-1]);
  return out;
}

int main(/*int argc, char* argv[]*/) {
  int fd_adc = open("/dev/i2c-6", O_RDWR);
  if (fd_adc < 0) cerr << "failed to open file for adc" << endl;
  ADC a = ADC(fd_adc, 3, true);
  
  int fd = open("/dev/i2c-4", O_RDWR);
  if (fd < 0) {
    cerr <<"Failed to open i2c bus (%c) ";
  }
  
  LCD l = LCD(fd);

  for(int i=0;i<10000000;i++){

    string s = to_string(a.read()[0]/17500*10);
    // print
    s+="inches";
    cout << s << endl;
    l.write(0,0,vector<char>(s.begin(),s.end()));
    usleep(1000.0*(1.0/860.0));

  }
  close(fd_adc);
  close(fd);
  return 0;
}
