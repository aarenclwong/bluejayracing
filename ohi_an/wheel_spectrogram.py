import matplotlib.pyplot as plt
import re
import numpy as np
import math
from scipy.signal import butter, lfilter, freqz


def butter_lowpass(cutoff, fs, order=5):
  return butter(order, cutoff, fs=fs, btype='low', analog=False)

def butter_lowpass_filter(data, cutoff, fs, order=5):
  b, a = butter_lowpass(cutoff, fs, order=order)
  y = lfilter(b, a, data)
  return y


time = []
cds_s = []

for i in range(0,62):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    cds_file = open("../../OHIO/endurance/OHI_center_0_"+num)
    file_lines = cds_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0]))
      cds_s.append(float(values[1].strip('\n')))

ftime = []
cds_f = []

spec_file = open("./wheel_freq.txt")
file_lines = spec_file.readlines()
for line in file_lines:
  values = line.split(',')
  ftime.append(float(values[0]))
  cds_f.append(float(values[1]))


SAMPLING_RATE_HZ = 860

NFFT = 512

print(len(cds_s))

cutoff = 400
sampling = 860
order = 10

b = 3500
s = 4000
bt = 0
st = 0
bf = 0
sf = 0
while(time[bt] < b):
  bt+=1
while(time[st] < s):
  st+=1
cds_s = cds_s[bt:st]
time = time[bt:st]

while(ftime[bf] < b):
  bf+=1
while(ftime[sf] < s):
  sf+=1

cds_f = cds_f[bf:sf]
ftime = ftime[bf:sf]

fig, axs = plt.subplots(4)


Pxx, freqs, bins, im = axs[0].specgram(cds_s, NFFT=NFFT, Fs=SAMPLING_RATE_HZ, noverlap=int(NFFT/32), pad_to=16384, mode="magnitude", scale='dB', window=np.blackman(NFFT))
Pxx, freqs, bins, im = axs[1].specgram(butter_lowpass_filter(cds_s, cutoff, sampling, order), NFFT=NFFT, Fs=SAMPLING_RATE_HZ, noverlap=int(NFFT/32), pad_to=16384, mode="magnitude", scale='dB', window=np.blackman(NFFT))
axs[2].scatter(ftime, cds_f, s=.25)
axs[3].scatter(ftime, butter_lowpass_filter(cds_f, 20, sampling, 10), s=.25)



plt.show()


