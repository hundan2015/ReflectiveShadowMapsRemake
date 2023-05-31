import matplotlib.pyplot as plt
import numpy as np
import math
import random


def ReturnPoint(s, t, r_max, sigma1, sigma2):
    x = s+r_max*sigma1*math.sin(2*math.pi*sigma2)
    y = t+r_max*sigma1*math.cos(2*math.pi*sigma2)
    return x, y


plot_x = []
plot_y = []
sizes = []
for i in range(400):
    sigma1 = random.random()*25
    sigma2 = random.random()*25
    weight = sigma1*sigma1
    x, y = ReturnPoint(0, 0, 10, sigma1, sigma2)
    plot_x.append(x)
    plot_y.append(y)
    sizes.append(weight)

x = np.array(plot_x)
y = np.array(plot_y)
size = np.array(sizes)
print(len(x))
plt.scatter(x, y, s=size, alpha=0.5)
plt.show()
