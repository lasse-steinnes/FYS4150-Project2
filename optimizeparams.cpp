#include "optimizeparams.hpp"
#include "jacobimethodsolver.hpp"
#include<iostream>
#include<armadillo>

using namespace std;
using namespace arma;

void OptimizeParams::initialize(){
  m_rho = zeros(6); m_N = zeros(5);
  m_rho(0) = 10.817; m_N(0) = 10;

  for (int i = 1; i < 6; i++){
    m_rho(i) = m_rho(i-1)*1.000005;
  }
  for (int j = 1; j < 5; j++){
    m_N(j) = m_N(j-1)*10;
  }
}

void OptimizeParams::optimize_rho(){
  OneElectronSolver mysolver; //initialize mysolver
  int Nn = m_N(1);
  cout << Nn << endl;
  vec num_lam = zeros(Nn);

  //create analytical lambdas to compare with
  m_lambdas = zeros<vec>(Nn);
  m_lambdas(0) = 3;
  for (int i = 1; i < Nn; i++){
    m_lambdas(i) = m_lambdas(i-1) + 4;
  }

  //optimize rho
  for (int i = 0; i < 6; i++){
    mysolver.init(Nn,m_rho(i));
    vec num_lam = mysolver.solve();
    num_lam = sort(num_lam);
    //cout << "numerical lambda: " << " " << num_lam << endl;
    cout << "max absolute error:" << " " << max(num_lam - m_lambdas) << " "  << "rho:"<< m_rho(i) << endl;
    }
  }

void OptimizeParams::optimize_n(){
  OneElectronSolver mysolver; //initialize mysolver
  double rho_ = 10.8171;
  for (int j = 0; j < 5; j++){
    //create analytical lambdas to compare with (each different size to fit)
    m_lambdas = zeros<vec>(m_N(j));
    m_lambdas(0) = 3;
    for (int i = 1; i < m_N(j); i++){
      m_lambdas(i) = m_lambdas(i-1) + 4;
    }

    // find N that gives tolerance
    mysolver.init(m_N(j),rho_);
    vec num_lam = mysolver.solve();
    num_lam = sort(num_lam);
    if (max(num_lam - m_lambdas) < 1E-4){
      cout << "reached tolerance (1E-4) for N:" << " " << m_N(j) << endl;
      break;
    }
  }
}
