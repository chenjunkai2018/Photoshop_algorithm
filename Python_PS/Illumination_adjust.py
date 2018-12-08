
import matplotlib.pyplot as plt
from skimage import io

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

# -255.0 - 255.0  alpha -1.0 - 1.0 
Increment = 105.0;
alpha = Increment/255.0;

def Illumi_adjust(alpha, img):
    if alpha > 0 :
        img_out = img * (1 - alpha) + alpha * 255.0
    else:
        img_out = img * (1 + alpha)
        
    return img_out/255.0

img_out = Illumi_adjust(alpha, img)

plt.figure()
plt.imshow(img)
plt.axis('off')

plt.figure(2)
plt.imshow(img_out)
plt.axis('off')

plt.show()