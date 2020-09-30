#ifndef OptimizeParams_HPP
#define OptimizeParams_HPP
#include <armadillo>

using namespace arma;

class OptimizeParams{
  protected:
    vec m_rho, m_N;
    vec m_lambdas;
  public: //only use void functions and rather just cout
    void initialize();
    void optimize_rho();
    void optimize_n();
  };

#endif
