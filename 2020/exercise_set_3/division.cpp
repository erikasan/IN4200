#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

clock_t numerical_integration(double x_min, double x_max, int slices);

int main(){

  double pi = 4*atan(1);
  double integral;
  int max_iterations = 1;

  /* First part of the task */
  // for (int i = 10; i <= max_iterations; i *= 10){
  //   integral = numerical_integration(0, 1, i);
  //   cout << "Iterations: " << i
  //        << " Integral = " << integral
  //        << " Error = "    << integral - pi
  //        << endl;
  // }

  cout << "Estimated latency = " << (double) numerical_integration(0, 1, max_iterations)/max_iterations << " clock cycles" << endl;

  return 0;
}

clock_t numerical_integration(double x_min, double x_max, int slices){
  double delta_x = (double) (x_max - x_min)/slices;
  double x, sum = 0.0;

  double denominator, tmp;
  clock_t start_time, total_time = 0;
  for (int i = 0; i < slices; i++){
    x = x_min + (i + 0.5)*delta_x;

    denominator = 1.0 + x*x;

    start_time = clock();
    tmp = 4.0/denominator;
    total_time += clock() - start_time;

    sum += tmp;
  }
  //return sum*delta_x;
  return total_time;
}
