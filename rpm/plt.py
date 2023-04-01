import matplotlib.pyplot as plt
import re
import numpy as np
from sklearn import preprocessing
import os
import time
import pandas as pd

fig, axs = plt.subplots(1)
fig.suptitle('Sensing')
# axs[0].set_title("Filtered Accel Data")

# Parse data from file into array in python
with open("temp.txt") as file:
    line = file.readlines()
    array_temp = np.array(line)
    array = np.asarray(array_temp, dtype=float)
    pass

# plot raw data
plt.plot(range(len(array)), array)
plt.show()

# normalize data so we can put it into numpy
# data_vector = [] # vector with the parsed floats
# data_vector = preprocessing.normalize(array.reshape(-1, 1))

# # for i in range(0, 100):
# #     print(data_vector[i])

# # reshape data vector to be a 2D array
# # data_vector = data_vector.reshape(-1, 1)

# # plot vectorized data
# axs.plot(range(len(data_vector)), data_vector)
# fig.canvas.draw()
# plt.show()
