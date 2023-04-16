import matplotlib.pyplot as plt
import numpy as np
import statistics

# Load data
# Parse data from file into array in python
with open("temp.txt") as file:
    line = file.readlines()
    array_temp = np.array(line)
    array = np.asarray(array_temp, dtype=float)

# Perform analysis
# find the mean
data_vector = array
print("# of peaks: ", len(data_vector))
sum = 0
for i in range(len(data_vector)):
    sum += data_vector[i]
mean = sum / len(data_vector)
print("mean: ", mean)

# find the standard deviation
sd = statistics.stdev(data_vector)
print("standard diviation: ", sd)

''' 
find peaks above average
above_avg_point = []
for i in range(len(data_vector)):
    if (data_vector[i] > mean):
        above_avg_point.append(data_vector[i])
print("# of peaks above avg: ", len(above_avg_point))
'''

# find local maxima
local_maxima_point = []
local_maxima_time = []
for i in range(0, len(data_vector), 5000):
    local_maxima_point.append((data_vector, np.greater))
    local_maxima_time.append(i)
print("# of local maxima: ", len(local_maxima_point))

# plot peaks
x = []
for i in range(len(data_vector)):
    x.append(i + 1)

y = []
for i in range(len(data_vector)):
    if i in local_maxima_time:
        val = 1
    else:
        val = 0
    y.append(val)

plt.plot(x, y)
plt.show()