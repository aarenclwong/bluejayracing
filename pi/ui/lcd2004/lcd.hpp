#ifndef LCD_HPP
#define LCD_HPP


#include "LCD2004.hpp"
#include "../../communication/i2c_dev.hpp"
#include "../interfaces/sensor_interface.hpp"

class LCD {
public:
  LCD();
  LCD(int fd);
  LCD(int fd, int location);
  LCD(int fd, int location, bool single_channel);
  ~ADC();
  
  
  std::vector<double> write();
  void reset();
  
private:
  int fd;
  int adr;
};

#endif