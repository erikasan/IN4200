#include <iostream>
#include <ctime>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(){
  int N_iterations = (int) 1e4;
  const int n = 10;

  int a[n] = {1,2,3,4,5,6,7,8,9,10};
  int b[n];

  time_t start_hand_copy,
         stop_hand_copy,
         start_memcpy,
         stop_memcpy;

  start_hand_copy = clock();
  for (int j = 0; j < N_iterations; j++){
    for (int i = 0; i < n; i++){
      b[i] = a[i];
    }
  }
  stop_hand_copy = clock();

  start_memcpy = clock();
  for (int j = 0; j < N_iterations; j++){
    memcpy(b, a, n);
  }
  stop_memcpy = clock();

  auto diff_hand_copy = difftime(stop_hand_copy, start_hand_copy);
  auto diff_memcpy    = difftime(stop_memcpy, start_memcpy);
  auto ratio = diff_hand_copy/diff_memcpy;

  cout << "Hand copy clock cycles: " << diff_hand_copy << endl;
  cout << "memcpy clock cycles: " << diff_memcpy << endl;
  cout << "Ratio: " << ratio << endl;

  return 0;
}
