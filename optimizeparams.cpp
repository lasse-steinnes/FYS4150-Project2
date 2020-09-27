#include "optimizeparams.hpp"
#include<iostream>
#include<armadillo>

using namespace std;
using namespace arma;

void OptimizeParams::initialize(){
  m_rho = zeros(6); m_N = zeros(5);
  m_rho(0) = 10; m_N(0) = 10;

  for (int i = 1; i < 6; i++){
    m_rho(i) = m_rho(i-1)*10;
  }
  for (int j = 1; j < 5; j++){
    m_N(j) = m_N(j-1)*10;
  }
}

void OptimizeParams::optimize_rho(){
  int Nn = N(3);
  for (int i = 0; i < 6; i++){
    mysolver.init(Nn,rho_m(i));
    mysolver.solve();
  }
}

void OptimizeParams::optimize_n(){
  double rho_ = rho_m(3);
  for (int j = 0; j < 5; j++){
    mysolver.init(N(j),rho_);
    mysolver.solve();
  }
}
