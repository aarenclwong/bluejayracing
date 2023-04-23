#ifndef LCD_HPP
#define LCD_HPP


#include "lcd2004.hpp"
#include "../../communication/i2c_dev.hpp"
#include <string>
#include <vector>

class LCD {
public:
  LCD();
  LCD(int fd);
  ~LCD();

  void write(int x, int y, std::vector<char> data);
  void reset();
  
private:
  int fd;
  const static int adr = 0x27;
  const static int BLEN = 1;

  void write_word(int data);
  void send_data(int data);
  void send_command(int comm);

  void clear();


  void write_character(int line, int pos, char content);
  void write_line(int line, std::string content);
  

};

#endif