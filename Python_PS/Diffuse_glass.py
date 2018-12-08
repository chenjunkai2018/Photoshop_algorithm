# -*- coding: utf-8 -*-
"""
Created on Sun Aug 20 11:03:53 2017

@author: shiyi
"""

import matplotlib.pyplot as plt
from skimage.filters import gaussian
from scipy.misc import imsave, imread
import random

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=imread(file_name)

g_img = gaussian(img, sigma=2, multichannel=True)

img_out = g_img.copy()

rows, cols, dpt = img.shape

p_size = 3

for i in range(p_size, rows-p_size, 1):
    for j in range(p_size, cols-p_size, 1):
        k1= random.random() - 0.5
        k2= random.random() - 0.5
        m=int (k1*(p_size*2-1)) 
        n=int (k2*(p_size*2-1))
        h=(i+m) % rows 
        w=(j+n) % cols  
        img_out[i, j, :] = g_img[h, w, :]

imsave('out.jpg', img_out)

plt.figure
plt.imshow(img_out)
plt.show()