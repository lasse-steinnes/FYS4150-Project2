# FYS4150-Project2: Eigenvalue Problems
Git for Project 2 in Computational Physics (FYS4150).

### Main overview
* The programs in this repository aim at solving the questions about eigenvalue problems (EVPs) posed in the project 2 description: [Project 2 - Eigenvalue Problems ](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/Report/Project2-description.pdf). The final report can be found at: [From the Buckling Beam Problem to Quantum Mechanics: Solving Eigenvalue Problems with Jacobi’s Method](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/Report/Aaby_Steinnes_Rahsid_Jacobi_Method_for_EVPs.pdf).

* The main challenge was to create an eigenvalue solver using the Jacobi Algorithm, then apply it to differential equations known from Physics.
1. The Buckling Beam problem
2. Quantum mechanics harmonic oscillator potential:
    -1 electron
    -2 electrons


* Another central task was to check crucial functions of the algorithm, using unit tests. In addition, benchmarking results with time usage and relative error is performed.

* Textfiles and figures can be found in the folder Results.

### Code: Link and description of programmes
- [main.cpp](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/main.cpp) : Runs the other programmes and provide user options through terminal.

 - [makefile](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/makefile) : Compiles and executes cpp files, and provides plot options of eigenvalues and transformations of the initial matrix.  

-  [jacobimethodsolver.hpp](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/jacobimethodsolver.hpp) : Headerfile for the superclass JacobiMethodSolver, with subclasses BucklingBeamSolver, OneElectronSolver and TwoElectronSolver.

- [jacobimethodsolver.cpp](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/jacobimethodsolver.cpp) : Superclass methods provided are given in following order
  1. initialize : Sets up the general matrix A
  2. Write_eigenvectors_to_file
  3. max_offdiag_elem: Find maximum absolute value of       off-diagonal element and return time
  4. rotating_matrixA: Performes the Jacobi transformation with S as a rotational matrix S and return time
  5.  Mean and std
  6. solve: Uses the above mentioned methods, returns eigenvalues through the method get_eigenvalues
  7. write_relative_error_to_file
  8. write_eigenvalues_and_rho_to_file

- [oneelectronssolver.cpp](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/oneelectronsolver.cpp) : Sets up the matrix A with a potential term.

- [twoelectronsolver.cpp](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/twoelectronssolver.cpp) : Sets up the matrix A with a potential term relating to the Coulomb repulsion.

- [test.cpp](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/test.cpp): Unit tests for eigenvalues and checking if max off-diagonal works as intended. Has headerfile [catch.hpp](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/catch.hpp)

- [optimizeparams.hpp](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/optimizeparams.hpp) : Headerfile relating to the class OptimizeParams with methods optimize_rho and optimize_n.

- [optimize.cpp](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/optimizeparams.cpp) : Methods for optimizing. Benchmark used - max absolute error for lambda
  1. initialize: Set rho and N intervals to be tested
  2. optimize_rho: Find optimal rho for given interval.
  3. optimize_n: Find optimal n for interval and given tolerance.

- [plot_eigenvector.py](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/plot_eigenvector.py) plots the eigenvectors and eigenvalues, while [plot_transformations.py](https://github.com/lasse-steinnes/FYS4150-Project2/blob/master/code-and-results/plot_transformations.py) visualizes matrix transformations T as a function of N intervals of rho.
