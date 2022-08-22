import numpy as np
import matplotlib.pyplot as plt
import random

data = np.loadtxt("init.txt")

U = data.T[-1]
m = data.T[0]
r = data.T[1]

grid = np.logspace(-1.5, 2, 100)

m_enc = (1 + 1/grid**2)**-1.5
rv = 16/(3*np.pi)

# plt.plot(grid/rv,m_enc)
# plt.hist(r, cumulative=True, bins=grid, weights=m,color="r")   
# plt.xscale("log")
# plt.show()

plt.plot(1 / r, U, "^-", ms=3)
plt.show()


# x, y, z = [], [], []
# for R in r:
#     x3 = random.random()
#     k = (1 - 2*random.random()) * R
#     z.append(k)
#     y.append(np.sqrt(R**2 - k**2)*np.sin(2 * np.pi * x3))
#     x.append(np.sqrt(R**2 - k**2)*np.cos(2 * np.pi * x3))
    
# fig = plt.figure()
# ax = fig.add_subplot(projection='3d')

# ax.scatter(x, y, z, "o",s=1)

# ax.set_xlabel('X Label')
# ax.set_ylabel('Y Label')
# ax.set_zlabel('Z Label')

# plt.show()