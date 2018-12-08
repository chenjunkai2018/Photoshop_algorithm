import numpy as np
import matplotlib.pyplot as plt
from skimage import io

file_name='D:/Image Processing/PS Algorithm/4.jpg';
img=io.imread(file_name)

img = img * 1.0

Color_ratio = np.zeros(6)

Color_ratio[0]=0.4;     # Red
Color_ratio[1]=0.6;     # Yellow
Color_ratio[2]=0.4;     # Green
Color_ratio[3]=0.6;     # Cyan
Color_ratio[4]=0.2;     # Blue
Color_ratio[5]=0.8;     # Magenta

max_val = img.max(axis = 2)
min_val = img.min(axis = 2)
sum_val = img.sum(axis = 2)
mid_val = sum_val - max_val - min_val

mask_r = (img[:, :, 0] - min_val - 0.01) > 0 
mask_r = 1 - mask_r
mask_g = (img[:, :, 1] - min_val - 0.01) > 0
mask_g = 1 - mask_g
mask_b = (img[:, :, 2] - min_val - 0.01) > 0
mask_b = 1 - mask_b

ratio_max_mid = mask_r * Color_ratio[3] + mask_g * Color_ratio[5] + mask_b * Color_ratio[1]

mask_r = (img[:, :, 0] - max_val + 0.01) < 0
mask_r = 1 - mask_r

mask_g = (img[:, :, 1] - max_val + 0.01) < 0
mask_g = 1 - mask_g

mask_b = (img[:, :, 2] - max_val + 0.01) < 0
mask_b = 1 - mask_b

ratio_max= mask_r * Color_ratio[4] + mask_g * Color_ratio[0] + mask_b * Color_ratio[2]

I_out = max_val * 1.0 

I_out = (max_val-mid_val)*ratio_max + (mid_val-min_val)*ratio_max_mid + min_val 

plt.figure()
plt.imshow(img/255.0)
plt.axis('off')

plt.figure(2)
plt.imshow(I_out/255.0, plt.cm.gray)
plt.axis('off')

plt.show()              
