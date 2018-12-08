import matplotlib.pyplot as plt
from skimage import io
import math
import numpy as np

# image fusion

file_name='D:/Visual Effects/PS Algorithm/2.jpg';
img_1=io.imread(file_name)
img_1 = img_1/255.0

file_name2='D:/Visual Effects/PS Algorithm/3.jpg'
img_2=io.imread(file_name2)
img_2 = img_2/255.0


# 不透明度
def Transparent(img_1, img_2, alpha):
    img = img_1 * alpha + img_2 * (1-alpha)
    return img

# 正片叠底
def Multiply (img_1, img_2):
    img = img_1 * img_2
    return img

# 颜色加深 
def Color_burn (img_1, img_2):
    img = 1 - (1 - img_2) / (img_1 + 0.001)
    
    mask_1 = img  < 0 
    mask_2 = img  > 1
    
    img = img * (1-mask_1)
    img = img * (1-mask_2) + mask_2
    
    '''
    row, col, channel = img.shape
    for i in range(row):
        for j in range(col):
            img[i, j, 0] = min(max(img[i, j, 0], 0), 1)
            img[i, j, 1] = min(max(img[i, j, 1], 0), 1)
            img[i, j, 2] = min(max(img[i, j, 2], 0), 1)
    '''
    
    return img

# 颜色减淡
def Color_dodge(img_1, img_2):
    img = img_2 / (1.0 - img_1 + 0.001)
    mask_2 = img  > 1
    img = img * (1-mask_2) + mask_2
                
    return img 

# 线性加深 
def Linear_burn(img_1, img_2):
    img = img_1 + img_2 - 1
    mask_1 = img  < 0 
    img = img * (1-mask_1)
    
    return img
    
# 线性减淡
def Linear_dodge(img_1, img_2):
    img = img_1 + img_2
    mask_2 = img  > 1
    img = img * (1-mask_2) + mask_2
    
    return img

# 变亮
def Lighten(img_1, img_2):
    img = img_1 - img_2
    mask = img > 0
    img = img_1 * mask + img_2 * (1-mask) 
    
    return img 

# 变暗
def Dark(img_1, img_2):
    img = img_1 - img_2
    mask = img < 0
    img = img_1 * mask + img_2 * (1-mask) 
    
    return img 
    
# 滤色
def Screen(img_1, img_2):
    img = 1- (1-img_1)*(1-img_2)
    
    return img

# 叠加
def Overlay(img_1, img_2):
    mask = img_2 < 0.5
    img = 2 * img_1 * img_2 * mask + (1-mask) * (1- 2 * (1-img_1)*(1-img_2))
    
    return img

# 柔光
def Soft_light(img_1, img_2):
    mask = img_1 < 0.5
    T1 = (2 * img_1 -1)*(img_2 - img_2 * img_2) + img_2
    T2 = (2 * img_1 -1)*(np.sqrt(img_2) - img_2) + img_2
    img = T1 * mask + T2 * (1-mask)
    
    return img

# 强光
def Hard_light(img_1, img_2):
    mask = img_1 < 0.5
    T1 = 2 * img_1 * img_2
    T2 = 1 - 2 * (1 - img_1) * (1 - img_2)
    img = T1 * mask + T2 * (1-mask)
    
    return img

# 亮光
def Vivid_light(img_1, img_2):
    mask = img_1 < 0.5
    T1 = 1 - (1 - img_2)/(2 * img_1 + 0.001)
    T2 = img_2 / (2*(1-img_1) + 0.001)
    mask_1 = T1 < 0
    mask_2 = T2 > 1
    T1 = T1 * (1-mask_1)
    T2 = T2 * (1-mask_2) + mask_2
    img = T1 * mask  + T2 * (1 - mask) 
    
    return img 

# 点光
def Pin_light(img_1, img_2):
    mask_1 = img_2 < (img_1 * 2 -1)
    mask_2 = img_2 > 2 * img_1
    T1 = 2 * img_1 -1 
    T2 = img_2
    T3 = 2 * img_1 
    img = T1 * mask_1 + T2 * (1 - mask_1) * (1 - mask_2) + T3 * mask_2
                             
    return img

# 线性光
def Linear_light(img_1, img_2):
    img = img_2 + img_1 * 2 - 1
    mask_1 = img < 0
    mask_2 = img > 1
    img = img * (1-mask_1)
    img = img * (1-mask_2) + mask_2
    
    return img

# 实色混合
def Hard_mix(img_1, img_2):
    img = img_1 + img_2 
    mask = img_1 + img_2 > 1 
    img = img * (1-mask) + mask 
    img = img * mask
    return img
        

alpha = 0.5

# img = Transparent(img_1, img_2, alpha)
# img = Multiply (img_1, img_2)
# img = Color_burn(img_1, img_2)
# img = Color_dodge(img_1, img_2)
# img = Linear_burn(img_1, img_2)
# img = Linear_dodge(img_1, img_2)
# img = Lighten(img_1, img_2)
# img = Dark (img_1, img_2)
# img = Screen(img_1, img_2)
# img = Overlay(img_1, img_2)
# img = Soft_light(img_1, img_2)
# img = Hard_light(img_1, img_2)
# img = Vivid_light(img_1, img_2)
# img = Pin_light(img_1, img_2)
# img = Linear_light(img_1, img_2)
img = Hard_mix(img_1, img_2)

# show the image

plt.figure(1)
plt.imshow(img_1)
plt.axis('off');

plt.figure(2)
plt.imshow(img_2)
plt.axis('off');

plt.figure(3)
plt.imshow(img)
plt.axis('off');
        
plt.show()
