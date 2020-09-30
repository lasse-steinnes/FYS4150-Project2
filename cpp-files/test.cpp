#include "catch.hpp"
#include "jacobimethodsolver.hpp"
#include<iostream>

TEST_CASE( "Testing eigenvalues") {
  JacobiMethodSolver mysolver;
  mat A = mysolver.initialize(5, 1);
  vec eigval = eig_sym(A);
  vector<double> exact; //Caluclated by hand for matrix A
  double tol = 1E-04;

  exact.insert(exact.begin(), 9.64617);
  exact.insert(exact.begin() + 1, 35.99999);
  exact.insert(exact.begin() + 2, 72);
  exact.insert(exact.begin() + 3, 107.99999);
  exact.insert(exact.begin() + 4, 134.35382);

  for(int i = 0; i < 5; i++) {
    REQUIRE((eigval[i] - exact[i]) < tol); //Check to see if each eigenvalue passes the approximation test
  }
}

TEST_CASE("Checking max offdiagonal element") {
  JacobiMethodSolver mysolver;
  mat A = mysolver.initialize(5, 1);
  double val = mysolver.max_offdiag_element(); //Returns max offdiagonal element which is supposed to be 36.
  double exact = 36;
  double tol = 1E-14;

  REQUIRE((val - exact) < tol); //Check to see if max_offdiag_element() returns the correct element

}
