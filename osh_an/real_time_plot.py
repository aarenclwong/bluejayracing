import matplotlib.pyplot as plt
import re
import numpy as np
import math
import time

#tourque

download_range = np.arange(0, 2000)
vecs_perst = []

def parse(vec):
    parsed_vec = re.findall("[-+]?\d+\.*\d*[e]*\d*", vec)
    if (len(parsed_vec)!= 1):
        print(parsed_vec)
        print(vec)
    x = float(parsed_vec[0])
    return x

fig, axs = plt.subplots(1)
fig.suptitle("Dashboard")
axs.set_title("Tourque")

axs.set_ylabel("")

plt.ion()
plt.show()

while True:
  f = open("data.txt", "r")
  f_lines = f.readlines()
  num = f_lines[0]
  f_lines.pop(0)

  vecs = []
  for line in f_lines:
    parsed_line = parse(line)
    vecs.append(parsed_line)
    vecs_perst.append(parsed_line)
  data = []
  for vec in vecs:
    data.append(vec[0])

  axs.clear()
  #axs[0].set_ylim(min(norm_data)-data_range,max(norm_data)+data_range)
  axs.plot(download_range, data, s=2) 

  
  fig.canvas.draw()
  fig.canvas.flush_events()