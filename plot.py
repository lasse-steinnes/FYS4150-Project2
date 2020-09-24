import numpy as np
import matplotlib.pyplot as plt

infile = open("transformation_func.txt", 'r')

n = []    #grid points
iter = []    #tridiagonal solutions
for line in infile:
    numbers = line.split()
    n.append(float(numbers[0]))
    iter.append(float(numbers[1]))

n = np.array(n)
iter = np.array(iter)

##plotting tridiagonal solutions along with analytic solutions

plt.plot(np.log10(n),np.log10(iter),"*", label = 'Transformations')
plt.title("Number of transformations as function of n")
plt.xlabel('n')
plt.ylabel('Number of transformations')
plt.legend()
plt.show()
