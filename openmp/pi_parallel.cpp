#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
  int num_steps = 100000000;

  double step = (double) 1/num_steps;
  double x;

  double pi  = 0;
  double sum = 0;

  double start, total;

  start = omp_get_wtime();
  omp_set_num_threads(8);
  #pragma omp parallel private(x) firstprivate(sum)
  {

    #pragma omp for
    for (int i = 0; i < num_steps; i++){
      x = (i + 0.5)*step;
      sum += 4/(1 + x*x);
    }

    #pragma omp critical
    {
      pi += sum;
    }
  }

  pi *= step;

  total = omp_get_wtime() - start;


  cout << "pi = " << pi << endl;
  cout << "time = " << total << " s" << endl;

  return 0;
}
