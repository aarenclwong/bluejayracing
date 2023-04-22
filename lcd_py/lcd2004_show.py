#!/usr/bin/env python3
import LCD2004
import time

def setup():
	LCD2004.init(0x27, 1)	# init(slave address, background light)
	LCD2004.write(0, 0, 'Bluejay Racing')
	LCD2004.write(0, 1, 'IIC/I2C LCD2004')
	LCD2004.write(0, 2, '20 cols, 4 rows')
	LCD2004.write(0, 3, 'www.sunfounder.com')
	time.sleep(2)

def destroy():
	LCD2004.clear()

if __name__ == "__main__":
	try:
		setup()
	except KeyboardInterrupt:
		destroy()
