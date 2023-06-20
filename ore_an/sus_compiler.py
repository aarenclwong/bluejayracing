import matplotlib.pyplot as plt
import re
import numpy as np
import math


time = []
a_x = []
a_y = []
a_z = []
a_m = []
w_x = []
w_y = []
w_z = []
      

for i in range(0,18,1):
    if (i%8 == 0):
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
      w_x.append(float(values[2]))
      w_y.append(float(values[3]))
      w_z.append(float(values[4]))
      a_x.append(float(values[5]))
      a_y.append(float(values[6]))
      a_z.append(float(values[7].strip('\n')))
    imu_file.close()

break_time = time[-1]

for i in range(0,45,1):
    if (i%8 == 0):
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
      w_x.append(float(values[2]))
      w_y.append(float(values[3]))
      w_z.append(float(values[4]))
      a_x.append(float(values[5]))
      a_y.append(float(values[6]))
      a_z.append(float(values[7].strip('\n')))

    imu_file.close()

print(len(a_x))

data = [a_x, a_y, a_z, w_x, w_y, w_z]

f = open("sus200hz.txt", "w")
f.writelines(["time,x_accel,y_accel,z_accel,x_angular,y_angular,z_angular\n"])
i = 8
n = len(time)
prev = 0
c = 1

while (i < n-2000):
  s = str(time[prev])
  for col in range(6):
    s += "," + str(np.average(data[col][prev:i]))[:9]
  s+="\n"
  f.writelines([s])
  prev = i
  i+=1
  c+=1
  while(time[i] <= time[0]+.005*c):
     i+=1
  
  
     
  
f.close()