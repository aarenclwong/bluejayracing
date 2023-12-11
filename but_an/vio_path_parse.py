import matplotlib.pyplot as plt
from datetime import time, timedelta
import numpy as np
import os
import shutil

imu_file = "OHI_imu_0_000"
gps_file = "OHI_gps_0_000"
cam_file = "timestamps.txt"
params_ = "OHI_parameters_0"
root = "C:/Users/aaren/Desktop/data/"
paths = os.listdir(root)
paths = [path+"/" for path in paths]
# paths = ["1701833093968/", "1701836195175/"]

output = "out/"


for path in paths:
  imu_t_s = []
  imu_d = []
  with open(root + path + imu_file) as f:
    file_lines = f.readlines()
    for line in file_lines:
      values = line.split(',')
      if len(values) == 8:
        t = float(values[0])
        imu_t_s.append(t)
        gyros = [float(values[4])*0.0174533,float(values[3])*0.0174533,float(values[2])*0.0174533]
        accels = [float(values[7])*9.81,float(values[6])*9.81,float(values[5])*9.81]
        imu_d.append(gyros + accels)

  cam_t_ms = []
  with open(root + path + cam_file) as f:
    file_lines = f.readlines()

    for line in file_lines[1:]:
      cam_t_ms.append(float(line))

  cam_t_ns = np.array(cam_t_ms[1:]) * 1000000
  imu_t_ns = np.array(imu_t_s) * 1000000000

  cam_t_ns = np.char.mod('%d', cam_t_ns)
  imu_t_ns = np.char.mod('%d', imu_t_ns)

  output_base = root + path + output

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

  cam_lines = []
  imu_lines = []

  for i in range(len(cam_t_ns)):
    cam_lines.append(cam_t_ns[i] + f", {i:08d}.jpg"+ '\n')

  for i in range(len(imu_t_ns)):
    imu_d_string = np.char.mod('%f', imu_d[i])
    imu_lines.append(imu_t_ns[i] + "," + ",".join(imu_d_string) + '\n')

  cam.writelines(cam_lines[12:])
  imu.writelines(imu_lines)

  cam.close()
  imu.close()

  if len(os.listdir(output_base + "mav0/cam0/data")) < 1:

    os.system(f"""ffmpeg -hide_banner -loglevel error -hwaccel auto -f rawvideo -pixel_format yuv420p -video_size 1472x1088 -framerate 60 -i {root+path}video.yuv -filter:v "crop=1456:1088:0:0" {output_base+"mav0/cam0/data/"}%8d.png""")
    shutil.copytree(f"{output_base}mav0/cam0", f"{output_base}mav0/cam1")

