import matplotlib.pyplot as plt
import re
import numpy as np
from sklearn import preprocessing
import os
import time
import pandas as pd

print("Running fourier")

SAMPLING_RATE_HZ = 860

fig, axs = plt.subplots(2)
fig.suptitle('A')
axs[0].set_title("Fourier transform")


# Parse data from file into array in python
with open("./temp.txt") as file:
    line = file.readlines()
    array_temp = np.array(line)
    array = np.asarray(array_temp, dtype=float)

# normalize data so we can put it into numpy
data_vector = array # vector with the parsed floats

'''
Call fft on data and create a vector
'''
# The algorithm is nlog(n), so perform sliding window
# fft on the data. Store the dominant frequency of each 
# partition
sliding_dominant_freqs = []
window_size = SAMPLING_RATE_HZ * 5
window_jump = SAMPLING_RATE_HZ * 1

num_windows = len()
for i in range(0, len(data_vector), partition_size):
    last_index = max(len(data_vector), i + partition_size)
    sp = np.fft.fft(data_vector[i:last_index])
    dom_freq = np.argmax(np.real(sp))
    partitioned_dominant_freqs.append(dom_freq)
    
# plot raw data
# for i in range(0, len(data_vector)):
#     plt.plot(i, data_vector[i])

plt.plot(range(len(sp_whole)), sp_whole)
plt.show()