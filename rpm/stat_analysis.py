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
sum = 0
for i in range(len(data_vector)):
    sum += data_vector[i]
mean = sum / len(data_vector)
print(mean)

# find the standard deviation
sd = statistics.stdev(data_vector)
print(sd)

# find peaks above average
above_avg_point = []
above_avg_time = []
for i in range(len(data_vector)):
    if (data_vector[i] > mean):
        above_avg_point.append(data_vector[i])
        above_avg_time.append(i)