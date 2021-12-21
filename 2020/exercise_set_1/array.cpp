/* Allocating a 1D array of length n which is prescribed at runtime using random numbers. */
/* Then finding the maximum and minimum values of the array. */

#include <iostream>
#include <random>

using namespace std;

int main(){

  int n;
  int min, max;
  int imin, imax;

  cout << "Enter the number of array elements. n = ";
  cin  >> n;

  int* arr = new int[n];
  default_random_engine generator;
  uniform_int_distribution<int> distribution(0, n);

  min = n;
  max = 0;

  for (int i = 0; i < n; i++){
    arr[i] = distribution(generator);
  }

  for (int i = 0; i < n; i++){
    if (min > arr[i]){
      min  = arr[i];
      imin = i;
    }

    if (max < arr[i]){
      max  = arr[i];
      imax = i;
    }
  }

  for (int i = 0; i < n; i++){
    cout << "arr[" << i << "] = " << arr[i] << endl;
  }

  cout << endl;
  cout << "min array value " << min << " at index " << imin << endl;
  cout << "max array value " << max << " at index " << imax << endl;

  return 0;
}
