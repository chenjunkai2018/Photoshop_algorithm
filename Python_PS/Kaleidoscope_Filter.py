# -*- coding: utf-8 -*-
"""
Created on Fri Apr 21 07:06:55 2017

@author: shiyi
"""

import matplotlib.pyplot as plt
from skimage import io
from skimage import img_as_float
import numpy as np
import numpy.matlib
import math

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

img = img_as_float(img)

row, col, channel = img.shape

# set the parameters
radius = 100.0
angle = math.pi/3
angle2 = math.pi/4
sides = 10.0
# set the center of the circle, proportion of the image size
centerX = 0.5     
centerY = 0.5

iWidth=col
iHeight=row

center_x=iWidth*centerX
center_y=iHeight*centerY

xx = np.arange (col) 
yy = np.arange (row)

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

xx_dif = x_mask - center_x
yy_dif = y_mask - center_y

r = np.sqrt(xx_dif * xx_dif + yy_dif * yy_dif)
theta = np.arctan2(yy_dif, xx_dif+0.0001) - angle - angle2
temp_theta=theta/math.pi*sides*0.5
temp_r = np.mod(temp_theta, 1.0)
mask_1 = temp_r < 0.5
theta = temp_r * 2 * mask_1 + (1-temp_r) * 2 * (1 - mask_1)

radius_c=radius/np.cos(theta)

temp_r = np.mod (r/radius_c, 1.0)
mask_1 = temp_r < 0.5
r = radius_c * (temp_r * 2 * mask_1 + (1-temp_r) * 2 * (1 - mask_1))

theta = theta + angle

x1_mask = r * np.cos(theta) + center_x
y1_mask = r * np.sin(theta) + center_y

mask = x1_mask < 0  
x1_mask = x1_mask * (1 - mask) 
mask = x1_mask > (col - 1) 
x1_mask = x1_mask * (1 - mask) + (x1_mask * 0 + col -2) * mask

mask = y1_mask < 0
y1_mask = y1_mask * (1 - mask)
mask = y1_mask > (row -1)
y1_mask = y1_mask * (1 - mask) + (y1_mask * 0 + row -2) * mask

img_out = img * 1.0

int_x = np.floor (x1_mask)
int_x = int_x.astype(int)
int_y = np.floor (y1_mask)
int_y = int_y.astype(int)

p_mask = x1_mask - int_x
q_mask = y1_mask - int_y

img_out = img * 1.0

for ii in range(row):
    for jj in range (col):
        new_xx = int_x [ii, jj]
        new_yy = int_y [ii, jj]
#        p = p_mask[ii, jj]    
#        q = q_mask[ii, jj] 
        
        img_out[ii, jj, :] = img[new_yy, new_xx, :]


plt.figure (1)
plt.imshow (img)
plt.axis('off')

plt.figure (2)
plt.imshow (img_out)
plt.axis('off')

plt.show()