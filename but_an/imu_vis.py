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
g_x = []
g_y = []
g_z = []

# imu_file = open("C:/Users/aaren/Desktop/data/biases/data/1702357282864/OHI_imu_0_000")
# imu_file = open("C:/Users/aaren/Desktop/data/biases/data/1702359299834/OHI_imu_0_000")
imu_file = open("C:/Users/aaren/Desktop/data/1702348921766/OHI_imu_0_000")
file_lines = imu_file.readlines()

for line in file_lines:
  values = line.split(',')
  time.append(float(values[0]))
  g_x.append(float(values[2])*0.0174533)
  g_y.append(float(values[3])*0.0174533)
  g_z.append(float(values[4])*0.0174533)
  a_x.append(float(values[5])*9.81)
  a_y.append(float(values[6])*9.81)
  a_z.append(float(values[7].strip('\n'))*9.81)
  # a_m.append(np.sqrt(a_x[-1]**2 + a_y[-1]**2 + a_z[-1]**2))

print("parsed")
cutoff = 10
sampling = 2000
order = 1



fig, axs = plt.subplots(3,4)
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

axs[0][2].plot(time, g_x)#, s=1)
axs[0][3].plot(time, butter_lowpass_filter(g_x,cutoff,sampling,order))#, s=1)
axs[1][2].plot(time, g_y)#, s=1)
axs[1][3].plot(time, butter_lowpass_filter(g_y,cutoff,sampling,order))#, s=1)
axs[2][2].plot(time, g_z)#, s=1)
axs[2][3].plot(time, butter_lowpass_filter(g_z,cutoff,sampling,order))#, s=1)

axs[0][0].set_title("acceleration m/s^2")
axs[0][1].set_title("lpf acceleration m/s^2")
axs[1][0].set_title("acceleration m/s^2")
axs[1][1].set_title("lpf acceleration m/s^2")
axs[2][0].set_title("acceleration m/s^2")
axs[2][1].set_title("lpf acceleration m/s^2")

axs[0][2].set_title("gyro rad/s")
axs[0][3].set_title("lpf gyro rad/s")
axs[1][2].set_title("gyro rad/s")
axs[1][3].set_title("lpf gyro rad/s")
axs[2][2].set_title("gyro rad/s")
axs[2][3].set_title("lpf gyro rad/s")


print(np.mean(butter_lowpass_filter(g_x,cutoff,sampling,order)))
print(np.mean(butter_lowpass_filter(g_y,cutoff,sampling,order)))
print(np.mean(butter_lowpass_filter(g_z,cutoff,sampling,order)))
print(np.std(butter_lowpass_filter(g_x,cutoff,sampling,order)))
print(np.std(butter_lowpass_filter(g_y,cutoff,sampling,order)))
print(np.std(butter_lowpass_filter(g_z,cutoff,sampling,order)))

plt.show()


