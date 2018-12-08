import numpy as np
import random
import math



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