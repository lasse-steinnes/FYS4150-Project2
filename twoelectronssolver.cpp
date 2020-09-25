#include "jacobimethodsolver.hpp"

//solving task e) with two electrons
void TwoElectronsSolver::init(int N, double rho_max,double omega){
  initialize(N,rho_max); //initialize funksjon fra superklassen
  omega_r = omega;
  double hh = h*h;
  double oo = omega_r*omega_r;
  for (int i= 0; i < N; ++i){ //looping over inner points
      A(i,i) = 2/hh + m_rho(i)*m_rho(i)*oo + (double) 1/m_rho(i); //diagonal elements
    }
}
