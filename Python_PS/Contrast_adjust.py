import matplotlib.pyplot as plt
from skimage import io

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

img = img * 1.0

thre = img.mean()

# -100 - 100
contrast = -55.0

img_out = img * 1.0

if contrast <= -255.0:
    img_out = (img_out >= 0) + thre -1
elif contrast > -255.0 and contrast < 0:
    img_out = img + (img - thre) * contrast / 255.0   
elif contrast < 255.0 and contrast > 0:    
    new_con = 255.0 *255.0 / (256.0-contrast) - 255.0
    img_out = img + (img - thre) * new_con / 255.0   
else:
    mask_1 = img > thre 
    img_out = mask_1 * 255.0
    
img_out = img_out / 255.0 

# 饱和处理
mask_1 = img_out  < 0 
mask_2 = img_out  > 1

img_out = img_out * (1-mask_1)
img_out = img_out * (1-mask_2) + mask_2

plt.figure(1)
plt.imshow(img/255.0)
plt.axis('off')

plt.figure(2)
plt.imshow(img_out)
plt.axis('off')

plt.show()