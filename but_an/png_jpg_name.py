import numpy as np
import os
import subprocess
import shutil


mapping = open("data.csv")
mapping_lines = mapping.readlines()



for line in mapping_lines:
  tk = line.strip('\n').split(',')

  # os.system(f'copy E:/butler_vid/{tk[0]} E:/butler_vio/{tk[1]}.png')
  shutil.copy(f'E:/butler_vid/{tk[1]}', f'E:/butler_vio/{tk[0]}.png')
  # print(f'copy E:/butler_vid/{tk[1]} E:/butler_vio/{tk[0]}.png')

