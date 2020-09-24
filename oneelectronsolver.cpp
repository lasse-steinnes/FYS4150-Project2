#include "jacobimethodsolver.hpp"

//solving task d) with one electron
void OneElectronSolver::init(int N, double rho_max){
  initialize(N,rho_max); //Initialize funksjon fra superklassen

  double hh = h*h;
  vec rho = vec(N);
  for (int i= 0; i < N; ++i){ //looping over inner points
      rho(i) += (i+1)*h;
      A(i,i) = 2/hh + rho(i)*rho(i); //diagonal elements
    }
}


//flere funksjoner nedover her
