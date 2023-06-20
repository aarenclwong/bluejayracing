import matplotlib.pyplot as plt
import re
import numpy as np
import math

time = []
cds_s = []

for i in range(0,18,1):
    if (i%10 == 0):
      print(str(round(i/.18,2)) + "% parsed")
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OREGON/rollover1/ORE_center_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0]))
      cds_s.append(float(values[1].strip('\n')))

break_time = time[-1]

for i in range(0,45,1):
    if (i%10 == 0):
      print(str(round(i/.45,2)) + "% parsed")
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OREGON/ORE_center_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0])+break_time)
      cds_s.append(float(values[1].strip('\n')))

print(len(cds_s))

cds_sp = []
window_size = 400
SAMPLING_RATE_HZ = 860

f = open("wheel_spec.txt", "w")

for i in range(len(cds_s)-window_size):
  if (i%(len(cds_s)/20) == 0):
      print(str(round(100*i/len(cds_s),2)) + "% processed")

  sp = np.abs(np.fft.fft(cds_s[i:i + window_size], 3200))

  #cds_sp.append(sp)

  s = str(time[i+window_size])
  for m in sp:
     s+= ","
     s+= str(m)
  s+="\n"
  f.writelines([s])

  

#mph =  np.array(cds_f) * 60 * 0.0397170837 * (SAMPLING_RATE_HZ) / (8*window_size * 24)
f.close()



