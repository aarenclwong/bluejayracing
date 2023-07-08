import matplotlib.pyplot as plt
import re
import numpy as np
import math

time = []
fr = []
fl = []
steering = []
cds = []


file = open("./ore_dynamics_freq_win128_padx32.txt")
file_lines = file.readlines()
file_lines = file_lines[1:]

for line in file_lines:
  values = line.split(',')
  time.append(float(values[0]))
  fr.append(float(values[1]))
  fl.append(float(values[2]))
  steering.append(float(values[3]))
  cds.append(float(values[4]))

f = open("./ore_dynamics_10hz.txt", 'w')

sample = 86
for i in range(sample,len(time), sample):
  s = str(time[i-sample//2])
  s+= "," + str(np.average(fr[i-sample:i]))
  s+= "," + str(np.average(fl[i-sample:i]))
  s+= "," + str(np.average(steering[i-sample:i]))
  s+= "," + str(np.average(cds[i-sample:i]))
  s+="\n"
  f.writelines([s])

f.close()