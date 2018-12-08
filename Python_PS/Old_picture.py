from skimage import img_as_float
import matplotlib.pyplot as plt
from skimage import io

file_name='D:/Image Processing/PS Algorithm/9.jpg';
img=io.imread(file_name)

img = img_as_float(img)

r=img[:,:,0];
g=img[:,:,1];
b=img[:,:,2];

img_out = img * 1.0

img_out[:, :, 0] = 0.393*r+0.769*g+0.189*b
img_out[:, :, 1] = 0.349*r+0.686*g+0.168*b
img_out[:, :, 2] = 0.272*r+0.534*g+0.131*b

mask = img_out > 1
img_out = img_out * (1 - mask) + (img_out * 0 + 1) * mask

plt.figure(1)
plt.imshow(img)
plt.axis('off');

plt.figure(2)
plt.imshow(img_out)
plt.axis('off');


plt.show();
