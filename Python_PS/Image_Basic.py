import matplotlib.pyplot as plt
from skimage import io
import numpy as np

file_name='D:/Image Processing/PS Algorithm/2.jpg';
img_1=io.imread(file_name)
img_1 = img_1/255.0

file_name2='D:/Image Processing/PS Algorithm/3.jpg'
img_2=io.imread(file_name2)
img_2 = img_2/255.0


zero_mask = np.zeros(img_1.shape)
one_mask = np.ones(img_1.shape)

img = 1 - (1 - img_2) / (img_1 + 0.001)
    
mask_1 = img  < 0 
mask_2 = img  > 1

img = img * (1-mask_1)
img = img * (1-mask_2) + mask_2

# get the r,g,b channels
r_img=img_1[:,:,0];
g_img=img_1[:,:,1];
b_img=img_1[:,:,2];
             
# show the images
plt.figure(1)
plt.imshow(img)
plt.axis('off');

plt.figure(2)
plt.imshow(r_img, plt.cm.gray)
plt.axis('off');

plt.figure(3)
plt.imshow(g_img, plt.cm.gray)
plt.axis('off');

plt.figure(4)
plt.imshow(b_img, plt.cm.gray)
plt.axis('off');

row, col, channel=img.shape;

print "red channel", r_img.dtype, r_img.shape

print "green channel", g_img.dtype, g_img.shape

print "blue channel", g_img.dtype, b_img.shape

print row, col, channel

print img.min(), img.max(), img.mean()

plt.show();




