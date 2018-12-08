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
a = row / 2.0
b = col / 2.0
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

r2 = R*R
Dis = xx_dif * xx_dif + yy_dif * yy_dif
mask = Dis > r2 
Dis = Dis * (1 - mask) + (Dis * 0 + r2) * mask
theta = np.arctan(yy_dif/(xx_dif + 0.0001))
mask_1 = xx_dif < 0
theta = theta * (1 - mask_1) + (theta + math.pi) * mask_1
radius=np.arcsin(np.sqrt(Dis)/R)*R/K
radius=(np.sqrt(Dis)-radius)*(1-alpha)+radius

x1_mask = center_x + radius * np.cos(theta)
y1_mask = center_y - radius * np.sin(theta)

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