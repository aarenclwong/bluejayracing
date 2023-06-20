import matplotlib.pyplot as plt
import re
import numpy as np
import math

time = []
lat = []
lon = []
alt = []

for i in range(0,18,1):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OREGON/rollover1/ORE_gps_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      if (values[1]!="nan"):
        time.append(float(values[0]))
        lat.append(float(values[1]))
        lon.append(float(values[2]))
        alt.append(float(values[3].strip('\n')))

break_time = time[-1]

for i in range(0,45,1):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OREGON/ORE_gps_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      if (values[1]!="nan"):
        time.append(float(values[0])+break_time)
        lat.append(float(values[1]))
        lon.append(float(values[2]))
        alt.append(float(values[3].strip('\n')))

lap_times = [4180, 6610, 7290, 7730, 8130, 8612, 9050, 9500, 9880, 10380, 10910, 12980, 13430, 13840, 14270, 14710, 15140, 15570, 15990, 16460, 17020, 17490, 17940, 18350, 18780]

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
range_start = 0
range_end = 0
b = 0
e = 0
lap_num = 1
f = open("heatmap.txt", "w")
f.writelines("time,latitude,longitude,speed")
for i in range(0, len(lap_segments[lap_num][0])-1):
  
  while(stime[b] < lap_segments[lap_num][0][i]):
    b+=1

  while(stime[e] < lap_segments[lap_num][0][i+1]):
    e+=1
  if (range_start == 0):
    range_start = b
  speed = np.average(mph[b:e])
  s = str(lap_segments[lap_num][0][i]) + ',' + str(lap_segments[lap_num][1][i])+','+str(lap_segments[lap_num][2][i]) +","+ str(speed)+ '\n'
  f.writelines([s])
range_end = e
f.close()


lap_speeds = mph[range_start:range_end]
print(max(lap_speeds))


fig, axs = plt.subplots(1)
fig.suptitle('Lap Speed')


axs.plot(stime[range_start:range_end], lap_speeds)

plt.show()