import matplotlib.pyplot as plt
from datetime import time, timedelta
import numpy as np
import os
import shutil
import math
from scipy.signal import butter, lfilter, freqz



tso = []

with open("C:/Users/aaren/Desktop/data/1702384541047/OHI_imu_0_000") as f:
    file_lines = f.readlines()
    for line in file_lines[1:]:
      values = line.split(',')
      tso.append(float(values[0]))

tdo = []
for i in range(len(tso)):
  tdo.append(tso[i]-(0 if i==0 else tso[i-1]))
  if i > 0 and (tso[i] < tso[i-1]):
    print(i)
    print(tso[i])
    print(tso[i-1])
    exit()


tsn = []
with open("C:/Users/aaren/Desktop/data/out/set845/mav0/imu0/data.csv") as f:
    file_lines = f.readlines()
    for line in file_lines[1:]:
      values = line.split(',')
      tsn.append(float(values[0])/1000000000)

tdn = []
for i in range(len(tsn)):
  tdn.append(tsn[i]-(0 if i==0 else tsn[i-1]))
  if i > 0 and (tsn[i] < tsn[i-1]):
    print(i)
    print(tsn[i])
    print(tsn[i-1])
    exit()


print(np.min(tdo))
print(np.min(tdn))

fig, axs = plt.subplots(2,1)

axs[0].plot(tdo[1:])
axs[1].plot(tdn[1:])

plt.show()