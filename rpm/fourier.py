import matplotlib.pyplot as plt
import re
import numpy as np
from sklearn import preprocessing
import os
import time
import pandas as pd
import math

print("Running fourier")

SAMPLING_RATE_HZ = 860



# Parse data from file into array in python
with open("./temp.txt") as file:
    line = file.readlines()
    array_temp = np.array(line)
    array = np.asarray(array_temp, dtype=float)

# normalize data so we can put it into numpy
data_vector = np.array(array) # vector with the parsed floats

'''
Call fft on data and create a vector
'''
# The algorithm is nlog(n), so perform sliding window
# fft on the data. Store the dominant frequency of each 
# window partition. If the amplitude is too small (noise),
# set that frequeny 
data_vector[abs(data_vector) <= 5] = 0
sliding_dominant_freqs = []
window_size = 430
window_jump = 1

for i in range(0, len(data_vector) - window_size, window_jump):
    sp = np.abs(np.fft.fft(data_vector[i:i + window_size], 4000))
    dom_freq = np.argmax(sp[1: len(sp)//2])
    
    # Do not add if the max amplitude is small
    if abs(np.max(sp[1: len(sp)//2])) > 400:
        sliding_dominant_freqs.append(dom_freq)
    else:
        sliding_dominant_freqs.append(0)

rps =  np.array(sliding_dominant_freqs) * (SAMPLING_RATE_HZ) / (window_size * 56)

fig, axs = plt.subplots(2)
fig.tight_layout()

axs[0].clear()
axs[0].set_title("Dominant frequencies over sliding windows")
axs[0].plot(range(len(sliding_dominant_freqs)), sliding_dominant_freqs)

axs[1].clear()
axs[1].set_title("Rotations per second")
axs[1].plot(range(len(rps)), rps)
plt.show()