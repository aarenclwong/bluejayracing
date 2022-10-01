from mahony_ahrs import Mahony, DEFAULT_SAMPLE_FREQ
import board
import adafruit_fxos8700 # accel and magnet
import adafruit_fxas21002c # Gyro

class IMU:
    def __init__(self, sample_freq=DEFAULT_SAMPLE_FREQ):
        self.i2c = board.I2C()
        self.gyro = adafruit_fxas21002c.FXAS21002C(self.i2c)
        self.sensor = adafruit_fxos8700.FXOS8700(self.i2c)
        self.mahony = Mahony(sample_freq)

    def get_raw(self):
        ax, ay, az = self.sensor.accelerometer
        gx, gy, gz = self.gyro.gyroscope
        mx, my, mz = self.sensor.magnetometer
        return gx, gy, gz, ax, ay, az, mx, my, mz

    def update(self):
        self.mahony.update(*self.get_raw())

    def getRoll(self):
        return self.mahony.getRoll()

    def getPitch(self):
        return self.mahony.getPitch()

    def getYaw(self):
        return self.mahony.getYaw()