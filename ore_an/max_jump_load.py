import matplotlib.pyplot as plt
import re
import numpy as np
import math


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


start = 3000000
dead = 5700000
tau = tau[start:dead]
time = time[start:dead]

t=0
poi = []

while t <len(time):
  if (tau[t] < -5500):
    poi.append(t)
    t+=100
  else:
    t+=1
   

ss_file = open("./wheel_freq_win512_pad4096.txt")
file_lines = ss_file.readlines()

stime = []
freq = []
mph = []

for line in file_lines:
  values = line.split(',')
  stime.append(float(values[0]))
  freq.append(float(values[1]))
  mph.append(float(values[2].strip('\n')))

t = 0
speed_ranges = []
for p in list(np.array(time)[poi]):
  while(stime[t] < p-1):
    t+=1
  r1 = t
  while(stime[t] < p+10):
    t+=1
  r2=t
  speed_ranges.append([r1,r2])


l = 1
   

#time = np.arange(0, len(tau))

print(list(np.array(time)[poi]))

fig, axs = plt.subplots(2)
fig.suptitle('Oregon Endurance')
axs[0].set_title("Torque vs Time")
axs[0].set_ylabel("Torque(in-lbs)")
axs[0].set_xlabel("Time since logging(s)")


axs[0].scatter(time, tau, s=1)
axs[0].scatter(list(np.array(time)[poi]), list(np.array(tau)[poi]), s=5, c='red')

axs[1].scatter(stime[speed_ranges[l][0]:speed_ranges[l][1]], mph[speed_ranges[l][0]:speed_ranges[l][1]], s=1)
axs[1].set_ylim([0,30])

plt.show()


