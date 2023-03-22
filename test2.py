import time
import board
import busio
import Adafruit_ADS1x15 #functions
import adafruit_ads1x15.ads1115 as ADS #objects

from adafruit_ads1x15.ads1x15 import Mode
from adafruit_ads1x15.ads1x15 import ADS1x15
from adafruit_ads1x15.analog_in import AnalogIn

# Data collection setup
RATE = 860
SAMPLES = 10000
GAIN = 1

i2c = busio.I2C(board.SCL, board.SDA, frequency=400000)

# Create the ADC object using the I2C bus
# ads1 = ADS.ADS1115(i2c, gain = GAIN, data_rate = 860, mode = Mode.CONTINUOUS, address = 0x49)
ads1 = Adafruit_ADS1x15.ADS1115(address = 0x49)
chan0 = AnalogIn(ads1, ADS.P0)

# Read ADC value
val0 = ads1.read_adc(ADS.P0, gain = GAIN)
val1 = ads1.read_adc(ADS.P1, gain = GAIN)
val2 = ads1.read_adc(ADS.P2, gain = GAIN)
val3 = ads1.read_adc(ADS.P3, gain = GAIN)
print(f"Value 0: {val0}, Value 1: {val1}, Value 2: {val2}, Value 3: {val3}")


# adc = Adafruit_ADS1x15.ADS1115()
# value = adc.read_adc(0, gain=GAIN)
# print(value)