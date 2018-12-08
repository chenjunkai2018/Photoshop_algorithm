import numpy as np
import matplotlib.pyplot as plt
from skimage import io
import numpy.matlib
from skimage import img_as_float

file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

img = img_as_float(img)

row, col, channel = img.shape

color_map = img.copy()

rNW = 0.5
rNE = 1.0     
rSW = 0.0
rSE = 0.5     

gNW = 0.0
gNE = 0.5
gSW = 0.0
gSE = 1.0

bNW = 1.0
bNE = 0.0
bSW = 0.5
bSE = 0.0

xx = np.arange (col) 
yy = np.arange (row)

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

fx = x_mask * 1.0 / col
fy = y_mask * 1.0 / row

p = rNW + (rNE - rNW) * fx
q = rSW + (rSE - rSW) * fx
r = ( p + (q - p) * fy )
r[r<0] = 0
r[r>1] =1

p = gNW + (gNE - gNW) * fx
q = gSW + (gSE - gSW) * fx
g = ( p + (q - p) * fy )
g[g<0] = 0
g[g>1] =1

p = bNW + (bNE - bNW) * fx
q = bSW + (bSE - bSW) * fx
b = ( p + (q - p) * fy )
b[b<0] = 0.0
b[b>1] = 1.0

color_map[:, :, 0] = r
color_map[:, :, 1] = g
color_map[:, :, 2] = b

plt.figure(1)
plt.imshow(color_map)
plt.axis('off');

plt.show();
