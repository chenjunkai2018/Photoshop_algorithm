import numpy as np
from skimage import data, img_as_float
import matplotlib.pyplot as plt
from skimage import io
import math

file_name='D:/Image Processing/PS Algorithm/2.jpg';
img=io.imread(file_name)

file_name2='D:/Image Processing/PS Algorithm/3.jpg'
img2=io.imread(file_name2)

img3 = img_as_float(img2)

img3 = abs(img3 -1)

half_size = 10

r_img=img2[:,:,0];
g_img=img2[:,:,1];
b_img=img2[:,:,2];

row, col = r_img.shape

# img3=img2*0.5+img*0.5;

# img3=img/255.0;

plt.figure(1)
plt.imshow(img3)
plt.axis('off')

plt.figure(2)
plt.imshow(r_img, plt.cm.gray)
plt.axis('off')

plt.figure(3)
plt.imshow(g_img, plt.cm.gray)
plt.axis('off')

plt.figure(4)
plt.imshow(b_img, plt.cm.gray)
plt.axis('off')

row, col, channel=img.shape

print ("red channel", r_img.dtype, r_img.shape)

print ("green channel", g_img.dtype, g_img.shape)

print ("blue channel", g_img.dtype, b_img.shape)

# print (r_img.shape, row, col, channel)
# print (img3.min(), img3.max(), img3.mean())

plt.show()
