import numpy as np
from skimage import img_as_float
import matplotlib.pyplot as plt
from skimage import io
import math
import numpy.matlib


file_name2='D:/Visual Effects/PS Algorithm/4.jpg'
img=io.imread(file_name2)

img = img_as_float(img)

# control the radius of the inner circle
radius = 150      
# control the distance between the inner circle and outer circle
high = 200       
angle = 0           
spreadAngle = math.pi  
# set the center of the circle, proportion of the image size  
centerX = 0.5
centerY = 1.0

row, col, channel = img.shape

icenterX = col * centerX
icenterY = row * centerY

img_out = img * 0 

xx = np.arange (col) 
yy = np.arange (row)

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

xx_dif = x_mask - icenterX
yy_dif = y_mask - icenterY 

theta = np.arctan2(-yy_dif, -xx_dif+0.0001) 

r = np.sqrt(xx_dif*xx_dif + yy_dif * yy_dif)

theta = np.mod(theta, 2 * math.pi)

x1_mask = col * theta/(spreadAngle+0.00001)
y1_mask = row * (1-(r-radius)/(high+0.00001))

'''
mask = x1_mask < 0  
x1_mask = x1_mask * (1 - mask) 
mask = x1_mask > (col - 1) 
x1_mask = x1_mask * (1 - mask) + (x1_mask * 0 + col -2) * mask

mask = y1_mask < 0
y1_mask = y1_mask * (1 - mask)
mask = y1_mask > (row -1)
y1_mask = y1_mask * (1 - mask) + (y1_mask * 0 + row -2) * mask
'''

int_x = np.floor (x1_mask)
int_x = int_x.astype(int)
int_y = np.floor (y1_mask)
int_y = int_y.astype(int)

for ii in range(row):
    for jj in range (col):
        new_xx = int_x [ii, jj]
        new_yy = int_y [ii, jj]
        
        if x1_mask [ii, jj] < 0 or x1_mask [ii, jj] > col -1 :
            continue
        if y1_mask [ii, jj] < 0 or y1_mask [ii, jj] > row -1 :
            continue

        img_out[ii, jj, :] = img[new_yy, new_xx, :]

plt.figure (1)
plt.imshow (img)
plt.axis('off')

plt.figure (2)
plt.imshow (img_out)
plt.axis('off')

plt.show()