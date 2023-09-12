import matplotlib.pyplot as plt
import re
import numpy as np
import math
from scipy.signal import butter, lfilter, freqz


def butter_lowpass(cutoff, fs, order=5):
  return butter(order, cutoff, fs=fs, btype='low', analog=False)

def butter_lowpass_filter(data, cutoff, fs, order=5):
  b, a = butter_lowpass(cutoff, fs, order=order)
  y = lfilter(b, a, data)
  return y

file_path = "../../OHIO_strain/"
names = ["torque0.txt", "torque1455.7.txt", "torque3518.txt", "torque2210o.txt", "torque3135o.txt"]
cals = [0, 1455.7, 3518, -2210, -3135]
res = []

for name in names:
  signal = []
  time = []

  signal_file = open(file_path + name)
  file_lines = signal_file.readlines()
  for line in file_lines:
    values = line.split(',')
    time.append(float(values[0]))
    signal.append(float(values[1]))
  res.append(np.mean(signal))



fig, axs = plt.subplots(1)
fig.suptitle('OHIO dynamics calibration')
axs.set_title("Torque Calibration")
# axs.set_ylabel("Torque(in-lbs)")
# axs.set_xlabel("Time since logging(s)")


axs.scatter(cals, res, s=5)
plt.show()


