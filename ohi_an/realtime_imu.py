import matplotlib.pyplot as plt
import re
import numpy as np
import os
import time


fig, axs = plt.subplots(3, 2)
fig.suptitle('rt imu')
fig.tight_layout(pad=1.5)

#axs[0].set_ylabel("accel_reading")

plt.ion()
plt.show()

while True:
  os.system('scp pi@baja2.local:bluejayracing/pi/rt_imu_pkg.txt ./')
  
  f = open("/Users/ashleyzhang/Desktop/baja/bluejayracing/ohi_an/rt_imu_pkg.txt", "r")
  f_lines = f.readlines()
  f.close()
  x_gyro = []
  y_gyro = []
  z_gyro = []
  x_accel = []
  y_accel = []
  z_accel = []
  for line in f_lines:
    data = line.split(' ')
    x_gyro.append(float(data[1]))
    y_gyro.append(float(data[2]))
    z_gyro.append(float(data[3]))
    x_accel.append(float(data[4]))
    y_accel.append(float(data[5]))
    z_accel.append(float(data[6]))

  t = np.arange(0,len(x_gyro))

  axs[0, 0].clear()
  axs[1, 0].clear()
  axs[2, 0].clear()
  axs[0, 1].clear()
  axs[1, 1].clear()
  axs[2, 1].clear()
  axs[0, 0].scatter(t,x_gyro, s=1)  
  axs[1, 0].scatter(t,y_gyro, s=1) 
  axs[2, 0].scatter(t,z_gyro, s=1) 
  axs[0, 1].scatter(t,x_accel, s=1)  
  axs[1, 1].scatter(t,y_accel, s=1) 
  axs[2, 1].scatter(t,z_accel, s=1)
  axs[0, 0].set_title('gyro x')
  axs[1, 0].set_title('gyro y')
  axs[2, 0].set_title('gyro z')
  axs[0, 1].set_title('accel x')
  axs[1, 1].set_title('accel y')
  axs[2, 1].set_title('accel z')

  fig.canvas.draw()
  fig.canvas.flush_events()
