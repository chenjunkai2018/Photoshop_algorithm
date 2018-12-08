# -*- coding: utf-8 -*-
"""
Created on Sun Aug 20 08:31:04 2017

@author: shiyi
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.misc import imsave, imread
from skimage.segmentation import slic
import numpy.matlib
import random

file_name='D:/Visual Effects/PS Algorithm/9.jpg';
img=imread(file_name)

row, col, channel = img.shape

# define the colormap

color_map = img.copy()

rNW = 0.5
rNE = 1.0     
rSW = 0.0
rSE = 0.5     

gNW = 0.0
gNE = 0.5
gSW = 0.0
gSE = 1.0

bNW = 1.0
bNE = 0.0
bSW = 0.5
bSE = 0.0

xx = np.arange (col) 
yy = np.arange (row)

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

fx = x_mask * 1.0 / col
fy = y_mask * 1.0 / row

p = rNW + (rNE - rNW) * fx
q = rSW + (rSE - rSW) * fx
r = ( p + (q - p) * fy )
r[r<0] = 0
r[r>1] =1

p = gNW + (gNE - gNW) * fx
q = gSW + (gSE - gSW) * fx
g = ( p + (q - p) * fy )
g[g<0] = 0
g[g>1] =1

p = bNW + (bNE - bNW) * fx
q = bSW + (bSE - bSW) * fx
b = ( p + (q - p) * fy )
b[b<0] = 0.0
b[b>1] = 1.0

color_map[:, :, 0] = r * 255
color_map[:, :, 1] = g * 255
color_map[:, :, 2] = b * 255
         
# segment the image
   
N_block = 100
segments = slic(img, n_segments=N_block, compactness=10)
# plt.imshow(segments, plt.cm.gray)

seg_img = img.copy()
T_mask = img.copy()
 
for i in range(N_block):
    mask = (segments == i)
    T_mask[:, :, 0] = mask
    T_mask[:, :, 1] = mask
    T_mask[:, :, 2] = mask
    x_ind = int(random.random() * (col-1))
    y_ind = int(random.random() * (row-1))
    color = color_map[y_ind, x_ind, :]
    T_img = seg_img * T_mask 
    T_img = color
    seg_img = seg_img * (1-T_mask) + T_img * T_mask

imsave('out.jpg', seg_img)

plt.figure(2)
plt.imshow(seg_img)
plt.show()

    