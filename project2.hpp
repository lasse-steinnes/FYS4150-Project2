#ifndef project2_HPP
#define project2_HPP
#include "armadillo"

using namespace arma;

class Project2 {
private:
  double m_a, m_b, m_c;
  double *m_v, *m_g, m_h;
  int m_N;      //Number of integration points.
  double *m_rho;

public:
  void diagonalize_A(double ai, double bi, double ci, int N);
  void initialize(double rho0, double rhoN, int N, double ai, double bi, double ci);
  void analytic_eigenpairs(int N);
};

#endif
