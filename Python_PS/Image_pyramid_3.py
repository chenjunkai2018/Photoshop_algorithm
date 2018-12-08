# -*- coding: utf-8 -*-
"""
Created on Mon Jan 22 22:43:18 2018

@author: shiyi
"""

import cv2
import numpy as np

A = cv2.imread('D:/Python_Code/Test_img/2.jpg')

row, col, dpt = A.shape

Mask = A.copy()
Mask = Mask * 0.0;

R = max(row, col) / 2;

a = range(col)
xx = np.matlib.repmat(a, row, 1)

a = range(row)
yy = np.matlib.repmat(a, col, 1)
yy = np.transpose(yy)
    
center_x = col / 2
center_y = row / 2

dif_xx = xx - center_x
dif_yy = yy - center_y

Sqrt_ = dif_xx * dif_xx + dif_yy * dif_yy

mask_ = Sqrt_ < (R*R)

Mask [:, :, 0] = mask_
Mask [:, :, 1] = mask_
Mask [:, :, 2] = mask_

cv2.imwrite("mask.jpg", Mask)

A = cv2.imread('D:/Python_Code/Test_img/2.jpg')
B = cv2.imread('D:/Python_Code/Test_img/3.jpg')

pyr_level = 4

# generate Gaussian pyramid for mask
G = Mask.copy()
gpM = [G]
for i in range(pyr_level):
    G = cv2.pyrDown(G)
    gpM.append(G)

# generate Gaussian pyramid for A
G = A.copy()
gpA = [G]
for i in range(pyr_level):
    G = cv2.pyrDown(G)
    gpA.append(G)

# generate Gaussian pyramid for B
G = B.copy()
gpB = [G]
for i in range(pyr_level):
    G = cv2.pyrDown(G)
    gpB.append(G)

# generate Laplacian Pyramid for A
lpA = [gpA[pyr_level -1 ]]
for i in range(pyr_level - 1,0,-1):
    GE = cv2.pyrUp(gpA[i])
    L = cv2.subtract(gpA[i-1],GE)
    lpA.append(L)

# generate Laplacian Pyramid for B
lpB = [gpB[pyr_level -1 ]]
for i in range(pyr_level - 1,0,-1):
    GE = cv2.pyrUp(gpB[i])
    L = cv2.subtract(gpB[i-1],GE)
    lpB.append(L)

# Now add left and right halves of images in each level
LS = []
ind = pyr_level - 1 
for la,lb in zip(lpA,lpB):
    rows,cols,dpt = la.shape
    ls = la * gpM[ind] + lb * (1 - gpM[ind])
    ind = ind - 1
    LS.append(ls)

# now reconstruct
ls_ = LS[0]
for i in range(1, pyr_level):
    ls_ = cv2.pyrUp(ls_)
    ls_ = cv2.add(ls_, LS[i])
    
cv2.imwrite("img_out.jpg", ls_)