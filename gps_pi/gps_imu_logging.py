import sys, os
import argparse
import datetime
import time
import csv
sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
sys.path.append(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..\imu'))


from imu import IMU
from imu import *
from gps_pi import GPS

#import board
#import busio
#import serial
#import adafruit_gps

# setting up the command line arguments
parser = argparse.ArgumentParser()
parser.add_argument('--mxo', type=float, default=0, help='Hard iron offset for mx')
parser.add_argument('--myo', type=float, default=0, help='Hard iron offset for my')
parser.add_argument('--mzo', type=float, default=0, help='Hard iron offset for mz')
parser.add_argument('--file', default="gps_imu_log.txt", help='Name of the csv to create')
parser.add_argument('--dur', type=int, default=60, help='Logging duration in seconds')
args = parser.parse_args()

# instantiate the imu with magnetometer hard iron offsets
imu = IMU(hi_xoff=args.mxo, hi_yoff=args.myo, hi_zoff=args.mzo)

# instantiate gps module
gps = GPS()

start = time.time() # start time in seconds
duration = args.dur # duration of the logging
filename = args.file # filename of the log file

# field names 
fields = ['Time', 'Gx', 'Gy', 'Gz', 'Ax', 'Ay', 'Az', 'Mx', 'My', 'Mz', 'Latitude', 'Longitude', 'Knots']

with open(filename, 'w') as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(fields)
    while time.time() - start < duration:
        # update the readings on IMU and GPS
        imu.update()
        gps.update()

        imu_raw = imu.get_raw()
        data_row = [imu_raw[i] for i in range(9)]
        data_row.insert(str(datetime.datetime.now()), 0)
        data_row = data_row + [gps.get_lat, gps.get_long, gps.get_knots]
        csvwriter.writerow(data_row)
