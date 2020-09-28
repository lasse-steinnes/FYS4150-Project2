#include "jacobimethodsolver.hpp"
#include<iostream>
#include<string>
#include<chrono>
using namespace std;
using namespace chrono;

//Setting up the superclass for Jacobi's method with rotational algorithm to be used in all derived classes

void JacobiMethodSolver::initialize(int N, double rho_max){
  //initialize variables to set up Jacobis algorithm
  //to be used in all derived classes
  m_N = N;
  rhoN = rho_max;
  h = (double) rhoN/(m_N+1);         //steplength m_N
  double hh = h*h;
  //creating matrix A
  A = zeros<mat>(m_N,m_N);
  m_rho = vec(m_N);
  for (int i = 0; i < m_N; ++i){    //n*n elements,n-1 highest index
      A(i,i) = 2; //diagonal elements
      m_rho(i) = (i+1)*h;
  }
  for (int i = 0; i < m_N-1; ++i){
      A(i+1,i) = -1; // Fill in for elemnts below diag
      A(i,i+1) = -1; // Fill in for elements above diag
  }
  A = (1/hh)*A;
}

void JacobiMethodSolver::write_eigenvectors_to_file(){
  vec eigval_start;
  mat eigvec_start;
  eig_sym(eigval_start,eigvec_start,A);
  ofstream myfile;
  string filename("./Results/eigenvectors" + to_string(m_N) + task + ".txt");
  myfile.open(filename);
  myfile << "rho_max " << rhoN << "\n";
  myfile << "omega_r " << omega_r << "\n";
  myfile << "Eigevectors";
  myfile << "\n";
  myfile << eigvec_start;
  myfile << "\n";
  myfile.close();
}


//finding maximal absolute offdiagonal element of matrix A, and its specific
//index (k,l), returns the time it took to find the element
duration<double, milli> JacobiMethodSolver::max_offdiag_element(){
  double max_val = 0.0;
  duration<double, milli> max_diag;
  auto start = chrono::high_resolution_clock::now(); // Start timer
  for (int i = 0; i < m_N; i++){
    for (int j = i+1; j < m_N; j++){
      double offdiag_ij = fabs(A(i,j));
      if (offdiag_ij > max_val){
        max_val = offdiag_ij;
        k = i;
        l = j;
      }
    }
  }
  max_offdiag = max_val;
  auto finish = chrono::high_resolution_clock::now(); // End timer
  max_diag = finish - start;
  return max_diag;
}

//updating the elements of matrix A by rotating around the elements given index (k,l)
// returns the time it took to rotate the matrix
duration<double, milli> JacobiMethodSolver::rotating_matrixA(){
  double tau, t, c, s;
  if (A(k,l) != (double) 0){
    tau = (A(l,l) - A(k,k))/(2*A(k,l));
    if (tau >= 0){
      t = 1/(tau + sqrt(1 + tau*tau));
    }
    else{
      t = 1/(tau - sqrt(1 + tau*tau));
    }
    c = 1/(sqrt(1 + t*t));
    s = t*c;
  }
  else{
    c = (double) 1;
    s = (double) 0;
  }
  //updating the matrix A
  A(k,k) = A(k,k)*c*c - 2*A(k,l)*c*s + A(l,l)*s*s;
  A(l,l) = A(l,l)*c*c + 2*A(k,l)*c*s + A(k,k)*s*s;
  A(k,l) = A(l,k) = (double) 0;

  duration<double, milli> rotate;
  auto start = chrono::high_resolution_clock::now(); // Start timer
  for (int i = 0; i < m_N; i ++){
    if (i != k && i != l){
      double aik = A(i,k);
      double ail = A(i,l);
      A(i,k) = aik*c - ail*s;
      A(i,l) = ail*c + aik*s;
      A(k,i) = A(i,k);
      A(l,i) = A(i,l);
    }
  }
  auto finish = chrono::high_resolution_clock::now(); // End timer
  rotate = finish - start;
  return rotate;
}

double Mean(vector<double> v) { // Method for finding mean of a vector
  double mean = accumulate(v.begin(), v.end(), 0./v.size());
  return mean;
}

double Std(vector<double> v) { //Method for finding the standard deviance
  double sq_sum = inner_product(v.begin(), v.end(), v.begin(), 0.0);
  double st_dev = sqrt(sq_sum/(v.size() - Mean(v) * Mean(v)));

  return st_dev;
}

vector<double> JacobiMethodSolver::analytic_eigenvalues() {
  vector<double> an_val;
  double d = 2./(h*h);
  double a = -1./(h*h);
  for(int i = 0; i < m_N; i++) {
    an_val.insert(an_val.begin() + i, d + (2*a*cos((M_PI*i)/m_N)));
  }
  return an_val;
}

vector<double> JacobiMethodSolver::solve(){
  double tol = 1.0E-10;
  transformations = 0;
  max_offdiag = 1;
  clock_t start, finish;
  start = clock();
  while (max_offdiag > tol){
    time_max.insert(time_max.begin() + transformations, max_offdiag_element().count()); // Inserting time used for calulations each time the method is called into vector.
    time_rotate.insert(time_rotate.begin() + transformations, rotating_matrixA().count()); // Inserting time used for calulations each time the method is called into vector.
    transformations++;
  }
  finish = clock();
  cpu_time_jacobi = 1000.0 * (finish - start)/CLOCKS_PER_SEC;  //computing CPU cpu_time_jacobi
  write_relative_error_to_file();

  return get_eigenvalues(A, m_N);
}

void JacobiMethodSolver::write_relative_error_to_file() {
  vector<double> an_val = analytic_eigenvalues();
  vector<double> n_val = get_eigenvalues(A, m_N);
  vector<double> relative_error;
  cout << "Writing relative error to file: relativeerror_lambda" + to_string(m_N) + task + ".txt" << "\n";
  ofstream file;
  file.open("./Results/relativeerror_lambda" + to_string(m_N) + ".txt");

  for (int i=0;i<m_N; i++){
    relative_error.insert(relative_error.begin() + i, abs((an_val[i] - n_val[i]))/an_val[i]);
    file << "n = " << i << " Analytic eigenvalue: " << n_val[i] << ", Numerical eigenvalue: " << an_val[i] << ", Relative error: " << relative_error[i] << "\n";
  }
}

void JacobiMethodSolver::write_eigenvalues_and_rho_to_file(){
  auto start = chrono::high_resolution_clock::now();
  vec eigval_final = eig_sym(A);
  auto finish = chrono::high_resolution_clock::now();
  double cpu_time_arma = duration_cast<milliseconds>(finish-start).count();

  ofstream file;
  cout << "Writing CPU times to file: CPU_time" + to_string(m_N) + ".txt" << "\n";
  file.open("./Results/CPU_time" + to_string(m_N) + ".txt");
  file << "Average CPU time + std to find the maximum offdiagonal element: " << Mean(time_max) << "ms, " << Std(time_max) << "ms" << "\n";
  file << "Average CPU time + std to rotate the matrix: " << Mean(time_rotate) << "ms, " << Std(time_rotate) << "ms" << "\n";
  file << "CPU time for Jacobi method: " << cpu_time_jacobi << "ms" << "\n";
  file << "CPU time for finding eigenvalues with armadillo: " << cpu_time_arma << "ms" <<"\n";
  file.close();


  ofstream myfile;
  cout << "Writing eigenvalues and rho-values to file: eigenvalues_rho" + to_string(m_N) + task + ".txt" << "\n";
  string filename("./Results/eigenvalues_rho" + to_string(m_N) + task + ".txt");
  myfile.open(filename);
  myfile << "rho_max " << rhoN << "\n";
  myfile << "omega_r " << omega_r << "\n";
  myfile << "Eigenvalues" << " " << "rho";
  myfile << "\n";
  for (int i = 0; i < m_N; i++){
    myfile << eigval_final(i) << " " << m_rho(i);
    myfile << "\n";
  }
  myfile.close();
  get_eigenvalues(A, m_N);
}

vector<double> JacobiMethodSolver::get_eigenvalues(mat A, int m_N) {
  vector<double> eigenvalues;
  for(int i = 0; i < m_N; i++) {
    eigenvalues.insert(eigenvalues.begin() + i, A(i, i));
  }
  sort(eigenvalues.begin(), eigenvalues.end());
  return eigenvalues;
}
