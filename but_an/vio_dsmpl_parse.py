import matplotlib.pyplot as plt
from datetime import time, timedelta
import numpy as np

VIDEO_START = timedelta(hours=13, minutes=10, seconds=34)
IMU_START = timedelta(hours=13, minutes=10, seconds=45, microseconds=407566)

FPS = 59

FRAME_TIME = timedelta(microseconds=1000000 // FPS)

DATA_PATH = "../../BUTLER/"

FRAME_FILENAME = "butler_comp"

IMU_FILENAME = "BUT_imu_0_"

frames = 0

race_start_t_f = 84524
race_end_t_f = 138654

first_frame = (IMU_START - VIDEO_START) // FRAME_TIME
frames += first_frame
frames = race_start_t_f



race_start_t_s = ((frames-first_frame)*FRAME_TIME).seconds


imu_t = []
imu_d = []

for i in range(0,9,1):
    num = ""

    if (i > 9):
      num = "0" + str(i)
    else:
       num = "00" + str(i)

    imu_file = open(DATA_PATH+IMU_FILENAME+num)
    file_lines = imu_file.readlines()

    for line in file_lines:
      values = line.split(',')
      t = float(values[0])
      if t > race_start_t_s:
        imu_t.append(t)
        gyros = [float(values[4])*0.0174533,float(values[3])*0.0174533,float(values[2])*0.0174533]
        accels = [float(values[7])*9.81,float(values[6])*9.81,float(values[5])*9.81]
        imu_d.append(gyros + accels)


cam = open("cam_data.csv", "w")
cam.writelines("#timestamp [ns],filename\n")
imu = open("imu_data.csv", "w")
imu.writelines("#timestamp [ns],w_RS_S_x [rad s^-1],w_RS_S_y [rad s^-1],w_RS_S_z [rad s^-1],a_RS_S_x [m s^-2],a_RS_S_y [m s^-2],a_RS_S_z [m s^-2]\n")

cam_lines = []
imu_lines = []

for frame in range(race_start_t_f, race_end_t_f):
  t_ns = ((frame-first_frame)*FRAME_TIME).total_seconds()*1000000000
  t_us = float(int(t_ns/1000))

  cam_lines.append(f"{int(t_ns)}, {t_us}.png\n")

for i in range(len(imu_t)):
   t_ns = imu_t[i]*1000000000
   imu_str = ""
   for d in imu_d[i]:
      imu_str+=str(d)+','
   imu_lines.append(f"{t_ns},{imu_str[:-1]}\n")

cam.writelines(cam_lines)
imu.writelines(imu_lines)

cam.close()
imu.close()
