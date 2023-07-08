import matplotlib.pyplot as plt
import re
import numpy as np
import math
from scipy.stats import gaussian_kde
from matplotlib.colors import LogNorm


tau = []
time = []

for i in range(16):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    torq_file = open("../../OREGON/rollover1/ORE_strain_0_"+num)
    file_lines = torq_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0]))
      tau.append(float(values[1])*7.05-246)

break_time = time[-1]

for i in range(40):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    torq_file = open("../../OREGON/ORE_strain_0_"+num)
    file_lines = torq_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0])+break_time)
      tau.append(float(values[1])*7.05-246)

start = 3150000
dead = 5700000
istart = 1095000+start
iend = 1790000+start
tau = tau[start:istart] + tau[iend:dead]
time = time[start:istart] + time[iend:dead]






ss_file = open("./wheel_freq_win400_pad3200.txt")
file_lines = ss_file.readlines()

stime = []
freq = []
mph = []

for line in file_lines:
  values = line.split(',')
  stime.append(float(values[0]))
  freq.append(float(values[1]))
  mph.append(float(values[2].strip('\n')))


rss = 0

rpm = []
torque = []

for t in range(1,len(time)):
  counter = 1
  value = 0
  while(stime[rss] < time[t]):
    value+=freq[rss] * 60 * 860 / (3200*24)
    #value+=mph[rss]/0.0397170837
    rss+=1
    counter+=1
  value+=freq[rss] * 60 * 860 / (3200*24)
  value/=counter
  torque.append(tau[t])
  rpm.append(value)

print(len(rpm))
print(len(torque))

horizontal = 10
vertical = 8
fig, axs = plt.subplots(1)
axs.set_title("Oregon Endurance Torque Speed Bins")
axs.set_ylabel("Torque(in-lbs)")
axs.set_xlabel("CDS Speed(rpm)")

#axs.scatter(rpm,torque, s=1)
p = axs.hist2d(rpm, torque, (horizontal,vertical), cmap=plt.cm.jet, norm=LogNorm())
cb = fig.colorbar(p[3], ax=axs)
cb.set_label("occurances")

print(len(p[1]))
print(len(p[0]))
print(len(p[0][0]))

f = open("ts_bins.txt", "w")

for h in range(horizontal):
  for v in range(vertical):
    s = str(p[1][h+1]) + "," + str(p[2][v+1]) + "," + str(p[0][h][v]) + "\n"
    f.writelines([s])

f.close()
     
#plt.colorbar()
plt.show()




  
  
   
   
     








