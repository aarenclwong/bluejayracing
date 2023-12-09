import matplotlib.pyplot as plt
import re
import numpy as np
from sklearn import preprocessing
from scipy.signal import find_peaks
import os
import time
import pandas as pd

fig, axs = plt.subplots(nrows=2)
# fig.subtitle('Sensing')
axs[0].set_title("Filtered Accel Data")

# Parse data from file into array in python
with open("temp.txt") as file:
    line = file.readlines()
    array_temp = np.array(line)
    array = np.asarray(array_temp, dtype=float)
    pass

# plot raw data
axs[0].plot(range(len(array)), array)

# normalize data so we can put it into numpy
# data_vector = [] # vector with the parsed floats
# data_vector = preprocessing.normalize(array.reshape(-1, 1))
data_vector = np.array(array).reshape(-1, 1)
data_vector = preprocessing.normalize(data_vector)

# for i in range(0, 100):
#     print(data_vector[i])

# plot vectorized data
# axs[1].plot(range(len(data_vector)), data_vector)
# axs[1].set_title("Vectorized Data")
# fig.canvas.draw()

# Find local maxima in the normalized data
peaks, _ = find_peaks(data_vector.ravel())

# Plot the original data and the local maxima
#ax.plot(array)
axs[1].plot(peaks, array[peaks])
axs[1].set_title("Local Maxima in Data")
# axs[1].set_xlabel("Sample Number")
axs[1].set_ylabel("Amplitude")
plt.show()
