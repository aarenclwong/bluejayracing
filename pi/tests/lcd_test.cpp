#include "../ui/lcd2004/lcd.hpp"
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

  int fd = open("/dev/i2c-1", O_RDWR);
  if (fd < 0) {
    cerr <<"Failed to open i2c bus (%c) ";
  }
  
  LCD l = LCD(fd);

  string s1 = "Bluejay Racing";
  string s2 = "hello";

  l.write(0, 0, vector<char>(s1.begin(), s1.end()));
	l.write(0, 1, vector<char>(s1.begin(), s1.end()));

  close(fd);
  return 0;
}