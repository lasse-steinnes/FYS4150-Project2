#ifndef JacobiMethodSolver_HPP
#define JacobiMethodSolver_HPP
#include <fstream>
#include <armadillo>
#include <chrono>

using namespace std;
using namespace arma;
using namespace chrono;

//setting up Jacobi's method as a superclass
class JacobiMethodSolver {
private:
  int k,l;
  double cpu_time_jacobi;
  vector<double> time_max;
  vector<double> time_rotate;

protected:
  string task;
  int m_N;
  vec m_rho, m_l;      //dimensionless length rho and the different computed eigenvalues m_l
  mat A, V;          //Our tridiagonal matrix A stored in a matrix
  ofstream m_ofile;
  double h,rhoN, max_offdiag, omega_r;
  int transformations;
  vector<double> an_val;

public:
  void initialize(int N, double rho_max);     //public init function to be used in all derived classes and outside the superclass
  duration<double, milli> max_offdiag_element();
  duration<double, milli> rotating_matrixA();
  vector<double> get_eigenvalues(mat A, int m_N);
  void finding_eigenvector();
  vector<double> solve();
  vector<double> analytic_eigenvalues();
  void write_relative_error_to_file();
  void write_eigenvalues_and_rho_to_file();
  void write_eigenvectors_to_file();
};


//solving task b) with the buckling beam
class BucklingBeamSolver : public JacobiMethodSolver {
private:

public:
  void init(int N, double rho_max);    ////special init function for this specific derived class
  void write_trans_dims_to_file();
  void analytic_eigenpairs();
};


//solving task d) with Quantum dots in three dimensions with one electron
class OneElectronSolver : public JacobiMethodSolver {
private:

public:
  void init(int N, double rho_max);   //special init function for this specific derived class
};

//solving task e) with Quantum dots in three dimensions with two electron
class TwoElectronsSolver : public JacobiMethodSolver {
private:

public:
  void init(int N, double rho_max, double omega_r);    //special init function for this specific derived class
};

#endif
