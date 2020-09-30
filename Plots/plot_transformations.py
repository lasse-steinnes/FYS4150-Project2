import numpy as np
import matplotlib.pyplot as plt

infile = open("./Results/transformations.txt", 'r')

n = []    #grid points
iter = []    #tridiagonal solutions
for line in infile:
    numbers = line.split()
    n.append(float(numbers[0]))
    iter.append(float(numbers[1]))

n = np.array(n)
iter = np.array(iter)

##plotting tridiagonal solutions along with analytic solutions

plt.plot(np.log10(n),np.log10(iter), label = 'Logarithm Log(T) of number of transformations T(n)')
plt.title("Matrix transformations T(n) as a function of n")
plt.xlabel('log(n)')
plt.ylabel('log(T)')
plt.legend()
plt.savefig("./results/figs/transformations.png")
plt.show()
