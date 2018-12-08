# -*- coding: utf-8 -*-
"""
Created on Fri Apr 21 07:06:55 2017

@author: shiyi
"""

import matplotlib.pyplot as plt
from skimage import io
import math

file_name='D:/Image Processing/PS Algorithm/4.jpg';
img=io.imread(file_name)

height, width, channel = img.shape

img = img * 1.0

center_x = (width-1)/2.0
center_y = (height-1)/2.0

e = width*1.0/height

img_out = img * 1.0

for ii in range(height):
    for jj in range (width):
        xx_dif = jj - center_x
        yy_dif = center_y - ii
        theta = math.atan2 (yy_dif*e, xx_dif+0.0001) 
        
        if yy_dif < 0:
            theta = theta + 2 * math.pi
        
        R1=(center_y-ii)/math.sin(theta)
        new_y=R1*2
        new_x=theta*width/(2*math.pi)
        
  #      new_x = max(new_x, 0)
        new_x = min(new_x, width-2)
  #      new_y = max(new_y, 0)
        new_y = min(new_y, height-2)
        
        int_x = math.floor(new_x)
        int_y = math.floor(new_y)
        
        int_x = int(int_x)
        int_y = int(int_y)
        
#        p = new_x - int_x
#        q = new_y - int_y
        
#        img_out[ii, jj, :] = img[int_y, int_x, :]

        p = 0.5
        q = 0.5

        img_out[ii, jj, :] = (1-p)*(1-q)*img[int_y, int_x, :] 
        + p*(1-q)*img[int_y, int_x+1, :]
        + q*(1-p)*img[int_y+1, int_x, :] 
        + p*q*img[int_y+1, int_x+1, :]        

          
img_out = img_out / 255.0                

plt.figure (1)
plt.imshow (img/255.0)
plt.axis('off')

plt.figure (2)
plt.imshow (img_out)
plt.axis('off')

plt.show()