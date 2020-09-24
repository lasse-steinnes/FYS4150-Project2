#include "jacobimethodsolver.hpp"

//task b)
void BucklingBeamSolver::init(int N, double rho_max){
  initialize(N,rho_max);  //Initialize funksjon fra superklassen
}

void BucklingBeamSolver::solve(){
  double tol = 1.0E-10;
  transformations = 0;
  max_offdiag = 1;
  while (max_offdiag > tol){
    max_offdiag_element();
    rotating_matrixA();
    transformations++;
  }
}

void BucklingBeamSolver::write_transformation_func_to_file(){
  vec n_lin = linspace(5, 150, 8);
  ofstream myfile;
  myfile.open("transformation_func.txt");
  double rho_max = 1;
  for (int i = 0; i < 8; i++){
    int int_n = (int) n_lin(i);
    init(int_n,rho_max);
    solve();
    myfile << int_n << " " << transformations;
    myfile << "\n";
  }
  myfile.close();
}
