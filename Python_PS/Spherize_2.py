# -*- coding: utf-8 -*-
"""
Created on Fri Apr 21 07:06:55 2017

@author: shiyi
"""

import matplotlib.pyplot as plt
from skimage import io
import numpy as np
import numpy.matlib
import math

file_name='D:/Image Processing/PS Algorithm/4.jpg';
img=io.imread(file_name)

row, col, channel = img.shape

img = img * 1.0/255.0

R = min(row, col)/2.0
a = col / 2.0
b = row / 2.0
e = a / b
K = math.pi/2.0
alpha = 0.5

center_x = (col-1)/2.0
center_y = (row-1)/2.0

xx = np.arange (col) 
yy = np.arange (row)

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

xx_dif = x_mask - center_x
yy_dif = center_y - y_mask

theta = np.arctan(yy_dif*e/(xx_dif + 0.0001))
mask_1 = xx_dif < 0
theta = theta * (1 - mask_1) + (theta + math.pi) * mask_1

a0 = xx_dif / np.cos (theta)
b0 = yy_dif / np.sin (theta)
mask = a0 > a 
a0 = a0 * (1 - mask) + (a0 * 0 + a) * mask
mask = b0 > b
b0 = b0 * (1 - mask) + (b0 * 0 + b) * mask

a1 = np.arcsin(a0 / a) * a / K
b1 = np.arcsin(b0 / b) * b / K

a1 = (a0 - a1) * (1 - alpha) + a1
b1 = (b0 - b1) * (1 - alpha) + b1

x1_mask = center_x + a1 * np.cos(theta)
y1_mask = center_y - b1 * np.sin(theta)

mask = x1_mask < 0  
x1_mask = x1_mask * (1 - mask) 
mask = x1_mask > (col - 1) 
x1_mask = x1_mask * (1 - mask) + (x1_mask * 0 + col -2) * mask

mask = y1_mask < 0
y1_mask = y1_mask * (1 - mask)
mask = y1_mask > (row -1)
y1_mask = y1_mask * (1 - mask) + (y1_mask * 0 + row -2) * mask

int_x = np.floor (x1_mask)
int_x = int_x.astype(int)
int_y = np.floor (y1_mask)
int_y = int_y.astype(int)

img_out = img * 1.0

for ii in range(row):
    for jj in range (col):
        
        new_xx = int_x [ii, jj]
        new_yy = int_y [ii, jj]
       
        img_out[ii, jj, :] = img[new_yy, new_xx, :]


plt.figure (1)
plt.imshow (img)
plt.axis('off')

plt.figure (2)
plt.imshow (img_out)
plt.axis('off')

plt.show()