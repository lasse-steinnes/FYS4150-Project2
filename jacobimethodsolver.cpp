#include "jacobimethodsolver.hpp"
#include<iostream>
using namespace std;

//Setting up the superclass for Jacobi's method with rotational algorithm to be used in all derived classes

void JacobiMethodSolver::initialize(int N, double rho_max){
  //initialize variables to set up Jacobis algorithm
  //to be used in all derived classes
  m_N = N;
  rhoN = rho_max;
  double h = (double) rhoN/(m_N+1);         //steplength m_N
  double hh = h*h;
  //creating matrix A
  A = zeros<mat>(m_N,m_N);
  for (int i = 0; i < m_N; ++i){    //n*n elements,n-1 highest index
      A(i,i) = 2/hh; //diagonal elements
    }
  for (int i = 0; i < m_N-1; ++i){
      A(i+1,i) = -1/hh; // Fill in for elemnts below diag
      A(i,i+1) = -1/hh; // Fill in for elements above diag
    }
}

//finding maximal absolute offdiagonal element of matrix A, and its specific index (k,l)
void JacobiMethodSolver::max_offdiag_element(){
  double max_val = 0.0;
  for (int i = 0; i < m_N; i++){
    for (int j = i+1; j < m_N; j++){
      double offdiag_ij = fabs(A(i,j));
      if (offdiag_ij > max_val){
        max_val = offdiag_ij;
        k = i;
        l = j;
      }
    }
  }
  max_offdiag = max_val;
}

//updating the elements of matrix A by rotating around the elements given index (k,l)
void JacobiMethodSolver::rotating_matrixA(){
  double tau, t, c, s;
  if (A(k,l) != (double) 0){
    tau = (A(l,l) - A(k,k))/(2*A(k,l));
    if (tau >= 0){
      t = 1/(tau + sqrt(1 + tau*tau));
    }
    else{
      t = 1/(tau - sqrt(1 + tau*tau));
    }
    c = 1/(sqrt(1 + t*t));
    s = t*c;
  }
  else{
    c = (double) 1;
    s = (double) 0;
  }
  //updating the matrix A
  A(k,k) = A(k,k)*c*c - 2*A(k,l)*c*s + A(l,l)*s*s;
  A(l,l) = A(l,l)*c*c + 2*A(k,l)*c*s + A(k,k)*s*s;
  A(k,l) = A(l,k) = (double) 0;
  for (int i = 0; i < m_N; i ++){
    if (i != k && i != l){
      double aik = A(i,k);
      double ail = A(i,l);
      A(i,k) = aik*c - ail*s;
      A(i,l) = ail*c + aik*s;
      A(k,i) = A(i,k);
      A(l,i) = A(i,l);
    }
  }
}
