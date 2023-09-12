import matplotlib.pyplot as plt
import re
import numpy as np
import os
import time



def mag(x, y, z):
    return np.sqrt(x**2 + y**2 + z**2)

def parse(vec):
    parsed_vec = re.findall("[-+]?\d+\.*\d*[e]*\d*", vec)
    if (len(parsed_vec)!= 1):
        print(parsed_vec)
        print(vec)
    x = float(parsed_vec[0])
    return [x]


download_range = np.arange(0, 2*860)
vecs_perst = []

fig, axs = plt.subplots(2)
fig.suptitle('strain cal')
#axs[0].set_title("Strain")
#axs[1].set_title("Transformed Data")

axs[0].set_ylabel("adc _reading")

plt.ion()
plt.show()

trig = []

while True:
    os.system('scp pi@baja2.local:bluejayracing/pi/cal_pkg.txt ./')
    

    f = open("C:/Users/aaren/Desktop/bluejayracing/cal_pkg.txt", "r")
    f_lines = f.readlines()
    num = f_lines[0]
    f_lines.pop(0)
    f.close()
    
    vecs = []
    for line in f_lines:
        parsed_line = parse(line)
        vecs.append(parsed_line)
        vecs_perst.append(parsed_line)
    data = []
    for vec in vecs:
        data.append(vec[0])
    norm_data = []
    data_sum = sum(data)
    for datum in data:
        #norm_data.append(datum-(data_sum/len(data)))
        norm_data.append(datum)
    # sp = np.fft.fft(np.blackman(len(data))*norm_data)#windowing function
    # freq = np.fft.fftfreq(download_range.shape[-1])
    # freq = freq * 400
    # abs_spec = abs(sp.real) + abs(sp.imag)
    
    data_range = max(norm_data) - min(norm_data)

    # if (sum(abs_spec[0:10]) > sum(abs_spec[11:50])):
    #     trig.append(1)
    # else:
    #     trig.append(0)


    axs[0].clear()
    axs[0].set_ylim(min(norm_data)-data_range,max(norm_data)+data_range)
    print(len(download_range))
    print(np.mean(norm_data))
    #axs[0].scatter(download_range, norm_data, s=2) 
    axs[0].scatter(np.arange(0,len(norm_data)), norm_data, s=2) 
    axs[1].clear()
    #axs[1].plot(freq, abs_spec)
    #axs[1].set_xlim(-1, 200)
    # axs[2].clear()    
    # axs[2].plot(trig)

    
    fig.canvas.draw()
    fig.canvas.flush_events()

    
    
    
    #time.sleep(3)
    


