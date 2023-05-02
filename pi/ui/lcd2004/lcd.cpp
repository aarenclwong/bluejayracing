#include "lcd.hpp"
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::uint8_t;
using std::uint16_t;
using std::int16_t;
using std::cout;
using std::cerr;
using std::endl;
using std::exception;


LCD::LCD(): fd{-1} {;}

LCD::LCD(int fd): fd{fd} {
	reset();
	// std::string welcomestring = "Bluejay Racing";
	// for (int i = 0; i < (int)welcomestring.size(); i++){
	// 	send_data(welcomestring[i]);
	// 	if (i < 7){
	// 		usleep(250000);
	// 	}
	// }
	// usleep(5000000);
	// reset();
}

LCD::~LCD() {;}

void LCD::reset() {
  send_command(0x33);	// Must initialize to 8-line mode at first
	usleep(5000);
	send_command(0x32);	// Then initialize to 4-line mode
	usleep(5000);
	send_command(0x28);	// 2 Lines & 5*7 dots
	usleep(5000);
	send_command(0x08);	// 4 
	usleep(5000);
	send_command(0x0C);	// Enable display without cursor
	usleep(5000);
	send_command(0x01);	// Clear Screen
	i2c_write_adr(fd, adr, 0x08);
}

void LCD::write_word(int data) {
	int temp = data;
	if ( BLEN == 1 )
		temp |= 0x08;
	else
		temp &= 0xF7;
	i2c_write_adr(fd, adr, temp);
}

void LCD::send_command(int comm) {
	int buf;
	// Send bit7-4 firstly
	buf = comm & 0xF0;
	buf |= 0x04;			// RS = 0, RW = 0, EN = 1
	write_word(buf);
	usleep(2000);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (comm & 0x0F) << 4;
	buf |= 0x04;			// RS = 0, RW = 0, EN = 1
	write_word(buf);
	usleep(2000);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
}

void LCD::send_data(int data){
	int buf;
	// Send bit7-4 firstly
	buf = data & 0xF0;
	buf |= 0x05;			// RS = 1, RW = 0, EN = 1
	write_word(buf);
	usleep(2000);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
	//usleep(2);

	// Send bit3-0 secondly
	buf = (data & 0x0F) << 4;
	buf |= 0x05;			// RS = 1, RW = 0, EN = 1
	write_word(buf);
	usleep(2000);
	buf &= 0xFB;			// Make EN = 0
	write_word(buf);
}

void LCD::clear() {
  send_command(0x01);
}

void LCD::write(int x, int y, vector<char> data){
	if (x < 0)  x = 0;
	if (x > 15) x = 15;
	if (y < 0)  y = 0;
	if (y > 1)  y = 1;

	// Move cursor
	int reg = 0x80 + 0x40 * y + x;
	send_command(reg);
	
	for (int i = 0; i < (int)data.size(); i++){
		send_data(data[i]);
	}
}
