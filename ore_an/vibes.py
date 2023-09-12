import matplotlib.pyplot as plt
import re
import numpy as np
import math

time = []
ax = []
ay = []
az = []

for i in range(0,18,1):
    if (i%10 == 0):
      print(str(round(i/.18,2)) + "% parsed")
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
      ax.append(float(values[5]))
      ay.append(float(values[6]))
      az.append(float(values[7].strip('\n')))

break_time = time[-1]

for i in range(0,45,1):
    if (i%10 == 0):
      print(str(round(i/.45,2)) + "% parsed")
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
      ax.append(float(values[5]))
      ay.append(float(values[6]))
      az.append(float(values[7].strip('\n')))


fx = []
fy = []
fz = []
window_size = 2000
SAMPLING_RATE_HZ = 2048


for i in range(len(time)-window_size):
  if (i%(len(time)/20) == 0):
      print(str(round(100*i/len(time),2)) + "% processed")

  sp = np.abs(np.fft.rfft(ax[i:i + window_size], 4096))
  dom_freq = np.argmax(sp[1:])
  if abs(np.max(sp[1:])) > 400:
    fx.append(dom_freq)
  else:
    fx.append(0)

for i in range(len(time)-window_size):
  if (i%(len(time)/20) == 0):
      print(str(round(100*i/len(time),2)) + "% processed")

  sp = np.abs(np.fft.rfft(ay[i:i + window_size], 4096))
  dom_freq = np.argmax(sp[1:])
  if abs(np.max(sp[1:])) > 400:
    fy.append(dom_freq)
  else:
    fy.append(0)

for i in range(len(time)-window_size):
  if (i%(len(time)/20) == 0):
      print(str(round(100*i/len(time),2)) + "% processed")

  sp = np.abs(np.fft.rfft(az[i:i + window_size], 4096))
  dom_freq = np.argmax(sp[1:])
  if abs(np.max(sp[1:])) > 400:
    fz.append(dom_freq)
  else:
    fz.append(0)


f = open("vibes.txt", "w")
f.writelines(["time,frequency_x,frequency_y,frequency_z"])
for i in range(0, len(fx), 1):
  s = str(time[i+window_size]) + "," + str(fx[i]) + "," + str(fy[i]) + "," + str(fz[i]) + '\n'
  f.writelines([s])
f.close()


fig, axs = plt.subplots(4)
axs[0].set_title("ax")
axs[1].set_title("fx")
axs[2].set_title("fy")
axs[3].set_title("fz")




axs[0].scatter(time, ax, s=1)
axs[1].scatter(time[0:len(time)-window_size], fx, s=1)
axs[2].scatter(time[0:len(time)-window_size], fy, s=1)
axs[3].scatter(time[0:len(time)-window_size], fz, s=1)

plt.show()


