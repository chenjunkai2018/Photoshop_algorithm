import numpy as np
import matplotlib.pyplot as plt
import math
from skimage import data

img = data.moon()

rows, cols = img.shape
N = rows * cols - 1

Hist_ori = np.zeros((256, 1))
Hist_cmu = np.zeros((256, 1))

for ii in range(256):
    mask_1 = (img == ii)
    Hist_ori[ii] = np.sum(mask_1) * 1.0 / N
    if ii == 0:
        Hist_cmu[ii] = Hist_ori[ii] 
    else:
        Hist_cmu[ii] = Hist_cmu[ii-1] + Hist_ori[ii]

Hist_eq = np.zeros((256, 1))
img_out = img.copy()

for ii in range(rows):
    for jj in range(cols):
        img_out[ii, jj] = math.floor(Hist_cmu[img[ii, jj]] * 255)
        Hist_eq[img_out[ii, jj]] = Hist_eq[img_out[ii, jj]] + 1



plt.figure()
plt.axis('off')
plt.subplot(2,2,1)
plt.imshow(img, plt.cm.gray)
plt.subplot(2,2,2)
plt.imshow(img_out, plt.cm.gray)
plt.subplot(2,2,3)
plt.plot(Hist_ori)
plt.subplot(2,2,4)
plt.plot(Hist_eq*1.0/N)


plt.show()