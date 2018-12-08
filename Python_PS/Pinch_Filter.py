
import matplotlib.pyplot as plt
from skimage import io
import numpy as np
import numpy.matlib
import math

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

row, col, channel = img.shape

img = img * 1.0/255.0

angle = math.pi/3
centreX = 0.25
centreY = 0.25
radius= 300
amount= 0.75

center_x = col * centreX
center_y = row * centreY

radius_2 = radius * radius

xx = np.arange (col) 
yy = np.arange (row)

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

xx_dif = x_mask - center_x
yy_dif = y_mask - center_y

distance = xx_dif * xx_dif + yy_dif * yy_dif
mask = distance > radius_2
distance = distance * (1 - mask) + (distance * 0 + radius_2) * mask
d = np.sqrt(distance / radius_2)
t = np.sin(math.pi * 0.5 * d) + 0.0001 
t = np.power(t, -amount)
dx = xx_dif * t
dy = yy_dif * t
e = 1 - d 
a = angle * e * e
s = np.sin(a)
c = np.cos(a)

x1_mask = center_x + c * dx - s * dy
y1_mask = center_y + s * dx + c * dy

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

print (x1_mask.min(),  x1_mask.max())
print (y1_mask.min(),  y1_mask.max())
print (int_x.min(), int_x.max())
print (int_y.min(), int_y.max())

img_out = img * 1.0

for ii in range(row):
    for jj in range (col):
        new_xx = int_x [ii, jj]
        new_yy = int_y [ii, jj]
       
        img_out[ii, jj, :] = img[new_yy, new_xx, :]


plt.figure (1)
plt.imshow (img)
plt.axis('off')

plt.figure (2)
plt.imshow (img_out)
plt.axis('off')

plt.show()