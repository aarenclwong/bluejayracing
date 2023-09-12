import matplotlib.pyplot as plt
import re
import numpy as np
import math

time = []
lat = []
lon = []
alt = []

for i in range(0,62):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OHIO/endurance/OHI_gps_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      if (values[1]!="nan"):
        time.append(float(values[0]))
        lat.append(float(values[1]))
        lon.append(float(values[2]))
        alt.append(float(values[3].strip('\n')))


lap_times = [4180]

start_index = 0
end_index = 0
lap_segments = []

for lap in range(len(lap_times)-1):
  while (time[start_index] < lap_times[lap]):
    start_index+=1
  end_index = start_index+1
  while (time[end_index] < lap_times[lap+1]):
    end_index+=1
  lap_segment = [time[start_index:end_index], lat[start_index:end_index], lon[start_index:end_index]]
  lap_segments.append(lap_segment)
  start_index = end_index+1

ss_file = open("./wheel_spec.txt")
file_lines = ss_file.readlines()

stime = []
freqs = []

for line in file_lines:
  values = line.split(',')
  stime.append(float(values[0]))
  spec = []
  for freq in range(1,len(values)):
    spec.append(float(values[freq]))
  freqs.append(spec)
  
fig, axs = plt.subplots(1)
fig.suptitle('Lap Speed')


axs.contourf(stime,np.arange(len(freqs)),freqs)

plt.show()