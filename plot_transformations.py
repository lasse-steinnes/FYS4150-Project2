import numpy as np
import matplotlib.pyplot as plt

infile = open("./Results/transformations.txt", 'r')
n = []    #different number of grid points
iter = []    #number of iterations for a given n
for line in infile:
    numbers = line.split()
    n.append(float(numbers[0]))
    iter.append(float(numbers[1]))

n = np.array(n)
iter = np.array(iter)

#Using polyfit on the measured values to calculate the slope of number of matrix transformations
p = np.polyfit(n,iter,50)
log_p = np.log10(np.abs(p))

sum = 0
for i in range(1,len(log_p)):
    sum += np.abs(log_p[i]-log_p[i-1])

slope = sum/(len(log_p))               #calculated slope number for number of transoformations
print(slope)

#plotting number of matrix transformations log(T) as function of n

plt.plot(np.log10(n),np.log10(iter), label = 'Logarithm Log(T) of number of transformations T(n)')
plt.title("Matrix transformations T(n) as a function of n")
plt.xlabel('$\log(n)$')
plt.ylabel('$\log(T)$')
plt.legend()
plt.savefig("./results/figs/transformations.png")
plt.show()
