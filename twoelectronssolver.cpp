#include "jacobimethodsolver.hpp"

//solving task e) with two electrons
void TwoElectronsSolver::init(int N, double rho_max,double omega_r){
  initialize(N,rho_max); //initialize funksjon fra superklassen
  double hh = h*h;
  double oo = omega_r*omega_r;
  vec rho = vec(N);
  for (int i= 0; i < N; ++i){ //looping over inner points
      rho(i) += (i+1)*h;
      A(i,i) = 2/hh + rho(i)*rho(i)*oo + (double) 1/rho(i); //diagonal elements
    }
}
