# using Mahony for sensor fusion
from IMU import IMU
import time

# everything is in seconds
sample_freq = 80 # Hz
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
        print(f"Yaw: {imu.getYaw()}\n\n\n")
        last_print = time.time()
