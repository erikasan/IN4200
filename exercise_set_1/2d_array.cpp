/* Assigning values to an m x n - matrix. */

#include <iostream>

using namespace std;

int main(){

  int m, n;
  int** A;
  int** B;

  cout << "Enter the dimensions of the matrix." << endl;
  cout << "m = "; cin >> m;
  cout << "n = "; cin >> n;

  A = new int*[m];
  B = new int*[m];
  for (int i = 0; i < m; i++){
    A[i] = new int[n];
    B[i] = new int[n];
  }

  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      A[i][j] = i - j;
    }
  }

  // Swapping the for-loops
  for (int j = 0; j < n; j++){
    for (int i = 0; i < n; i++){
      B[i][j] = i - j;
    }
  }

  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      cout << A[i][j] << " " << B[i][j] << endl;
    }
  }

  return 0;
}
