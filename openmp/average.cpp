#include <iostream>
#include "omp.h"

using namespace std;

int main(){
  double ave = 0;
  int A[5] = {1,2,3,4,5};
  double start = omp_get_wtime();
  #pragma omp parallel for reduction(+:ave)
  for (int i = 0; i < 5; i++){
    ave += A[i];
  }

  ave /= 5;

  cout << ave << endl;
  cout << omp_get_wtime() - start << endl;
  return 0;
}
