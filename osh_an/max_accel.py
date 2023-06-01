import matplotlib.pyplot as plt
import re
import numpy as np
import math

time = []
a_x = []
a_y = []
a_z = []
a_m = []

for i in range(10,12,1):
    if (i%10 == 0):
      print(i)
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OSHKOSH/3/OSH_imu_3_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0]))
      a_x.append(float(values[5]))
      a_y.append(float(values[6]))
      a_z.append(float(values[7].strip('\n')))
      a_m.append(np.sqrt(a_x[-1]**2 + a_y[-1]**2 + a_z[-1]**2))

# f = open("gps_vis.txt", "w")
# for i in range(len(gps_lat)):
#   s = gps_lat[i] + ',' + gps_lon[i]+','+gps_alt[i] + '\n'
#   f.writelines([s])
# f.close()
print(max(a_m))
print(max(a_x))
print(max(a_y))
print(max(a_z))

fig, axs = plt.subplots(4)
fig.suptitle('Accel')
axs[0].set_title("accel x")
axs[1].set_title("accel y")
axs[2].set_title("accel z")
axs[3].set_title("accel m")



axs[0].scatter(time, a_x, s=1)
axs[1].scatter(time, a_y, s=1)
axs[2].scatter(time, a_z, s=1)
axs[3].scatter(time, a_m, s=1)

plt.show()


