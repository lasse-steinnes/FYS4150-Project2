#include "jacobimethodsolver.hpp"

//task b)
void BucklingBeamSolver::init(int N, double rho_max){
  initialize(N,rho_max);  //Initialize funksjon fra superklassen
}

void BucklingBeamSolver::write_trans_dims_to_file(){
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
