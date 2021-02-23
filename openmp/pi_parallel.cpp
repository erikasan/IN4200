#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
  int num_steps = 100000;
  double step = (double) 1/num_steps;

  int num_threads = 4;
  int steps_per_thread = num_steps/num_threads;

  double pi, sum[num_threads];

  omp_set_num_threads(4);
  #pragma omp parallel
  {

    int ID = omp_get_thread_num();

    double x;
    for (int i = ID*steps_per_thread; i < (ID + 1)*steps_per_thread; i++){
      x = (i + 0.5)*step;
      sum[ID] += 4/(1 + x*x);
    }
  }

  for (int i = 0; i < num_threads; i++){
    pi += sum[i];
  }
  pi *= step;
  cout << "pi = " << pi << endl;

  return 0;
}
