import matplotlib.pyplot as plt
import re
import numpy as np
import math


steering = []
time = []
stime = []
fr_s = []
fl_s = []
cds_s = []

for i in range(90):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    torq_file = open("../../OREGON/dynamics/ORE_front_4_"+num)
    file_lines = torq_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0]))
      fr_s.append(float(values[1]))
      fl_s.append(float(values[2]))
      steering.append(float(values[3].strip('\n'))*270/(19653.0)-135)

for i in range(90):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    torq_file = open("../../OREGON/dynamics/ORE_center_4_"+num)
    file_lines = torq_file.readlines()

    for line in file_lines:
      values = line.split(',')
      stime.append(float(values[0]))
      cds_s.append(float(values[1]))

# time correction
stime = stime[25:]
cds_s = cds_s[25:]

fr_f = []
fl_f = []
cds_f = []
window_size = 128
zero_padding = window_size*32
SAMPLING_RATE_HZ = 860
ROTOR_GEAR_TEETH = 56
CDS_GEAR_TEETH = 24


for i in range(len(fr_s)-window_size):
  if (i%(len(fr_s)/20) == 0):
      print(str(round(100*i/len(fr_s),2)) + "% processed")

  sp = np.abs(np.fft.rfft(fr_s[i:i + window_size], zero_padding))
  dom_freq = np.argmax(sp[1: len(sp)])
  if abs(np.max(sp[1: len(sp)])) > 400:
    fr_f.append(dom_freq)
  else:
    fr_f.append(0)


for i in range(len(fl_s)-window_size):
  if (i%(len(fl_s)/20) == 0):
      print(str(round(100*i/len(fl_s),2)) + "% processed")

  sp = np.abs(np.fft.rfft(fl_s[i:i + window_size], zero_padding))
  dom_freq = np.argmax(sp[1: len(sp)])
  if abs(np.max(sp[1: len(sp)])) > 400:
    fl_f.append(dom_freq)
  else:
    fl_f.append(0)

for i in range(len(cds_s)-window_size):
  if (i%(len(cds_s)/20) == 0):
      print(str(round(100*i/len(cds_s),2)) + "% processed")

  sp = np.abs(np.fft.rfft(cds_s[i:i + window_size], zero_padding))
  dom_freq = np.argmax(sp[1: len(sp)])
  if abs(np.max(sp[1: len(sp)])) > 400:
    cds_f.append(dom_freq)
  else:
    cds_f.append(0)

fr_rpm =  np.array(fr_f) * 60  * (SAMPLING_RATE_HZ) / (zero_padding * ROTOR_GEAR_TEETH)
fl_rpm =  np.array(fl_f) * 60  * (SAMPLING_RATE_HZ) / (zero_padding * ROTOR_GEAR_TEETH)
cds_rpm = np.array(cds_f) * 60  * (SAMPLING_RATE_HZ) / (zero_padding * CDS_GEAR_TEETH)


print(max(steering))
print(min(steering))
print(max(fr_rpm))
print(max(fl_rpm))
print(max(cds_rpm))
print(len(time))
print(len(stime))
print(len(steering))


f = open("ore_dynamics_freq_win128_padx32.txt", "w")
f.writelines(["time,fr_rpm,fl_rpm,steering_deg,cds_rpm\n"])

m_len = min([len(time),len(stime),len(steering),len(cds_rpm)])

for i in range(m_len):
  s = str(time[i])
  s+= "," + str(fr_rpm[i])
  s+= "," + str(fl_rpm[i])
  s+= "," + str(steering[i])[:5]
  s+= "," + str(cds_rpm[i])
  s+="\n"
  f.writelines([s])

f.close()


