#ifndef JacobiMethodSolver_HPP
#define JacobiMethodSolver_HPP
#include <fstream>
#include <armadillo>
#include <cmath>

using namespace std;
using namespace arma;

//setting up Jacobi's method as a superclass
class JacobiMethodSolver {
protected:
  int m_N;             //number of grid points
  vec m_rho, m_l;      //dimensionless length rho and the different computed eigenvalues m_l
  mat A, m_v;          //Our tridiagonal matrix A and computed eigenvectors m_v, both stored in a matrix
  ofstream m_ofile;

public:
  void initialize(int N);     //public init function to be used in all derived classes
  void max_offdiag_element();
  void jacobi_algo();
  
public vec arma_eig (mat A) {
  eig_sym(A);    
  return eig_val
}

};


//solving task b) with the buckling beam
class BucklingBeamSolver : public JacobiMethodSolver {
private:

public:
  void init(int N);    ////special init function for this specific derived class
  


};


//solving task d) with Quantum dots in three dimensions with one electron
class OneElectronSolver : public JacobiMethodSolver {
private:

public:
  void init(int N);   //special init function for this specific derived class

};


//solving task e) with Quantum dots in three dimensions with two electron
class TwoElectronsSolver : public JacobiMethodSolver {
private:

public:
  void init(int N);    //special init function for this specific derived class

};


#endif
