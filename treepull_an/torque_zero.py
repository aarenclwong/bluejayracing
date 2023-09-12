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


tau = []
time = []

for i in range(8):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    torq_file = open("../../treepull/ORE_strain_0_"+num)
    file_lines = torq_file.readlines()
    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0]))
      tau.append(float(values[1]))



#start = 3150000
#dead = 5700000
#istart = 1095000+start
#iend = 1790000+start
#tau = tau[start:istart] + tau[iend:dead]
#time = time[start:istart] + time[iend:dead]

# f = open("gps_vis.txt", "w")
# for i in range(len(gps_lat)):
#   s = gps_lat[i] + ',' + gps_lon[i]+','+gps_alt[i] + '\n'
#   f.writelines([s])
# f.close()
print(max(tau))
print(min(tau))
print(np.average(tau))

print(time[-1]/len(time))

#time = np.arange(0, len(tau))


fig, axs = plt.subplots(2)
fig.suptitle('Oregon Endurance')
axs[0].set_title("Torque vs Time")
axs[0].set_ylabel("Torque(in-lbs)")
axs[0].set_xlabel("Time since logging(s)")


cutoff = 35
sampling = 860
order = 10

axs[0].scatter(time, tau, s=1)
axs[1].scatter(time, butter_lowpass_filter(tau, cutoff, sampling, order), s=1)
plt.show()


