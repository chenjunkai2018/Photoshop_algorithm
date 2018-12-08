from skimage import img_as_float
import matplotlib.pyplot as plt
from skimage import io
# import cv2

file_name='D:/Visual Effects/PS Algorithm/4.jpg'

img=io.imread(file_name)

img = img_as_float(img)

r = img[:, :, 0]
g = img[:, :, 1]
b = img[:, :, 2]

blueGreen=0.3
redBlue=0.5
greenRed=0.75

intoR=0.75
intoG=0.5
intoB=0.75

img_out = img.copy()

img_out[:, :, 0] = (intoR * (blueGreen*g+(1-blueGreen)*b) + (1-intoR)*r)
img_out[:, :, 1] = (intoG * (redBlue*b+(1-redBlue)*r) + (1-intoG)*g)
img_out[:, :, 2] = (intoB * (greenRed*r+(1-greenRed)*g) + (1-intoB)*b)

plt.figure(2)
plt.imshow(img_out)
plt.axis('off')

plt.figure(1)
plt.imshow(img)
plt.axis('off')


'''
cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()
'''
