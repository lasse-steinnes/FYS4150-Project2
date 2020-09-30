import numpy as np
import matplotlib.pyplot as plt


##plotting tridiagonal solutions along with analytic solutions
task = input("Insert task number (b,d or e) = ")
N = input("Number of grid points N = ")

infile = open("./Results/eigenvalues_rho" + str(N) + task + ".txt", 'r')
rho_max_line = infile.readline().split()
rho_max = float(rho_max_line[1])
omega_r_line = infile.readline().split()
omega_r = float(omega_r_line[1])
infile.readline()
Lambda = []
rho = []
for line in infile:
    numbers = line.split()
    Lambda.append(float(numbers[0]))
    rho.append(float(numbers[1]))

rho = np.array(rho)
Lambda = np.array(Lambda)

if task == "b":
    infile = open("./Results/eigenvectors" + str(N) + str(task) + ".txt", 'r')
    infile.readline()
    infile.readline()
    infile.readline()

    N = int(N)
    V = np.zeros((N,N))   #the eigenvectors
    m = 0
    for line in infile:
        numbers = line.split()
        for i in range(len(numbers)):
            V[m,i] = float(numbers[i])
        m = m + 1

    #analytical ground_state for buckling beam problem
    ground_state = np.zeros(N)
    for i in range(N):
        ground_state[i] = np.sin(((i+1)*np.pi)/(N+1))

    plt.plot(rho,-V[:,0], label = 'Numerical eigenvector $u(\\rho)$')
    plt.plot(rho,-ground_state/(np.linalg.norm(ground_state)), label = 'Analytical eigenvector')
    plt.title("Buckling beam eigenvector $u(\\rho)$ for lowest eigenvalue for N = %d" %(N))
    plt.xlabel('$\\rho$')
    plt.ylabel('$u(\\rho)$')
    plt.legend()
    plt.savefig("./results/figs/lowest_eigenvector%db).png" %(N))
    plt.show()

if task == "d":
    N = int(N)
    Lambda_an = np.zeros(N)
    for i in range(N):
        Lambda_an[i] = 3 + 4*i

    plt.plot(rho,Lambda/(np.linalg.norm(Lambda)), label = 'One-electron eigenvalues $\lambda$')
    plt.plot(rho,Lambda_an/(np.linalg.norm(Lambda_an)), label = 'Analytical eigenvalues $\lambda$')
    plt.title("One-electron eigenvalues $\lambda$ for N = %d and $\\rho_{max}$ = %.2f" %(N,rho_max))
    plt.xlabel('$\\rho$')
    plt.ylabel('$\lambda$')
    plt.legend()
    plt.savefig("./results/figs/compare_eigenvalues%dd)rho=%.2f.png" %(N,rho_max))
    plt.show()

if task == "e":
    omega_r = input("Oscillating frequency (w_r) = ")
    infile = open("./Results/eigenvectors" + str(N) + str(task) + "omega=" + str(omega_r) + '' + ".txt", 'r')
    rho_max_line = infile.readline().split()
    rho_max = float(rho_max_line[1])
    infile.readline()
    infile.readline()

    N = int(N)
    omega_r = float(omega_r)
    V = np.zeros((N,N))   #the eigenvectors
    m = 0
    for line in infile:
        numbers = line.split()
        for i in range(len(numbers)):
            V[m,i] = float(numbers[i])
        m = m + 1

    plt.plot(rho,-V[:,0], label = 'Ground state, $\\rho_{max}$ = %.2f, $\omega_{r}$ = %.2f' %(rho_max, omega_r))
    plt.title("Ground state $u(\\rho)$ with two electrons for N = %d" %(N))
    plt.xlabel('$\\rho$')
    plt.ylabel('$u(\\rho)$')
    plt.legend()
    plt.savefig("./results/figs/ground_state%de)rho=%.2fomega=%.2f.png" %(N,rho_max,omega_r))
    plt.show()
