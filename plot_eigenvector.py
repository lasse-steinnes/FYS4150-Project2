import numpy as np
import matplotlib.pyplot as plt

N = input("Number of grid points N = ")

infile1 = open("./Results/eigenvalues_rho" + str(N) + ".txt", 'r')
infile1.readline()

Lambda = []    #the eigenvalues
rho = []
for line in infile1:
    numbers1 = line.split()
    Lambda.append(float(numbers1[0]))
    rho.append(float(numbers1[1]))

rho = np.array(rho)
Lambda = np.array(Lambda)

infile2 = open("./Results/eigenvectors" + str(N) + ".txt", 'r')
infile2.readline()

N = int(N)
V = np.zeros((N,N))   #the eigenvectors
m = 0
for line in infile2:
    numbers2 = line.split()
    for i in range(len(numbers2)):
        V[m,i] = float(numbers2[i])
    m = m + 1



##plotting tridiagonal solutions along with analytic solutions

plt.plot(rho,-V[:,0], label = 'Eigenvector')
plt.title("Eigenvector for lowest eigenvalue for N = %d" %(N))
plt.xlabel('rho')
plt.ylabel('Eigenvector')
plt.legend()
plt.savefig("./results/figs/lowest_eigenvector%d.png" %(N))
plt.show()
