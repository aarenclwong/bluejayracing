# uncomment the following to read raw data
import time
import board
import adafruit_fxos8700 # accel and magnet
import adafruit_fxas21002c # Gyro
from time import sleep
import math

i2c = board.I2C()
gyro = adafruit_fxas21002c.FXAS21002C(i2c)
sensor = adafruit_fxos8700.FXOS8700(i2c)

sleep(1)
while True:
    #accel_x, accel_y, accel_z = sensor.accelerometer
    #gyro_x, gyro_y, gyro_z = gyro.gyroscope
    mag_x, mag_y, mag_z = sensor.magnetometer
    # this is the calibration obtained from calibration.py
    mag_x += 30.6
    mag_y += 11.25
    mag_z += 80.8
    #print(f"Acceleration (m/s^2): ({accel_x}, {accel_y}, {accel_z})")
    #print(f"Gyroscope (rad/sec): ({gyro_x}, {gyro_y}, {gyro_z})")
    #print(f"Magnetometer (uTesla): ({mag_x}, {mag_y}, {mag_z})")
    print(f"x: {round(mag_x, 2)}, y: {round(mag_y, 2)} z: {round(mag_z, 2)}")
    yaw = 180 * math.atan2(mag_y, mag_x)/math.pi
    print(f"strength: {math.sqrt(mag_x**2+mag_y**2+mag_z**2)} uT")
    print(f"Yaw: {yaw}")
    print("\n\n\n\n")
    time.sleep(0.5)
