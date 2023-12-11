import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

points = []

with open("C:/Users/aaren/Downloads/Untitled5.txt") as f:
  file_lines = f.readlines()
  for line in file_lines[1:]:
    values = line.split(',')
    points.append([float(values[1]), float(values[2]), float(values[3])])

points = np.array(points).T
    
end = 100
fig = plt.figure()
ax = fig.add_subplot(111, projection = '3d')
ax.plot(points[0][:100], points[1][:100], points[2][:100], marker = 'x')
ax.scatter(*points.T[0], color = 'red')
plt.show()
