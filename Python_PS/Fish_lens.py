import numpy as np
from skimage import img_as_float
import matplotlib.pyplot as plt
from skimage import io
import math
import numpy.matlib

file_name2='D:/Visual Effects/PS Algorithm/4.jpg'
img=io.imread(file_name2)

img = img_as_float(img)

row, col, channel = img.shape

img_out = img * 1.0

R=(min(row, col)/2)

# gamma > 1 zoom in  gamma < 1 zoom out
gamma = 1.5

center_x = (col-1)/2.0
center_y = (row-1)/2.0

xx = np.arange (col) 
yy = np.arange (row)

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

xx_dif = x_mask - center_x
yy_dif = center_y - y_mask

r = np.sqrt(xx_dif * xx_dif + yy_dif * yy_dif)

theta = np.arctan(yy_dif / xx_dif)

mask_1 = xx_dif < 0
theta = theta * (1 - mask_1) + (theta + math.pi) * mask_1

r_new = R*np.power(r/R, gamma)

x_new = r_new * np.cos(theta) + center_x
y_new = center_y - r_new * np.sin(theta) 

int_x = np.floor (x_new)
int_x = int_x.astype(int)
int_y = np.floor (y_new)
int_y = int_y.astype(int)

for ii in range(row):
    for jj in range (col):
        new_xx = int_x [ii, jj]
        new_yy = int_y [ii, jj]
        
        if x_new [ii, jj] < 0 or x_new [ii, jj] > col -1 :
            continue
        if y_new [ii, jj] < 0 or y_new [ii, jj] > row -1 :
            continue

        img_out[ii, jj, :] = img[new_yy, new_xx, :]


plt.figure (1)
plt.imshow (img)
plt.axis('off')

plt.figure (2)
plt.imshow (img_out)
plt.axis('off')

plt.show()