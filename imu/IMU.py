from mahony_ahrs import Mahony, DEFAULT_SAMPLE_FREQ
import board
import adafruit_fxos8700 # accel and magnet
import adafruit_fxas21002c # Gyro
import time

class IMU:
    def __init__(self, sample_freq=DEFAULT_SAMPLE_FREQ, hi_xoff=0, hi_yoff=0, hi_z0ff=0):
        self.i2c = board.I2C()
        self.gyro = adafruit_fxas21002c.FXAS21002C(self.i2c)
        self.sensor = adafruit_fxos8700.FXOS8700(self.i2c)
        self.mahony = Mahony(sample_freq)
        self.calibrate()

    def calibrate(self):
        ax_avg = 0
        ay_avg = 0
        az_avg = 0
        gx_avg = 0
        gy_avg = 0
        gz_avg = 0
        n = 0
        now = time.time()
        while time.time() - now < 3:
            ax, ay, az = self.sensor.accelerometer
            gx, gy, gz = self.gyro.gyroscope
            ax_avg += ax
            ay_avg += ay
            az_avg += az
            gx_avg += gx
            gy_avg += gy
            gz_avg += gz
            n += 1
            time.sleep(0.1)

        self.ax_offset = ax_avg/n
        self.ay_offset = ay_avg/n
        self.az_offset = az_avg/n - 9.81
        self.gx_offset = gx_avg/n
        self.gy_offset = gy_avg/n
        self.gz_offset = gz_avg/n

    def adjust(self, gx, gy, gz, ax, ay, az, mx, my, mz):
        # adjust according to calibrate data
        return gx - self.gx_offset, gy - self.gy_offset, gz - self.gz_offset, \
            ax - self.ax_offset, ay - self.ay_offset, az-self.az_offset, \
            mx + hi_xoff, my + hi_yoff, mz + hi_zoff
             

    def get_raw(self):
        ax, ay, az = self.sensor.accelerometer
        gx, gy, gz = self.gyro.gyroscope
        mx, my, mz = self.sensor.magnetometer
        return self.adjust(gx, gy, gz, ax, ay, az, mx, my, mz)

    def update(self):
        self.mahony.update(*self.get_raw())

    def getRoll(self):
        return self.mahony.getRoll()

    def getPitch(self):
        return self.mahony.getPitch()

    def getYaw(self):
        return self.mahony.getYaw()