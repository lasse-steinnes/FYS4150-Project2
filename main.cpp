#include "jacobimethodsolver.hpp"
#include <cmath>
#include <string>
#include <time.h>
#include <armadillo>

using namespace arma;
using namespace std;


int main(int argc, char const *argv[]){
  int task;
  cout << "Press 0 to run superclass \n";
  cout << "Press 1 to run task b) \n";
  cout << "Press 2 to run task d) \n";           //asking which task you want to run
  cout << "Press 3 to run task e) \n";
  cout << "Enter number:" << " ";
  cin >> task;

  int N;
  double rho_max = 1;
  //run task b)
  if (task==0){
    JacobiMethodSolver mysolver;
    cout << "Number of grid points (N) = ";
    cin >> N;
    mysolver.initialize(N,rho_max);
  }

  if (task==1){
    BucklingBeamSolver mysolver;
    string check;
    cout << "Write transformations as function of n to file? (yes/no)";
    cin >> check;
    if (check=="yes"){
      mysolver.write_trans_dims_to_file();
    }
    else {
      cout << "Number of grid points (N) = ";
      cin >> N;
      mysolver.init(N,rho_max);
      mysolver.solve();
      mysolver.write_eigen_to_file();
    }
  }

  //run task d)
  if (task==2){
    OneElectronSolver mysolver;
    cout << "Number of grid points (N) = ";
    cin >> N;
    mysolver.init(N,rho_max);
    mysolver.solve();
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
    mysolver.solve();
    mysolver.write_eigen_to_file();
  }


  return 0;
}
