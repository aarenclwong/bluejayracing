import matplotlib.pyplot as plt
import re
import numpy as np
from scipy.signal import butter, lfilter, freqz


def butter_lowpass(cutoff, fs, order=5):
  return butter(order, cutoff, fs=fs, btype='low', analog=False)

def butter_lowpass_filter(data, cutoff, fs, order=5):
  b, a = butter_lowpass(cutoff, fs, order=order)
  y = lfilter(b, a, data)
  return y

with open("C:/Users/aaren/Downloads/MobilenetEmbed.txt", 'r') as f:


  losses = []


  lines = f.readlines()
  for line in lines:
    p_line = re.findall(", Loss: \d+\.*\d*", line)
    if len(p_line) > 0:
      loss = re.findall("\d+\.*\d*", p_line[0])
      if len(loss) > 0:
        losses.append(float(loss[0]))

  test_losses = []

  for line in lines:
    p_line = re.findall("Test loss: \d+\.*\d*", line)
    if len(p_line) > 0:
      loss = re.findall("\d+\.*\d*", p_line[0])
      if len(loss) > 0:
        test_losses.append(float(loss[0]))

  fig, ax = plt.subplots(2)

  ax[0].plot(butter_lowpass_filter(losses, 10, 1000, 5))
  ax[1].plot(np.arange(len(test_losses))*400, test_losses)

  plt.show()
  
      