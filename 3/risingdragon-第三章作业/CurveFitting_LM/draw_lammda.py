# -*- coding: utf-8 -*-


import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

x = [0,1,2,3,4,5,6,7,8,9,10,11]
y = [0.001,699.051,1864.14,1242.76,414.252,138.084,46.028,15.3427,5.11423,1.70474,0.568247,0.378832]


x1 = [0,1,2,3,4,5,6,7,8,9]
y1 = [0.001,0.00091,0.00059,0.00034,0.0002,0.00011,6.14e-05,3.48e-05,1.97e-05,1.11e-05]

x2 = [0,1,2,3,4,5,6,7,8,9]
y2 = [0.001,17.8946,1.98828,0.22092,0.0245467,0.00272741,0.000303046,3.36718e-05,3.74131e-06,4.15701e-07]

#plt.plot(x,y,marker="o",linestyle="dashed")
plt.plot(x1,y1,marker="o",linestyle="dashed")
plt.plot(x2,y2,marker="o",linestyle="dashed")
plt.xlabel('iter number')

plt.ylabel('lammda')
plt.show()
