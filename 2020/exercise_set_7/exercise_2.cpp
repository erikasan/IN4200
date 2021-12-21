#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

int main(){

  std::default_random_engine generator(2021);
  std::uniform_int_distribution<int> distribution(-2,2);

  double dotp = 0;
  int n = 100000;
  int a[n], b[n];

  double start = omp_get_wtime();

  int num_threads;

  for (int i = 0; i < n; i++){
    a[i] = distribution(generator);
    b[i] = distribution(generator);
  }

  int chunk_size = 1;
  #pragma omp parallel for schedule(static) reduction(+:dotp)
  for (int i = 0; i < n; i++){
    dotp += a[i]*b[i];
  }
  cout << dotp << endl;
  cout << omp_get_wtime() - start << endl;

  return 0;
}
