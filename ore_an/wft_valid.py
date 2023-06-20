import matplotlib.pyplot as plt
import re
import numpy as np
import math


time = []
mx = []
my = []
mz = []

nm_inlb_conv = 8.8507457916

file = open("../../wft2.txt")
file_lines = file.readlines()
file_lines = file_lines[1:]

for line in file_lines:
  values = line.split(',')
  time.append(float(values[0]))
  mx.append(float(values[4])*nm_inlb_conv)
  my.append(float(values[5])*nm_inlb_conv)
  mz.append(float(values[6])*nm_inlb_conv)




fig, axs = plt.subplots(3)
fig.suptitle('S, F, mph')
axs[0].set_title("mx")
axs[1].set_title("my")
axs[2].set_title("mz")


print(max(mx))
print(max(my))
print(max(mz))
print(min(mx))
print(min(my))
print(min(mz))


axs[0].scatter(time, mx, s=1)
axs[1].scatter(time, my, s=1)
axs[2].scatter(time, mz, s=1)


plt.show()


