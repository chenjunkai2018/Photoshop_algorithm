from skimage import img_as_float
import matplotlib.pyplot as plt
from skimage import io
import random
import numpy as np

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

img = img_as_float(img)

img_out = img.copy()

row, col, channel = img.shape

half_patch =10

for i in range(half_patch, row-1-half_patch, half_patch):
    for j in range (half_patch, col-1-half_patch, half_patch):
        k1 = random.random() - 0.5
        k2 = random.random() - 0.5
        m=np.floor(k1*(half_patch*2 + 1))
        n=np.floor(k2*(half_patch*2 + 1))
        h=int((i+m) % row)
        w=int((j+n) % col)
        
        img_out[i-half_patch:i+half_patch, j-half_patch:j+half_patch, :] =\
                        img[h, w, :]


plt.figure(1)
plt.imshow(img)
plt.axis('off')

plt.figure(2)
plt.imshow(img_out)
plt.axis('off')

plt.show()


