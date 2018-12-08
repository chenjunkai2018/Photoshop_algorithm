import matplotlib.pyplot as plt
from skimage import io

file_name = 'D:/Visual Effects/PS Algorithm/4.jpg'
img=io.imread(file_name)

img = img * 1.0
img_out = img * 1.0

# -1 ~ 1
Increment = 0.5

img_min = img.min(axis=2)
img_max = img.max(axis=2)

Delta = (img_max - img_min) / 255.0
value = (img_max + img_min) / 255.0
L = value/2.0

mask_1 = L < 0.5

s1 = Delta/(value + 0.001)
s2 = Delta/(2 - value + 0.001)
s = s1 * mask_1 + s2 * (1 - mask_1)

if Increment >= 0 :
    temp = Increment + s
    mask_2 = temp >  1
    alpha_1 = s
    alpha_2 = s * 0 + 1 - Increment
    alpha = alpha_1 * mask_2 + alpha_2 * (1 - mask_2)
    alpha = 1/(alpha + 0.001) -1 
    img_out[:, :, 0] = img[:, :, 0] + (img[:, :, 0] - L * 255.0) * alpha
    img_out[:, :, 1] = img[:, :, 1] + (img[:, :, 1] - L * 255.0) * alpha
    img_out[:, :, 2] = img[:, :, 2] + (img[:, :, 2] - L * 255.0) * alpha
    
else:
    alpha = Increment
    img_out[:, :, 0] = L * 255.0 + (img[:, :, 0] - L * 255.0) * (1 + alpha)
    img_out[:, :, 1] = L * 255.0 + (img[:, :, 1] - L * 255.0) * (1 + alpha)  
    img_out[:, :, 2] = L * 255.0 + (img[:, :, 2] - L * 255.0) * (1 + alpha) 
    
    
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


