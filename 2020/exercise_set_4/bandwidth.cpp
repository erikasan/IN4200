#include <iostream>
#include <ctime>

using namespace std;

int main(){

  int numberOfFlops = 1;
  int numberOfLoadsOrStores = 2;

  double codeBalance = (double) numberOfLoadsOrStores/numberOfFlops;
  double time, bandwidth;

  int iterations = (int) 1e8;
  const int N = (int) 1e2;
  double A[N];
  double B[N];
  double s = -43;

  clock_t start, total;

  for (int i = 0; i < N; i++){
    B[i] = i*s - i*i + 3;
  }

  start = clock();
  for (int k = 0; k < iterations; k++)
    for (int i = 0; i < N; i++){
      A[i] = s*B[i];
  }
  total = clock() - start;

  time = total/CLOCKS_PER_SEC;
  time /= iterations;

  bandwidth = codeBalance*numberOfFlops/time;
  bandwidth /= 8; //Convert from Words to Bytes
  bandwidth /= 1000; // Convert from Bytes to KBytes

  cout << "Estimated bandwidth = " << bandwidth << " KBytes/s" << endl;


  return 0;
}
