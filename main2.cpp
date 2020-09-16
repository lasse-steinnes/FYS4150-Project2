#include "project2.hpp"
#include <iostream>
#include <cmath>
#include "time.h"
#include "armadillo"

using namespace arma;

using namespace std;


int main(int argc, char const *argv[]) { //our main function
  double rho0 = 0;   //Start point
  double rhoN = 1;   //End point
  int N;           //Number of grid points

  double ai = -1;  //elements on the lower diagonal
  double bi = 2;   //elements on the main diagonal
  double ci = -1;  //elements on the upper diagonal

  Project2 Solver;
  int task;
  cout << "Press 1 to diagonalize the matrix and compare with analytic results \n";
  cout << "Enter number:" << " ";
  cin >> task;

  if (task==1){
    cout << "Number of grid points (N) = ";
    cin >> N;    //giving the number of grid points
    Solver.initialize(rho0,rhoN,N,ai,bi,ci);
    Solver.diagonalize_A(ai, bi, ci, N);
    Solver.analytic_eigenpairs(N);
  }

}
