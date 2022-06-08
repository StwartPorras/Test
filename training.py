from ast import Constant
from cmath import pi
import math
import matplotlib.pyplot as plt
import numpy as np

v = 100; a = pi/3


t = np.linspace(0,17.33, num=100)
x = v*math.cos(a)*t; y = v*math.sin(a)*t-5*np.square(t)
t2 = np.arange(0,17.33,2)
x2 = v*math.cos(a)*t2; y2 = v*math.sin(a)*t2-5*np.square(t2)


plt.figure()
plt.plot(x,y,'g-',x2,y2,'r*')
plt.xlabel('distancia');plt.ylabel('altura');plt.title('Tiro parabólico')
plt.grid()
plt.show()

