import numpy as np
import os
import subprocess
import shutil


target  = "C:/Users/aaren/Desktop/data/out/set489/"

mapping = open(target + "mav0/cam0/data.csv")
mapping_lines = mapping.readlines()



for line in mapping_lines[1:]:
  tk = line.strip('\n').split(',')
  shutil.copy(target + f'mav0/cam0/data/{tk[1][1:]}', target+f"mav0/cam0/data/{tk[0]}.png")

