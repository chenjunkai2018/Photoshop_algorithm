from skimage import img_as_float
import matplotlib.pyplot as plt
from skimage import io
import numpy as np
import numpy.matlib

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

img = img_as_float(img)

img_out = img.copy()

row, col, channel = img.shape

xx = np.arange (col) 
yy = np.arange (row)

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

center_y = (row -1) / 2.0
center_x = (col -1) / 2.0

R = np.sqrt((x_mask - center_x) **2 + (y_mask - center_y) ** 2)

angle = np.arctan2(y_mask - center_y , x_mask - center_x)

Num = 20
arr = np.arange(Num)

for i in range (row):
    for j in range (col):
       
        R_arr = R[i, j] - arr   
        R_arr[R_arr < 0] = 0
        
        new_x = R_arr * np.cos(angle[i,j]) + center_x
        new_y = R_arr * np.sin(angle[i,j]) + center_y
        
        int_x = new_x.astype(int)
        int_y = new_y.astype(int)
        
        int_x[int_x > col-1] = col - 1
        int_x[int_x < 0] = 0
        int_y[int_y < 0] = 0
        int_y[int_y > row -1] = row -1
        
        img_out[i,j,0] = img[int_y, int_x, 0].sum()/Num
        img_out[i,j,1] = img[int_y, int_x, 1].sum()/Num
        img_out[i,j,2] = img[int_y, int_x, 2].sum()/Num
        

plt.figure(1)
plt.imshow(img)
plt.axis('off')

plt.figure(2)
plt.imshow(img_out)
plt.axis('off')

plt.show()

