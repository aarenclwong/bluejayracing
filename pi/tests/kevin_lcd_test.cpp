#include "../ui/lcd2004/lcd.hpp"
#include <iostream>
#include <vector>
#include <unistd.h>
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

  int fd = open("/dev/i2c-4", O_RDWR);
  if (fd < 0) {
    cerr <<"Failed to open i2c bus (%c) ";
  }
  
  LCD l = LCD(fd); //instantiate LCD object

  
  string s1 = "bluejay racing";
  string s2 = "hi there";
  
  for(int i = 0; i < 100; i++){

    s2 = std::to_string(i);

    l.write(0, 0, vector<char>(s1.begin(), s1.end())); //vector = very smart list
	  l.write(1, 1, vector<char>(s2.begin(), s2.end()));
    sleep(1);
  }
  // row, column
  


  close(fd);
  return 0;
}