#include "project2.hpp"
#include <iostream>     //Provides us with function to print to terminal
#include <cmath>        //Provides us with mathematical functions such as sin, cos, exp and so on.
#include <fstream>
#include "armadillo"

using namespace arma;
using namespace std;

//Initializing the system for the general algorithm
void Project2::initialize(double rho0, double rhoN, int N, double ai, double bi, double ci){
  m_N = N;                              //Number of grid points
  m_h = ((double)(rhoN - rho0)/(m_N+1));    // steplength h

  double hh = m_h*m_h;
  m_a = ai/hh;
  m_b = bi/hh;
  m_c = ci/hh;


  m_v = new double[m_N];     //allocating the numerical solutions v
  m_rho = new double[m_N];     //allocating the grid points

  for (int i = 0; i < m_N; i++){
    m_rho[i] = rho0 + (i+1)*m_h;      //filling the grid points from 0 to 1
  }
}

void Project2::diagonalize_A(double ai, double bi, double ci, int N){
  //creating the tridiagonal matrix A with NxN elements
  mat A = mat(N,N);
  for (int i = 1; i < N-1; i++){
    A(i,i) = bi;
    A(i,i+1) = ai;
    A(i,i-1) = ci;
  }
  A(0,0) = bi;
  A(N-1,N-1) = bi;
  A(N-1,N-2) = ai;
  A(0,1) = ci;

  mat B = diagmat(A);
  B.print();
}

//finding analytic eigenvalues and eigenvectors
void Project2::analytic_eigenpairs(int N){
  mat Lambda = mat(N,N);
  mat u = mat(N,N);
  for (int j = 0; j < N; j++){
    Lambda(j,j) = m_b + 2*m_a*cos(((j+1)*M_PI)/N);
    for (int i = 0; i < N; i++){
      u(i,j) = sin(((i+1)*(j+1)*M_PI)/N);
    }
  }

  Lambda.print();
  //cout << "printing eigenvectors" << "\n";
  //u.print();
}
