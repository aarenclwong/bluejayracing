import matplotlib.pyplot as plt
import re
import numpy as np
import math
from scipy.stats import gaussian_kde
from matplotlib.colors import LogNorm



mc_file = open("RPM-Torque-with-Randomness-and-Negatives1.csv")
file_lines = mc_file.readlines()

torque = []
speed = []

for line in file_lines:
  values = line.split(',')
  torque.append(float(values[1]))
  speed.append(float(values[0]))


horizontal = 10
vertical = 32
fig, axs = plt.subplots(1)
axs.set_title("Oregon Endurance Torque Speed Bins")
axs.set_ylabel("Torque(in-lbs)")
axs.set_xlabel("CDS Speed(rpm)")

p = axs.hist2d(speed, torque, (horizontal,vertical), cmap=plt.cm.jet,norm=LogNorm())
cb = fig.colorbar(p[3], ax=axs)
cb.set_label("occurances")

total = len(speed)

f = open("mc_bins.txt", "w")

for h in range(horizontal):
  for v in range(vertical):
    s = "{:0.2f}".format((p[1][h]+p[1][h+1])/2) + "," + "{:0.3f}".format((p[2][v]+p[2][v+1])/2) + "," + "{:0.6f}".format(p[0][h][v]/total) + "\n"
    f.writelines([s])

f.close()


plt.show()




























