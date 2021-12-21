#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

double powpow(double x);

int main(){
  double x = 0.999;
  int iterations = (int) 1e7;

  clock_t start, total;

  start = clock();
  for (int i = 0; i < iterations; i++){
    powpow(x);
  }
  total = clock() - start;

  double total_powpow = (double) total/(iterations*CLOCKS_PER_SEC);

  start = clock();
  for (int i = 0; i < iterations; i++){
    pow(x, 100);
  }
  total = clock() - start;

  double total_pow = (double) total/(iterations*CLOCKS_PER_SEC);

  double ratio = (double) total_pow/total_powpow;

  cout << "pow time = " << total_pow << endl;
  cout << "powpow time = " << total_powpow << endl;
  cout << "ratio = " << ratio << endl;

  return 0;
}

double powpow(double x){
  x = x*x;        // x^2
  double a = x*x; // x^4
  x = a*a;        // x^8
  x = x*x;        // x^16
  double b = x*x; // x^32
  x = b*b;        // x^64
  return x*b*a;   // x^(64 + 32 + 4) = x^100
}
