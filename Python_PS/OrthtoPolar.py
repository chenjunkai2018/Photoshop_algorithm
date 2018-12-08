# -*- coding: utf-8 -*-
"""
Created on Fri Apr 21 07:06:55 2017

@author: shiyi
"""

import matplotlib.pyplot as plt
from skimage import io
import numpy as np
import numpy.matlib

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

row, col, channel = img.shape

img = img * 1.0

center_x = (col-1)/2.0
center_y = (row-1)/2.0

xx = np.arange (col) 
yy = np.arange (row)

e = col*1.0/row

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

xx_dif = x_mask - center_x
yy_dif = center_y - y_mask

theta = np.arctan2(yy_dif*e, xx_dif+0.0001) 

mask_1 = yy_dif < 0

theta = theta * (1 - mask_1) + (theta + 3.1415 * 2) * mask_1

r1 = yy_dif / np.sin(theta)
y1_mask = r1 * 2.0
x1_mask = theta * col / (2 * 3.1415)

# mask = (x1_mask > 0) * (x1_mask < 1) 
# x1_mask = x1_mask * (1 - mask )  + ( x1_mask * mask + 1 ) * mask

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

p_mask = x1_mask - int_x
q_mask = y1_mask - int_y

img_out = img * 1.0

for ii in range(row):
    for jj in range (col):
        new_xx = int_x [ii, jj]
        new_yy = int_y [ii, jj]
        p = p_mask[ii, jj]    
        q = q_mask[ii, jj] 
        
        img_out[ii, jj, :] = img[new_yy, new_xx, :]


'''
        img_out[ii, jj, :] = (1-p)*(1-q)*img[new_yy, new_xx, :] 
        + p*(1-q)*img[new_yy, new_xx+1, :]
        + q*(1-p)*img[new_yy+1, new_xx, :] 
        + p*q*img[new_yy+1, new_xx+1, :]  
'''
        
img_out = img_out / 255.0                

plt.figure (1)
plt.imshow (img/255.0)
plt.axis('off')

plt.figure (2)
plt.imshow (img_out)
plt.axis('off')

plt.show()