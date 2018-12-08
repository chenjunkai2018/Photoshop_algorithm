import matplotlib.pyplot as plt
from skimage import io
import numpy as np
import numpy.matlib

file_name='D:/Visual Effects/PS Algorithm/1.jpg';
img=io.imread(file_name)

def Sur_blur ( I_in, thre, half_size):
    I_out = I_in * 1.0
    row, col = I_in.shape
    w_size = half_size * 2 + 1
    for ii in range (half_size, row-1-half_size):
        for jj in range (half_size, col-1-half_size):
            aa = I_in [ii-half_size:ii+half_size+1, jj-half_size : jj+half_size+1]
            p0 = I_in [ii, jj]
            mask_1 = numpy.matlib.repmat(p0, w_size, w_size)
            mask_2 = 1-abs(aa-mask_1)/(2.5*thre);
            mask_3 = mask_2 * (mask_2 > 0)
            t1 = aa * mask_3
            I_out[ii, jj] = t1.sum()/mask_3.sum()
    
    return I_out

img_out = img * 1.0
thre = 20
half_size =10 
img_out[:, :, 0] = Sur_blur (img[:, :, 0], thre, half_size)
img_out[:, :, 1] = Sur_blur (img[:, :, 1], thre, half_size)
img_out[:, :, 2] = Sur_blur (img[:, :, 2], thre, half_size)
            
img_out = img_out/255

plt.figure(1)
plt.imshow(img)
plt.axis('off')

plt.figure(2)
plt.imshow(img_out)
plt.axis('off')

plt.show()


