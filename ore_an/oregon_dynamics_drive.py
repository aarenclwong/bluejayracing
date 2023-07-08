import matplotlib.pyplot as plt
import re
import numpy as np
import math

steering = []
time = []
stime = []
fr_s = []
fl_s = []
cds_s = []

for i in range(0,61,1):
    if (i%10 == 0):
      print(str(round(i/.90,2)) + "% parsed")
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OSHKOSH/OSH_front_4_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0]))
      fr_s.append(float(values[1]))
      fl_s.append(float(values[2]))
      steering.append(float(values[3].strip('\n'))*270/(19653.0)-135)







fig, axs = plt.subplots(3)
# axs[0].set_title("raw signal")
# axs[1].set_title("dominant forier transform")
# axs[2].set_title("mph")



axs[0].scatter(time, fr_s, s=1)
axs[1].scatter(time, fl_s, s=1)
axs[2].scatter(time, steering, s=1)

plt.show()


