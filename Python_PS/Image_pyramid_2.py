# -*- coding: utf-8 -*-
"""
Created on Mon Jan 22 22:43:18 2018

@author: shiyi
"""

import cv2
import numpy as np
import matplotlib.pyplot as plt

A = cv2.imread('D:/Python_Code/Test_img/2.jpg')

row, col, dpt = A.shape

pyr_level = 4

# generate Gaussian pyramid for A
G = A.copy()
gpA = [G]
for i in range(pyr_level):
    G = cv2.pyrDown(G)
    gpA.append(G)

G = np.zeros([row, col, dpt], dtype='uint8')

rowX2 = row // 2
colX2 = col // 2
G[:rowX2, :colX2, :] = gpA[1]

rowX4 = rowX2 // 2
colX4 = colX2 // 2
G[rowX2:rowX2+rowX4, colX2:colX2+colX4, :] = gpA[2]
G[:rowX4, colX2:colX2+colX4, :] = gpA[2]

rowX8 = rowX4 // 2
colX8 = colX4 // 2
G[rowX2+rowX4:rowX2+rowX4+rowX8, colX2+colX4:colX2+colX4+colX8, :] = gpA[3]
G[ :rowX8, colX2+colX4:colX2+colX4+colX8, :] = gpA[3]

cv2.imshow("gau_pyr", G)

cv2.imwrite("gau_pyr.jpg", G)


    

