import matplotlib.pyplot as plt
from datetime import time, timedelta
import numpy as np
import os
import shutil
import math
from scipy.signal import butter, lfilter, freqz

def butter_lowpass(cutoff, fs, order=5):
  return butter(order, cutoff, fs=fs, btype='low', analog=False)

def butter_lowpass_filter(data, cutoff, fs, order=5):
  b, a = butter_lowpass(cutoff, fs, order=order)
  y = lfilter(b, a, data)
  return y



imu_file = "OHI_imu_0_000"
gps_file = "OHI_gps_0_000"
cam_file = "timestamps.txt"
params_ = "OHI_parameters_0"
root = "C:/Users/aaren/Desktop/data/"
paths = os.listdir(root)
paths = [path+"/" for path in paths]
# paths = ["1701833093968/", "1701836195175/"]


output = "out/"

if output in paths: paths.remove(output)


for path in paths:
  imu_t_s = []
  imu_d = [[],[],[],[],[],[]]
  with open(root + path + imu_file) as f:
    file_lines = f.readlines()
    for line in file_lines:
      values = line.split(',')
      if len(values) == 8:
        t = float(values[0])
        imu_t_s.append(t)
        for i in range(3):
          imu_d[i].append(float(values[i+2]))
        for i in range(3):
          imu_d[i+3].append(float(values[i+5]))

  imu_t_d = []

  for i in range(len(imu_t_s)):
    imu_t_d.append(imu_t_s[i]-(0 if i==0 else imu_t_s[i-1]))

  imu_d[0] = (np.array(imu_d[0])*0.0174533).tolist()
  imu_d[1] = (np.array(imu_d[1])*0.0174533).tolist()
  imu_d[2] = (np.array(imu_d[2])*0.0174533).tolist()
  imu_d[3] = (np.array(imu_d[3])*9.81).tolist()
  imu_d[4] = (np.array(imu_d[4])*9.81).tolist()
  imu_d[5] = (np.array(imu_d[5])*9.81).tolist()


  for c in range(len(imu_d)):
    imu_d[c] = butter_lowpass_filter(imu_d[c], 10, 2000, 1)

  imu_p = []
  for r in range(len(imu_d[0])):
    imu = []
    for c in range(len(imu_d)):
      imu.append(imu_d[c][r])
    imu_p.append(imu)
  imu_d = imu_p
  

  cam_t_ms = []
  with open(root + path + cam_file) as f:
    file_lines = f.readlines()

    for line in file_lines[1:]:
      cam_t_ms.append(float(line))

  cam_t_ns = np.array(cam_t_ms[1:]) * 1000000
  imu_t_ns = np.array(imu_t_s) * 1000000000

  cam_t_ns = np.char.mod('%d', cam_t_ns)
  imu_t_ns = np.char.mod('%d', imu_t_ns)

  output_base = root + output + "set"+path[5:8] + "/"

  if not os.path.exists(output_base):
    os.makedirs(output_base)
    os.makedirs(output_base + "mav0")
    os.makedirs(output_base + "mav0/imu0")
    os.makedirs(output_base + "mav0/cam0")
    os.makedirs(output_base + "mav0/cam0/data")

  cam = open(output_base + "mav0/cam0/data.csv", "w")
  cam.writelines("#timestamp [ns],filename\n")
  imu = open(output_base + "mav0/imu0/data.csv", "w")
  imu.writelines("#timestamp [ns],w_RS_S_x [rad s^-1],w_RS_S_y [rad s^-1],w_RS_S_z [rad s^-1],a_RS_S_x [m s^-2],a_RS_S_y [m s^-2],a_RS_S_z [m s^-2]\n")
  tsl = open(output_base + "timestamps.txt", "w")

  cam_lines = []
  imu_lines = []
  timestamp_lines = []

  for i in range(len(cam_t_ns)):
    timestamp_lines.append(cam_t_ns[i]+'\n')
    cam_lines.append(cam_t_ns[i] + f", {i:08d}.png"+ '\n')

  for i in range(len(imu_t_ns)-1):
    if imu_t_d[i+1] > 0.01:
      t_start = imu_t_s[i] + .01
      while (t_start < imu_t_s[i+1]):
        imu_d_string = np.char.mod('%f', imu_d[i])
        imu_lines.append(str(t_start*1000000000) + "," + ",".join(imu_d_string) + '\n')        
        t_start += 0.01
    else:
      imu_d_string = np.char.mod('%f', imu_d[i])
      imu_lines.append(imu_t_ns[i] + "," + ",".join(imu_d_string) + '\n')

  cam.writelines(cam_lines[12:])
  imu.writelines(imu_lines)
  tsl.writelines(timestamp_lines[12:])

  cam.close()
  imu.close()
  tsl.close()

  if len(os.listdir(output_base + "mav0/cam0/data")) < 1:
    shutil.copytree(f"{output_base}mav0/cam0", f"{output_base}mav0/cam1")

    os.system(f"""ffmpeg -hide_banner -loglevel error -hwaccel auto -f rawvideo -pixel_format yuv420p -video_size 1472x1088 -framerate 60 -i {root+path}video.yuv -filter:v "crop=1456:1088:0:0" {output_base+"mav0/cam0/data/"}%8d.png""")
    mapping = open(output_base + "mav0/cam0/data.csv")
    mapping_lines = mapping.readlines()

    for line in mapping_lines[1:]:
      tk = line.strip('\n').split(',')
      shutil.copy(output_base + f'mav0/cam0/data/{tk[1][1:]}', output_base+f"mav0/cam0/data/{tk[0]}.png")


    

