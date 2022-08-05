# -*- coding: utf-8 -*-


import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

x = [1,2,3,4,5,6,7,8,9,10]
y = [8.00803e+07,2.00198e+07, 8.8976e+06,5.00484e+06,3.20306e+06, 2.22432e+06,1.63418e+06,1.25115e+06,988554,800719]


x1 = [0,1,2,3,4,5,6,7,8,9]
y1 = [0.001,0.00091,0.00059,0.00034,0.0002,0.00011,6.14e-05,3.48e-05,1.97e-05,1.11e-05]

x2 = [2,3,4,5,6,7,8,9]
y2 = [ 2.63692e+06,973951,2.49664e+06,5.80843e+06,1.17346e+07,2.00198e+07, 2.90264e+07, 4.72672e+07]

plt.plot(x,y,marker="o",linestyle="dashed")
#plt.plot(x1,y1,marker="o",linestyle="dashed")
#plt.plot(x2,y2,marker="o",linestyle="dashed")
plt.xlabel('pixel error')

plt.ylabel('ratio')


plt.figure()

plt.plot(x2,y2,marker="o",linestyle="dashed")
plt.xlabel('num frame')
plt.ylabel('ratio')
plt.show()
