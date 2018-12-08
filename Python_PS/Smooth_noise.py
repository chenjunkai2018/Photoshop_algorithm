import numpy as np
import matplotlib.pyplot as plt
from skimage import io
import math
import numpy.matlib

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

row, col, channel=img.shape
base_noise = np.random.randn(row, col)

octave = 4.0

samplePeriod = math.pow(2, octave)
sampleFrequency = 1.0 / samplePeriod

xx = np.arange(col)
yy = np.arange(row)

x_mask = numpy.matlib.repmat(xx, row, 1)
y_mask = numpy.matlib.repmat(yy, col, 1)
y_mask = np.transpose(y_mask)

y0 = np.floor(y_mask * 1.0 / samplePeriod) * samplePeriod
y1 = np.mod(y0 + samplePeriod, row)
v_blend = (y_mask - y0) * sampleFrequency

x0 = np.floor(x_mask * 1.0 / samplePeriod) * samplePeriod
x1 = np.mod(x0 + samplePeriod, col)
h_blend = (x_mask - x0) * sampleFrequency

int_x0 = x0.astype(int)
int_x1 = x1.astype(int)
int_y0 = y0.astype(int)
int_y1 = y1.astype(int)

sm_noise = np.zeros((row, col))
top = np.zeros((row, col))
bottom = np.zeros((row, col))

for ii in range(row):
    for jj in range (col):
        
        s_i0 = int_y0 [ii, jj]
        s_i1 = int_y1 [ii, jj]
        s_j0 = int_x0 [ii, jj]
        s_j1 = int_x1 [ii, jj]
        
        v_alpha = v_blend [ii, jj]
        h_alpha = h_blend [ii, jj]
        
        top [ii, jj] = (1.0 - h_alpha) * base_noise[s_i0, s_j0] 
        + h_alpha * base_noise[s_i0, s_j1] 
        bottom [ii, jj] = (1.0 - h_alpha) * base_noise[s_i1, s_j0]
        + h_alpha * base_noise[s_i1, s_j1]
        sm_noise[ii, jj] = (1.0 - v_alpha) * top [ii, jj] 
        + v_alpha * bottom [ii, jj]

'''
mask = sm_noise < 0 
sm_noise = sm_noise * (1 - mask)
mask = sm_noise > 1
sm_noise = sm_noise * (1 - mask) + ( sm_noise * 0 + 1 ) * mask
'''

plt.figure(1)
plt.imshow(sm_noise, plt.cm.gray)
plt.axis('off')

plt.figure(2)
plt.imshow(base_noise, plt.cm.gray)
plt.axis('off')

plt.figure(3)
plt.imshow(top, plt.cm.gray)
plt.axis('off')

plt.figure(4)
plt.imshow(bottom, plt.cm.gray)
plt.axis('off')

plt.show()
