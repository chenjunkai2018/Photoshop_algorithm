import matplotlib.pyplot as plt
from skimage import io
from skimage.filters import gaussian

file_name = 'D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

img = img * 1.0
gauss_out = gaussian(img, sigma=5, multichannel=True)

# alpha 0 - 5
alpha = 1.5
img_out = (img - gauss_out) * alpha + img

img_out = img_out/255.0

# 饱和处理
mask_1 = img_out  < 0 
mask_2 = img_out  > 1

img_out = img_out * (1-mask_1)
img_out = img_out * (1-mask_2) + mask_2

plt.figure()
plt.imshow(img/255.0)
plt.axis('off')

plt.figure(2)
plt.imshow(img_out)
plt.axis('off')

plt.show()          
