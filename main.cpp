#include "jacobimethodsolver.hpp"
#include <cmath>
#include <string>
#include <time.h>
#include <armadillo>

using namespace arma;


int main(int argc, char const *argv[]){
  int task;
  cout << "Press 0 to run superclass \n";
  cout << "Press 1 to run task b) \n";
  cout << "Press 2 to run task d) \n";           //asking which task you want to run
  cout << "Press 3 to run task e) \n";
  cout << "Enter number:" << " ";
  cin >> task;

  int N;
  //run task b)
  if (task==0){
    JacobiMethodSolver mysolver;
    cout << "Number of grid points (N) = ";
    cin >> N;
    mysolver.initialize(N);
  }

  if (task==1){
    BucklingBeamSolver mysolver;
    cout << "Number of grid points (N) = ";
    cin >> N;
    mysolver.init(N);
    mysolver.solve();
    //mysolver.write_transformation_func_to_file();

  }

  //run task d)
  if (task==2){
    OneElectronSolver mysolver;
  }

  //run task e)
  if (task==3){
    TwoElectronsSolver mysolver;

  }

  return 0;
}
