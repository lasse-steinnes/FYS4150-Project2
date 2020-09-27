#include "jacobimethodsolver.hpp"
#include<iostream>
#include<string>
#include "time.h"
using namespace std;

//Setting up the superclass for Jacobi's method with rotational algorithm to be used in all derived classes

void JacobiMethodSolver::initialize(int N, double rho_max){
  //initialize variables to set up Jacobis algorithm
  //to be used in all derived classes
  m_N = N;
  rhoN = rho_max;
  h = (double) rhoN/(m_N+1);         //steplength m_N
  double hh = h*h;
  //creating matrix A
  A = zeros<mat>(m_N,m_N);
  m_rho = vec(m_N);
  for (int i = 0; i < m_N; ++i){    //n*n elements,n-1 highest index
      A(i,i) = 2; //diagonal elements
      m_rho(i) = (i+1)*h;
  }
  for (int i = 0; i < m_N-1; ++i){
      A(i+1,i) = -1; // Fill in for elemnts below diag
      A(i,i+1) = -1; // Fill in for elements above diag
  }
  A = (1/hh)*A;
}

void JacobiMethodSolver::write_eigenvectors_to_file(){
  vec eigval_start;
  mat eigvec_start;
  eig_sym(eigval_start,eigvec_start,A);
  ofstream myfile;
  string filename("./Results/eigenvectors" + to_string(m_N) + ".txt");
  myfile.open(filename);
  myfile << "Eigevectors";
  myfile << "\n";
  myfile << eigvec_start;
  myfile << "\n";
  myfile.close();
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

void JacobiMethodSolver::solve(){
  double tol = 1.0E-10;
  transformations = 0;
  max_offdiag = 1;
  clock_t start, finish;
  start = clock();
  while (max_offdiag > tol){
    max_offdiag_element();
    rotating_matrixA();
    transformations++;
  }
  finish = clock();
  cpu_time_jacobi = 1000.0 * (finish - start)/CLOCKS_PER_SEC;  //computing CPU cpu_time_jacobi
}

void JacobiMethodSolver::write_eigenvalues_and_rho_to_file(){
  clock_t start, finish;
  start = clock();
  vec eigval_final = eig_sym(A);
  finish = clock();
  double cpu_time_arma = 1000.0 * (finish - start)/CLOCKS_PER_SEC;  //computing CPU time
  cout << "CPU time for Jacobi method with N = " + to_string(m_N) + " : " << cpu_time_jacobi << "ms\n";
  cout << "CPU time for finding eigenvalues with armadillo for N = " + to_string(m_N) + " : " << cpu_time_arma << "ms\n";

  ofstream myfile;
  cout << "Writing eigenvalues and rho-values to file: eigenvalues_rho" + to_string(m_N) + ".txt" << "\n";
  string filename("./Results/eigenvalues_rho" + to_string(m_N) + ".txt");
  myfile.open(filename);
  myfile << "Eigenvalues" << " " << "rho";
  myfile << "\n";
  for (int i = 0; i < m_N; i++){
    myfile << eigval_final(i) << " " << m_rho(i);
    myfile << "\n";
  }
  myfile.close();
}
