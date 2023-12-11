import csv
from datetime import time, timedelta
import matplotlib.pyplot as plt

VIDEO_START = timedelta(hours=13, minutes=10, seconds=34)
IMU_START = timedelta(hours=13, minutes=10, seconds=45, microseconds=407566)

FPS = 59
FRAME_TIME = timedelta(microseconds=1000000 // FPS)

DATA_PATH = "../../BUTLER/"

FRAME_FILENAME = "butler_comp"

IMU_FILENAME = "BUT_imu_0_"

frames = 0
first_frame = (IMU_START - VIDEO_START) // FRAME_TIME
print(first_frame)
frames += first_frame
frames = 84524

fig, axs = plt.subplots()

times = []
data = []

with open('data.csv', 'w', newline='') as data_file:
    with open('sensor.csv', 'w', newline='') as sensor_file:
        data_writer = csv.writer(data_file)
        sensor_writer = csv.writer(sensor_file)

        for file_num in range(0, 9):
            with open(f"{DATA_PATH+IMU_FILENAME}{file_num:03}") as imu:
                reader = csv.reader(imu)
                i = 0
                for l in reader:
                    timestamp = (frames - first_frame) * FRAME_TIME

                    # print(timedelta(seconds=float(l[0])).total_seconds() * 1000000)
                    # print("a" + str(timestamp.microseconds))
                    if timedelta(seconds=float(l[0])).total_seconds() * 1000000 > timestamp.total_seconds() * 1000000 and frames < 138654:
                        data_writer.writerow([str(timestamp.total_seconds() * 1000000000), f"{FRAME_FILENAME}{frames:08}.png"])
                        sensor_writer.writerow([str(timestamp.total_seconds() * 1000000000)] + list(map(str, [-1*deg2rad*float(l[3]) ,deg2rad*float(l[2]) , deg2rad*float(l[4]), -9.81*float(l[6]), 9.81*float(l[5]), 9.81*float(l[7])])))
                        times.append(timestamp.total_seconds() * 1000000)
                        data.append(l[2])
                        frames += 1
                        i = 0
                    else:
                        i += 1
                        deg2rad = 0.0174533
                        if i < 10: sensor_writer.writerow([str(timestamp.total_seconds() * 1000000000 + i * 500000)] + list(map(str, [-1*deg2rad*float(l[3]) ,deg2rad*float(l[2]) , deg2rad*float(l[4]), -9.81*float(l[6]), 9.81*float(l[5]), 9.81*float(l[7])])))
