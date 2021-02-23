#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
  int num_steps = 100000;
  double x, pi, sum = 0;
  double step = (double) 1/num_steps;

  for (int i = 0; i < num_steps; i++){
    x = (i + 0.5)*step;
    sum += 4/(1 + x*x);
  }
  pi = step*sum;
  cout << "pi = " << pi << endl;

  return 0;
}
