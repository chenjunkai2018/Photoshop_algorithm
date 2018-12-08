from skimage import img_as_float
import matplotlib.pyplot as plt
from skimage import io

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

img = img_as_float(img)

img_1 = img.copy()
img_2 = img.copy()
img_3 = img.copy()
img_4 = img.copy()

img_out = img.copy()

Offset = 7

row, col, channel = img.shape

img_1[:, 0 : col-1-Offset, :] = img[:, Offset:col-1, :]
img_2[:, Offset:col-1, :] = img[:, 0 : col-1-Offset, :] 
img_3[0:row-1-Offset, :, :] = img[Offset:row-1, :, :]
img_4[Offset:row-1, :, :] = img[0:row-1-Offset, :, :]

img_out = (img_1 + img_2 + img_3 + img_4) / 4.0

plt.figure(1)
plt.imshow(img)
plt.axis('off');

plt.figure(2)
plt.imshow(img_out)
plt.axis('off');

