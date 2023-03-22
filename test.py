# SPDX-FileCopyrightText: 2021 ladyada for Adafruit Industries
# SPDX-License-Identifier: MIT

import time
import board
import busio
# import Adafruit_ADS1x15 #functions
import adafruit_ads1x15.ads1115 as ADS #objects

from adafruit_ads1x15.ads1x15 import Mode
# from adafruit_ads1x15.ads1x15 import ADS1x15
from adafruit_ads1x15.analog_in import AnalogIn

# Data collection setup
RATE = 860
SAMPLES = 10000
GAIN = 1

# Create the I2C bus with a fast frequency
# NOTE: Your device may not respect the frequency setting
#       Raspberry Pis must change this in /boot/config.txt

# i2c1 = busio.I2C(board.SCL, board.SDA, frequency=400000)
# i2c2 = busio.I2C(board.SCL, board.SDA, frequency=400000)
# i2c3 = busio.I2C(board.SCL, board.SDA, frequency=400000)
# i2c4 = busio.I2C(board.SCL, board.SDA, frequency=400000)
i2c = busio.I2C(board.SCL, board.SDA, frequency=400000)

# Create the ADC object using the I2C bus
ads1 = ADS.ADS1115(i2c, gain = GAIN, data_rate = RATE, mode = Mode.CONTINUOUS, address = 0x49)
ads2 = ADS.ADS1115(i2c, gain = GAIN, data_rate = RATE, mode = Mode.CONTINUOUS, address = 0x48)
ads3 = ADS.ADS1115(i2c, gain = GAIN, data_rate = RATE, mode = Mode.CONTINUOUS, address = 0x4a)
ads4 = ADS.ADS1x15(i2c, gain = GAIN, data_rate = RATE, mode = Mode.CONTINUOUS, address = 0x4b)

# Create single-ended input on channel 0
adc0 = AnalogIn(ads1)
adc1 = AnalogIn(ads2, ADS.P0)
adc2 = AnalogIn(ads3, ADS.P0)
adc3 = AnalogIn(ads4, ADS.P0)

# print(chan0.value, chan0.voltage)
# print(chan1.value, chan1.voltage)
# print(chan2.value, chan2.voltage)

# ADC Configuration
ads1.mode = Mode.CONTINUOUS
ads1.data_rate = RATE
ads2.mode = Mode.CONTINUOUS
ads2.data_rate = RATE
ads3.mode = Mode.CONTINUOUS
ads3.data_rate = RATE
ads4.mode = Mode.CONTINUOUS
ads4.data_rate = RATE

# First ADC channel read in continuous mode configures device
# and waits 2 conversion cycles
_ = adc0.value
_ = adc1.value
_ = adc2.value
_ = adc3.value

# sample_interval = 1.0 / ads1.data_rate
sample_interval = 1.0 / ads1.data_rate

repeats = 0
skips = 0
bittommconversion = 96.0612

data1 = [None] * SAMPLES
data2 = [None] * SAMPLES
data3 = [None] * SAMPLES
data4 = [None] * SAMPLES

start = time.monotonic()
time_next_sample = start + sample_interval

# Read the same channel over and over
for i in range(SAMPLES):
    # Wait for expected conversion finish time
    while time.monotonic() < (time_next_sample):
        pass

    # Read conversion value for ADC channel
    data1[i] = adc0.value
    data2[i] = adc1.value
    data3[i] = adc2.value
    data4[i] = adc3.value
    # adc = Adafruit_ADS1x15.ADS1115()
    # data1[i] = adc0.read_adc(1,gain=GAIN)
    # data2[i] = ads1.read_adc(2, gain=GAIN)
    # data3[i] = ads1.read_adc(3, gain=GAIN)
    # data4[i] = ads1.read_adc(4, gain=GAIN)
    
    # Loop timing
    time_last_sample = time.monotonic()
    time_next_sample = time_next_sample + sample_interval
    if time_last_sample > (time_next_sample + sample_interval):
        skips += 1
        time_next_sample = time.monotonic() + sample_interval

    # Detect repeated values due to over polling
    # if data1[i] == data1[i - 1]:
    #     repeats += 1
    # print(f"ADC0: {data1[i]}")
    if data2[i] == data2[i - 1]:
        repeats += 1
    print(f"ADC1: {(data1[i]/bittommconversion)*.039} inches")
    print(f"ADC2: {(data2[i]/bittommconversion)*.039} inches")
    print(f"ADC3: {(data3[i]/bittommconversion)*.039} inches")
    print(f"ADC4: {(data4[i]/bittommconversion)*.039} inches")
    #convert bits to inches
    #275 mm = 10.827 in 26392

    # if data2[i] == data2[i - 1]:
    #     repeats += 1
    # print(f"ADC2: {data3[i]}")
    # if data2[i] == data2[i - 1]:
    #     repeats += 1
    # print(f"ADC3: {data4[i]}")

end = time.monotonic()
total_time = end - start

rate_reported = SAMPLES / total_time
rate_actual = (SAMPLES - repeats) / total_time
# NOTE: leave input floating to pickup some random noise
#       This cannot estimate conversion rates higher than polling rate

print("Took {:5.3f} s to acquire {:d} samples.".format(total_time, SAMPLES))
print("")
print("Configured:")
print("    Requested       = {:5d}    sps".format(RATE))
print("    Reported        = {:5d}    sps".format(ads1.data_rate))
print("")
print("Actual:")
print("    Polling Rate    = {:8.2f} sps".format(rate_reported))
print("                      {:9.2%}".format(rate_reported / RATE))
print("    Skipped         = {:5d}".format(skips))
print("    Repeats         = {:5d}".format(repeats))
print("    Conversion Rate = {:8.2f} sps   (estimated)".format(rate_actual))
