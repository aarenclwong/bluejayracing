import matplotlib.pyplot as plt
import re
import numpy as np
import os
import time





fig, axs = plt.subplots(3)
fig.suptitle('rt accel')

#axs[0].set_ylabel("accel_reading")

plt.ion()
plt.show()


while True:
  os.system('scp pi@baja2.local:bluejayracing/pi/rt_accel_pkg.txt ./')
  
  f = open("/Users/ashleyzhang/Desktop/baja/bluejayracing/ohi_an/rt_accel_pkg.txt", "r")
  f_lines = f.readlines()
  f.close()
  x_accel = []
  y_accel = []
  z_accel = []
  for line in f_lines:
    data = line.split(',')
    x_accel.append(float(data[0]))
    y_accel.append(float(data[1]))
    z_accel.append(float(data[2]))
  t = np.arange(0,len(x_accel))
  axs[0].clear()
  axs[1].clear()
  axs[2].clear()
  axs[0].scatter(t,x_accel, s=1)  
  axs[1].scatter(t,y_accel, s=1) 
  axs[2].scatter(t,z_accel, s=1) 


  fig.canvas.draw()
  fig.canvas.flush_events()

