#include "jacobimethodsolver.hpp"
#include "optimizeparams.hpp"
#include <cmath>
#include <string>
#include <time.h>
#include <armadillo>

using namespace arma;
using namespace std;


int main(int argc, char const *argv[]){
  int task;
  cout << "Press 0 to write number of matrix transformations as function of n to file \n";
  cout << "Press 1 to run task b) with the buckling beam \n";
  cout << "Press 2 to run task d) with one electron \n";           //asking which task you want to run
  cout << "Press 3 to run task e) with two electrons \n";
  cout << "Enter number:" << " ";
  cin >> task;

  int N;
  double rho_max = 1;

  if (task==0){
    BucklingBeamSolver mysolver;
    mysolver.write_trans_dims_to_file();
    cout << "Type: make plot2, to get a plot showing transformations as function of n" << "\n";
  }

  //run task b)
  if (task==1){
    BucklingBeamSolver mysolver;
    cout << "Solving the Buckling beam problem" << "\n";
    cout << "Number of grid points (N) = ";
    cin >> N;
    mysolver.init(N,rho_max);
    mysolver.write_eigenvectors_to_file();
    cout << "Running Jacobi's method..." << "\n";
    cout << "Finding maximal offdiagonal element..." << "\n";
    cout << "Rotating matrix A..." << "\n";
    mysolver.solve();
    mysolver.write_eigenvalues_and_rho_to_file();
    cout << "Type: make plot1, to get a plot of the eigenvector for the lowest eigenvalue" << "\n";
  }

  //run task d)
  if (task==2){
    string answ;
    cout << "Optimize parameters (yes/no)";
    cin >> answ;
    if (answ == "yes"){
      //initialize optimizer here
      OptimizeParams myopt;
      myopt.initialize();

      //run optimizer
      string opt;
      cout << "optimize param (rho/n)";
      cin >> opt;
      if (opt == "rho"){
        //optimize rho
        myopt.optimize_rho();
      } else{
        //optimize n
        myopt.optimize_n();
      }
    } else {
    OneElectronSolver mysolver;
    cout << "Number of grid points (N) = ";
    cin >> N;
    mysolver.init(N,rho_max);
    mysolver.write_eigenvectors_to_file();
    mysolver.solve();
    mysolver.write_eigenvalues_and_rho_to_file();
  }
}

  //run task e)
  if (task==3){
    TwoElectronsSolver mysolver;
    double omega;
    cout << "Number of grid points (N) = ";
    cin >> N;
    cout << "Oscillating frequency (w_r) = ";
    cin >> omega;
    mysolver.init(N,rho_max,omega);
    mysolver.write_eigenvectors_to_file();
    mysolver.solve();
    mysolver.write_eigenvalues_and_rho_to_file();
  }


  return 0;
}
