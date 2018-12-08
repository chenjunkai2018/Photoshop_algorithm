from skimage import img_as_float
import matplotlib.pyplot as plt
from skimage import io
from skimage.filters._gaussian import gaussian

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

img = img_as_float(img)

img_out = gaussian(img, sigma=3, multichannel=True)

plt.figure(1)
plt.imshow(img)
plt.axis('off');

plt.figure(2)
plt.imshow(img_out)
plt.axis('off');

