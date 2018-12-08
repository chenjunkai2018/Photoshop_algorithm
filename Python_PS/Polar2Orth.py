
import matplotlib.pyplot as plt
from skimage import io
import numpy as np
import numpy.matlib
import math

file_name='D:/Image Processing/PS Algorithm/4.jpg';
img=io.imread(file_name)

row, col, channel = img.shape

img = img * 1.0

center_x = (col-1)/2.0
center_y = (row-1)/2.0

xx = np.arange (col) 
yy = np.arange (row)

e = col*1.0/row
R = row/2.0
a = col/2.0
b = R

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

R1 = y_mask * R / row
R2 = R1 * e
theta = x_mask * 2 * math.pi / col

y1_mask = center_y - R1 * np.sin(theta)
x1_mask = center_x + R2 * np.cos(theta)

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
#        p = p_mask[ii, jj]    
#        q = q_mask[ii, jj] 
        
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