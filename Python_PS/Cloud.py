import numpy as np
import matplotlib.pyplot as plt
from skimage import io
import math
import numpy.matlib

file_name='D:/Image Processing/PS Algorithm/4.jpg';
img=io.imread(file_name)

row, col, channel=img.shape

base_noise = np.random.randn(row, col)

def Generate_noise(base_noise, octave):
    
    samplePeriod = math.pow(2.0, octave)
    sampleFrequency = 1.0 / samplePeriod

    xx = np.arange (col) 
    yy = np.arange (row)

    x_mask = numpy.matlib.repmat (xx, row, 1)
    y_mask = numpy.matlib.repmat (yy, col, 1)
    y_mask = np.transpose(y_mask)

    y0 = np.floor (y_mask / samplePeriod) * samplePeriod
    y1 = np.mod(y0 + samplePeriod, row)
    v_blend = (y_mask - y0) * sampleFrequency

    x0 = np.floor (x_mask / samplePeriod) * samplePeriod
    x1 = np.mod (x0 + samplePeriod, col)
    h_blend = (x_mask - x0) * sampleFrequency

    int_x0 = x0.astype(int)
    int_x1 = x1.astype(int)
    int_y0 = y0.astype(int)
    int_y1 = y1.astype(int)

    sm_noise = base_noise * 1.0

    for ii in range(row):
        for jj in range (col):
            s_y0 = int_y0 [ii, jj]
            s_y1 = int_y1 [ii, jj]
            s_x0 = int_x0 [ii, jj]
            s_x1 = int_x1 [ii, jj]
            v_alpha = v_blend [ii, jj]
            h_alpha = h_blend [ii, jj]
            top = (1 - h_alpha) * base_noise[s_y0, s_x0] 
            + h_alpha * base_noise[s_y0, s_x1]
            bottom = (1 - h_alpha) * base_noise[s_y1, s_x0]
            + h_alpha * base_noise[s_y1, s_x1]
            sm_noise[ii, jj] = (1 - v_alpha) * top 
            + v_alpha * bottom
    
    return sm_noise

persistance = 0.75
totalAmplitude = 0.0
octaveCount = 8
Cloud_texture = base_noise * 0.0

for ii in range (octaveCount):
    amplitude = math.pow(persistance, octaveCount - ii)
    totalAmplitude=totalAmplitude+amplitude
    sm_noise = Generate_noise(base_noise, ii)
    Cloud_texture = Cloud_texture + sm_noise * amplitude

Cloud = Cloud_texture/totalAmplitude

        
plt.figure(1)
plt.imshow(Cloud , plt.cm.gray)
plt.axis('off');

plt.figure(2)
plt.imshow(base_noise, plt.cm.gray)
plt.axis('off');

plt.show();
