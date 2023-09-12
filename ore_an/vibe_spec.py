import matplotlib.pyplot as plt
import re
import numpy as np
import math

time = []
ax = []
ay = []
az = []
am = []

for i in range(0,18,1):
    if (i%10 == 0):
      print(str(round(i/.18,2)) + "% parsed")
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OREGON/rollover1/ORE_imu_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0]))
      ax.append(float(values[5]))
      ay.append(float(values[6]))
      az.append(float(values[7].strip('\n')))
      am.append(np.sqrt(ax[-1]**2 + ay[-1]**2 + az[-1]**2))

break_time = time[-1]

for i in range(0,45,1):
    if (i%10 == 0):
      print(str(round(i/.45,2)) + "% parsed")
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open("../../OREGON/ORE_imu_0_"+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      time.append(float(values[0])+break_time)
      ax.append(float(values[5]))
      ay.append(float(values[6]))
      az.append(float(values[7].strip('\n')))
      am.append(np.sqrt(ax[-1]**2 + ay[-1]**2 + az[-1]**2))

SAMPLING_RATE_HZ = 2000

NFFT = 16384

print(len(ax))




fig, axs = plt.subplots(4)

Pxx, freqs, bins, im = axs[0].specgram(ax, NFFT=NFFT, Fs=SAMPLING_RATE_HZ, noverlap=int(NFFT/32), scale='dB')
Pxx, freqs, bins, im = axs[1].specgram(ay, NFFT=NFFT, Fs=SAMPLING_RATE_HZ, noverlap=int(NFFT/32), scale='dB')
Pxx, freqs, bins, im = axs[2].specgram(az, NFFT=NFFT, Fs=SAMPLING_RATE_HZ, noverlap=int(NFFT/32), scale='dB')
Pxx, freqs, bins, im = axs[3].specgram(am, NFFT=NFFT, Fs=SAMPLING_RATE_HZ, noverlap=int(NFFT/32), scale='dB')

plt.show()


