#include "omp.h"
#include <cmath>
#include <iostream>

using namespace std;

int main(){
  int i;
  double x = 100000000000;
  int N = (int) sqrt(x);
  double a[N], b[N];

  double num_threads;

  double start = omp_get_wtime();
  #pragma omp parallel
  {
    #pragma omp for
    for (i = 0; i < N; i++){
      a[i] = i;
    }

    #pragma omp for
    for(i = 0; i < (int) sqrt(x); i++){
      a[i] = 2.3*x;
      if (i < 10) b[i] = a[i];
    }
  }


  cout << omp_get_wtime() - start << endl;

  return 0;
}
