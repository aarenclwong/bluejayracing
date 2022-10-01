import time
import board
import adafruit_fxos8700 # accel and magnet
import adafruit_fxas21002c # Gyro
from time import sleep

i2c = board.I2C()
gyro = adafruit_fxas21002c.FXAS21002C(i2c)
sensor = adafruit_fxos8700.FXOS8700(i2c)

sleep(1)
while True:
    accel_x, accel_y, accel_z = sensor.accelerometer
    gyro_x, gyro_y, gyro_z = gyro.gyroscope
    mag_x, mag_y, mag_z = sensor.magnetometer
    print(f"Acceleration (m/s^2): ({accel_x}, {accel_y}, {accel_z})")
    print(f"Gyroscope (rad/sec): ({gyro_x}, {gyro_y}, {gyro_z})")
    print(f"Magnetometer (uTesla): ({mag_x}, {mag_y}, {mag_z})")
    time.sleep(0.5)
    print("\n\n\n\n")
