#include "omp.h"
#include <cstdio>
#include <iostream>

using namespace std;

int main(){
  int N = 100000;
  double w = 1.0/N, x, approx_pi;
  double sum = 0;

  #pragma omp parallel private(x) firstprivate(sum)
  {

    #pragma omp for
    for (int i = 1; i <= N; i++){
      x = w*(i - 0.5);
      sum += 4.0/(1 + x*x);
    }

    #pragma omp critical
    {
      approx_pi += w*sum;
    }

  }

  cout << "pi = " << approx_pi << endl;

  return 0;
}
