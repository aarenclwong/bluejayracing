# uncomment the following to read raw data
'''import time
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
'''

# using Mahony for sensor fusion
from IMU import IMU
import time

# everything is in seconds
sample_freq = 100 # Hz
sample_period = 1/sample_freq
imu = IMU(sample_freq)
print_period = 0.5 # print results once every print_period
last_print = time.time()

while True:
    now = time.time()
    imu.update()
    # wait
    while time.time() - now < sample_period:
        pass
    if time.time() - last_print >= print_period:
        print(f"Roll: {imu.getRoll()}")
        print(f"Pitch: {imu.getPitch()}")
        print(f"Yaw: {imu.getYaw()}")
        last_print = time.time()
