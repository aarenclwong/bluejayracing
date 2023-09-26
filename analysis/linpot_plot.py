from ast import parse
import matplotlib.pyplot as plt
import re
import numpy as np


l1 = open("../data/LOGGER01.CSV", "r")

lines = l1.readlines()

lines.pop(0)
parsed_lines = [[], [], [], [], [], [], [], [], []]

for line in lines:
  p_line = re.findall("[-+]?\d+\.*\d*", line)
  data_sentence = []
  for i in range(len(p_line)):
    parsed_lines[i].append(float(p_line[i]))



for i in range(len(parsed_lines[0])):
  parsed_lines[0][i]/=1000
  parsed_lines[0][i]/=50




# 0 = Time (ms)
# 1 = Shock pot FL displacement (in)
# 2 = Shock pot FL voltage (V)
# 3 = Shock pot FR displacement (in)
# 4 = Shock pot FR voltage (V)
# 5 = Shock pot RL displacement (in)
# 6 = Shock pot RL voltage (V)
# 7 = Shock pot RR displacement (in)
# 8 = Shock pot RR voltage (V)

fig, axs = plt.subplots(4)

fig.suptitle('Linear Potentiometer Data')

axs[0].set_title("Front Left")
axs[1].set_title("Front Right")
axs[2].set_title("Rear Left")
axs[3].set_title("Rear Right")

axs[0].scatter(parsed_lines[0], parsed_lines[2], s=2)
axs[1].scatter(parsed_lines[0], parsed_lines[4], s=2)
axs[2].scatter(parsed_lines[0], parsed_lines[6], s=2)
axs[3].scatter(parsed_lines[0], parsed_lines[8], s=2)

#plt.ion()
plt.show()

i = (1/6)
t = i


# while(True):
#   axs[0].set_xlim(t-i, t)
#   axs[1].set_xlim(t-i, t)
#   axs[2].set_xlim(t-i, t)
#   axs[3].set_xlim(t-i, t)
#   t+=i
#   fig.canvas.draw()
#   fig.canvas.flush_events()