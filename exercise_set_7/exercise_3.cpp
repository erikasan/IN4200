#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

void dense_mat_vec(int m, int n, double *x, double *A, double *y){
  int i, j;
  int num_threads;
  #pragma omp parallel
  {

    #pragma omp for private(j)
    for (i = 0; i < m; i++){
      double tmp = 0.;

      for (j = 0; j < n; j++){
        tmp += A[i*n + j]*y[j];
      }

      x[i] = tmp;

    }
  }

}

int main(){
  int m, n;
  cout << "Enter two positive integers m and n: ";
  cin >> m >> n;

  double x[m], y[n], A[m*n];

  std::default_random_engine generator(2021);
  std::uniform_int_distribution<int> distribution(-5,5);

  for (int i = 0; i < m; i++){
    x[i] = distribution(generator);
  }
  for (int i = 0; i < n; i++){
    y[i] = distribution(generator);
  }
  for (int i = 0; i < m*n; i++){
    A[i] = distribution(generator);
  }

  double start = omp_get_wtime();
  dense_mat_vec(m, n, x, y, A);
  cout << omp_get_wtime() - start << endl;
  return 0;
}
