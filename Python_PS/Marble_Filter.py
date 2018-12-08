import numpy as np
import math
import numpy.matlib
from skimage import io
import random
from skimage import img_as_float
import matplotlib.pyplot as plt

def Init_arr():
    
    B = 256
    P = np.zeros((B+B+2, 1))
    g1 = np.zeros((B+B+2, 1))
    g2 = np.zeros((B+B+2, 2))
    g3 = np.zeros((B+B+2, 3))

    N_max = 1e6

    for i in range(B+1):
        P[i] = i
        g1[i] = (((math.floor(random.random()*N_max)) % (2*B))-B)*1.0/B
        g2[i, :] = (np.mod((np.floor(np.random.rand(1, 2)*N_max)), (2*B))-B)*1.0/B
        g2[i, :] = g2[i, :] / np.sum(g2[i, :] **2)
        g3[i, :] = (np.mod((np.floor(np.random.rand(1, 3)*N_max)), (2*B))-B)*1.0/B
        g3[i, :] = g3[i, :] / np.sum(g3[i, :] **2)
    

    for i in range(B, -1, -1):
        k = P[i]
        j = math.floor(random.random()*N_max) % B
        P [i] = P [j]
        P [j] = k

    P[B+1:2*B+2]=P[0:B+1];
    g1[B+1:2*B+2]=g1[0:B+1];
    g2[B+1:2*B+2, :]=g2[0:B+1, :]
    g3[B+1:2*B+2, :]=g3[0:B+1, :]
    
    P = P.astype(int)
    
    return P, g1, g2, g3


def Noise_2(x_val, y_val, P, g2):
    
    BM=255
    N=4096

    t = x_val + N
    bx0 = ((np.floor(t).astype(int)) & BM) + 1
    bx1 = ((bx0 + 1).astype(int) & BM) + 1
    rx0 = t - np.floor(t)
    rx1 = rx0 - 1.0

    t = y_val + N
    by0 = ((np.floor(t).astype(int)) & BM) + 1
    by1 = ((bx0 + 1).astype(int) & BM) + 1
    ry0 = t - np.floor(t)
    ry1 = rx0 - 1.0

    sx = rx0 * rx0 * (3 - 2.0 * rx0)
    sy = ry0 * ry0 * (3 - 2.0 * ry0)
    
    row, col = x_val.shape
    
    q1 = np.zeros((row, col ,2))
    q2 = q1.copy()
    q3 = q1.copy()
    q4 = q1.copy()
    
    for i in range(row):
        for j in range(col):
            ind_i = P[bx0[i, j]]
            ind_j = P[bx1[i, j]]
            b00 = P[ind_i + by0[i, j]]
            b01 = P[ind_i + by1[i, j]]
            b10 = P[ind_j + by0[i, j]]
            b11 = P[ind_j + by1[i, j]]
            
            q1[i, j, :] = g2[b00, :]
            q2[i, j, :] = g2[b10, :]
            q3[i, j, :] = g2[b01, :]
            q4[i, j, :] = g2[b11, :]
    
    u1 = rx0 * q1[:, :, 0] + ry0 * q1[:, :, 1]
    v1 = rx1 * q2[:, :, 0] + ry1 * q2[:, :, 1]
    a = u1 + sx * (v1 - u1)
    
    u2 = rx0 * q3[:, :, 0] + ry0 * q3[:, :, 1]
    v2 = rx1 * q4[:, :, 0] + ry1 * q4[:, :, 1]
    b = u2 + sx * (v2 - u2)
    
    out = (a + sy * (b - a)) * 1.5
          
    return out
    
    
file_name='D:/Visual Effects/PS Algorithm/4.jpg';
img=io.imread(file_name)

img = img_as_float(img)
row, col, channel = img.shape

xScale = 25.0
yScale = 25.0
turbulence =0.25

xx = np.arange (col) 
yy = np.arange (row)

x_mask = numpy.matlib.repmat (xx, row, 1)
y_mask = numpy.matlib.repmat (yy, col, 1)
y_mask = np.transpose(y_mask)

x_val = x_mask / xScale
y_val = y_mask / yScale

Index = np.arange(256)

sin_T=-yScale*np.sin(2*math.pi*(Index)/255*turbulence);
cos_T=xScale*np.cos(2*math.pi*(Index)/255*turbulence)

P, g1, g2, g3 = Init_arr()

Noise_out = Noise_2(x_val, y_val, P, g2)

Noise_out = 127 * (Noise_out + 1)

Dis = np.floor(Noise_out)

Dis[Dis>255] = 255
Dis[Dis<0] = 0
Dis = Dis.astype(int)

img_out = img.copy()
   
for ii in range(row):
    for jj in range(col):
        
        new_x = jj + sin_T[Dis[ii, jj]]
        new_y = ii + cos_T[Dis[ii, jj]]
        
        if (new_x > 0 and new_x < col-1 and new_y > 0 and new_y < row-1):
            int_x = int(new_x)
            int_y = int(new_y)
            
            img_out[ii, jj, :] = img[int_y, int_x, :]


            
plt.figure(1)
plt.imshow(img)
plt.axis('off');
        
plt.figure(2)
plt.imshow(img_out)
plt.axis('off');

plt.show();        
