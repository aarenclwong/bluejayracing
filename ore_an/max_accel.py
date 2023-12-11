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


time = []
a_x = []
a_y = []
a_z = []
# a_m = []

for i in range(0,18,1):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OREGON/rollover1/ORE_imu_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0]))
      a_x.append(float(values[5]))
      a_y.append(float(values[6]))
      a_z.append(float(values[7].strip('\n')))
      # a_m.append(np.sqrt(a_x[-1]**2 + a_y[-1]**2 + a_z[-1]**2))

break_time = time[-1]

for i in range(0,45,1): 
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OREGON/ORE_imu_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0])+break_time)
      a_x.append(float(values[5]))
      a_y.append(float(values[6]))
      a_z.append(float(values[7].strip('\n')))
      # a_m.append(np.sqrt(a_x[-1]**2 + a_y[-1]**2 + a_z[-1]**2))

print("parsed")
cutoff = 5
sampling = 2000
order = 1


ts = 18550000
te = 18630000

a_x = a_x[ts:te]
a_y = a_y[ts:te]
a_z = a_z[ts:te]
time = time[ts:te]



fig, axs = plt.subplots(3,2)
fig.tight_layout()
# fig.suptitle('Accel')

# axs[0].set_title("accel x")
# axs[1].set_title("accel y")
# axs[2].set_title("accel z")
# axs[3].set_title("accel m")

# f_x = butter_lowpass_filter(a_x, cutoff, sampling, order)
# f_y = butter_lowpass_filter(a_y, cutoff, sampling, order)
# f_z = butter_lowpass_filter(a_z, cutoff, sampling, order)
# f_m = butter_lowpass_filter(a_m, cutoff, sampling, order)

# print(max(f_x))
# print(max(f_y))
# print(max(f_z))
# print(max(f_m))

# axs[0].scatter(time, a_x, s=1)
# axs[1].scatter(time, a_y, s=1)
# axs[2].scatter(time, a_z, s=1)
# axs[3].scatter(time, a_m, s=1)

axs[0][0].plot(time, a_x)#, s=1)
axs[0][1].plot(time, butter_lowpass_filter(a_x,cutoff,sampling,order))#, s=1)
axs[1][0].plot(time, a_y)#, s=1)
axs[1][1].plot(time, butter_lowpass_filter(a_y,cutoff,sampling,order))#, s=1)
axs[2][0].plot(time, a_z)#, s=1)
axs[2][1].plot(time, butter_lowpass_filter(a_z,cutoff,sampling,order))#, s=1)

axs[0][0].set_title("acceleration m/s^2")
axs[0][1].set_title("lpf acceleration m/s^2")
axs[1][0].set_title("acceleration m/s^2")
axs[1][1].set_title("lpf acceleration m/s^2")
axs[2][0].set_title("acceleration m/s^2")
axs[2][1].set_title("lpf acceleration m/s^2")

plt.show()


