#include "../ui/lcd2004/lcd.hpp"
#include <iostream>

using std::vector;



int main(/*int argc, char* argv[]*/) {
  int fd = open("/dev/i2c-1", O_RDWR);
  if (fd < 0) {
    char err[200];
    sprintf(err, "Failed to open i2c bus (%c) ", BUS_NAME);
  }
  
  LCD l - LCD(fd);
  l.write(0, 0, "Bluejay Racing");
	l.write(0, 1, "I2C LCD2004");

  close(fd);
  return 0;
}