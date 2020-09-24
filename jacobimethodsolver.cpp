#include "jacobimethodsolver.hpp"

//Setting up the superclass for Jacobi's method with rotational algorithm to be used in all derived classes

void JacobiMethodSolver::initialize(int N){
  //initialize variables to set up Jacobis algorithm
  //to be used in all derived classes
  m_N = N;
}

//finding maximal absolute offdiagonal element of matrix A, and its specific index (k,l)
void JacobiMethodSolver::max_offdiag_element(){

}

//updating the elements of matrix A by rotating around the elements given index (k,l)
void JacobiMethodSolver::jacobi_algo(){

}
