#ifndef JacobiMethodSolver_HPP
#define JacobiMethodSolver_HPP
#include <fstream>
#include <armadillo>

using namespace std;
using namespace arma;

//setting up Jacobi's method as a superclass
class JacobiMethodSolver {
private:
  int k,l;

protected:
  int m_N;
  vec m_rho, m_l;      //dimensionless length rho and the different computed eigenvalues m_l
  mat A, V;          //Our tridiagonal matrix A stored in a matrix
  ofstream m_ofile;
  double h,rhoN, max_offdiag;

public:
  void initialize(int N, double rho_max);     //public init function to be used in all derived classes and outside the superclass
  void max_offdiag_element();
  void rotating_matrixA();
  void finding_eigenvector();
};


//solving task b) with the buckling beam
class BucklingBeamSolver : public JacobiMethodSolver {
private:
  int transformations;

public:
  void init(int N, double rho_max);    ////special init function for this specific derived class
  void solve();
  void write_transformation_func_to_file();

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
