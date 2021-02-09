#include <iostream>

using namespace std;

int main(){
  const int n = 100;
  const int m = 100;
  const int p = 100;

  double A[n][m];
  double B[m][p];
  double C[n][p];

  double tmp = 0;
  for (int i = 0; i < n; i++){
    for (int j = 0; j < p; j++){
      for (int k = 0; k < m; k++){
        tmp += A[i][k]*B[k][j];
      }
      C[i][j] = tmp;
      tmp = 0;
    }
  }

  return 0;
}
