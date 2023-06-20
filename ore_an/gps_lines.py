import matplotlib.pyplot as plt
import re
import numpy as np
import math

time = []
lat = []
lon = []
alt = []

for i in range(0,18,1):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OREGON/rollover1/ORE_gps_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      if (values[1]!="nan"):
        time.append(float(values[0]))
        lat.append(float(values[1]))
        lon.append(float(values[2]))
        alt.append(float(values[3].strip('\n')))

break_time = time[-1]

for i in range(0,45,1):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OREGON/ORE_gps_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      if (values[1]!="nan"):
        time.append(float(values[0])+break_time)
        lat.append(float(values[1]))
        lon.append(float(values[2]))
        alt.append(float(values[3].strip('\n')))


f = open("gps_vis.txt", "w")
for i in range(0, len(lat), 5):
  s = str(lat[i]) + ',' + str(lon[i])+','+str(time[i]) + '\n'
  f.writelines([s])
f.close()

fig, axs = plt.subplots(2)
fig.suptitle('GPS')
axs[0].set_title("gps coords")
axs[1].set_title("lat plot")

axs[0].scatter(lon, lat, s=1)
axs[1].scatter(time, lat, s=1)

plt.show()


