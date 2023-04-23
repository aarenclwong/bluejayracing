#ifndef LCD_HPP
#define LCD_HPP


#include "LCD2004.hpp"
#include "../../communication/i2c_dev.hpp"
#include "../interfaces/sensor_interface.hpp"
#include <string>

class LCD {
public:
  LCD();
  LCD(int fd);
  ~LCD();

  void write();
  void reset();
  
private:
  int fd;
  static int adr = 0x27;

  void write_word(int data);
  void send_data(int data);

  void clear();


  void write_character(int line, int pos, char content);
  void write_line(int line, std::string content);


};

#endif