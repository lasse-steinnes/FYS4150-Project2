import numpy as np
import matplotlib.pyplot as plt

task = input("Insert task number (b,d or e) = ")
N = input("Number of grid points N = ")

infile1 = open("./Results/eigenvalues/eigenvalues_rho" + str(N) + task + ".txt", 'r')
rho_max_line = infile1.readline().split()
rho_max = float(rho_max_line[1])
omega_r_line = infile1.readline().split()
omega_r = float(omega_r_line[1])
infile1.readline()


Lambda = []    #the eigenvalues
rho = []
for line in infile1:
    numbers1 = line.split()
    Lambda.append(float(numbers1[0]))
    rho.append(float(numbers1[1]))

rho = np.array(rho)
Lambda = np.array(Lambda)

infile2 = open("./Results/eigenvector/eigenvectors" + str(N) + str(task) + ".txt", 'r')
infile2.readline()
infile2.readline()
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
if task == "b":
    plt.plot(rho,-V[:,0], label = 'Eigenvector')
    plt.title("Eigenvector for lowest eigenvalue for N = %d" %(N))
    plt.xlabel('rho')
    plt.ylabel('Eigenvector')
    plt.legend()
    plt.savefig("./Results/figs/lowest_eigenvector%db).png" %(N))
    plt.show()

if task == "d":
    plt.plot(rho,-V[:,0], label = 'Ground state, rho_max = %.2f' %(rho_max))
    plt.title("Ground state with one electron for lowest eigenvalue for N = %d" %(N))
    plt.xlabel('rho')
    plt.ylabel('Ground state')
    plt.legend()
    plt.savefig("./Results/figs/ground_state%dd)rho=%.2f.png" %(N,rho_max))
    plt.show()

if task == "e":
    plt.plot(rho,-V[:,0], label = 'Ground state, rho_max = %.2f, omega_r = %.2f' %(rho_max, omega_r))
    plt.title("Ground state with two electrons for lowest eigenvalue for N = %d" %(N))
    plt.xlabel('rho')
    plt.ylabel('Ground state')
    plt.legend()
    plt.savefig("./Results/figs/ground_state%de)rho=%.2fomega=%.2f.png" %(N,rho_max,omega_r))
    plt.show()
