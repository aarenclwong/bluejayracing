# Wrapping class for GPS

import datetime
import time
import board
import busio
import serial
import adafruit_gps

class GPS:
    def __init__(self):
        # pyserial library for uart access
        self.uart = serial.Serial("/dev/ttyS0", baudrate=9600, timeout=50)

        # create GPS module instance
        self.gps = adafruit_gps.GPS(self.uart, debug=False)

        # Turn on the basic GGA and RMC info (what you typically want)
        self.gps.send_command(b"PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0")

        # Set update rate to once a second (5hz), the upper limit for the Adafruit Ultimate GPS module
        self.gps.send_command(b"PMTK220,200")

    
    def update(self):
        self.gps.update()

    def get_lat(self):
        if not self.gps.has_fix:
            return "x"
        return "{0:.6f}".format(self.gps.latitude)

    def get_long(self):
        if not self.gps.has_fix:
            return "x"
        return "{0:.6f}".format(self.gps.longtitude)

    def get_knots(self):
        if not self.gps.has_fix:
            return "x"
        return "{}".format(self.gps.speed_knots)
    
