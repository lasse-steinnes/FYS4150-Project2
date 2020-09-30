#include "jacobimethodsolver.hpp"

//solving task d) with one electron
void OneElectronSolver::init(int N, double rho_max){
  initialize(N,rho_max); //Initialize funksjon fra superklassen
  task = "d";
  omega_r = 0;

  double hh = h*h;
  for (int i= 0; i < N; ++i){ //looping over inner points
      m_rho(i) = (i+1)*h;
      A(i,i) = 2/hh + m_rho(i)*m_rho(i); //diagonal elements
    }
}
