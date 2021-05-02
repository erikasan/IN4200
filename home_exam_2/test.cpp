#include <iostream>

using namespace std;

int main()
{
  int M = 2, N = 2;
  int **A;

  A    = new int*[M];
  A[0] = new int[M*N];
  for (int i = 1; i < M; i++){
    A[i] = &A[0][i*N];
  }

  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
      cout << i << " " << j << " " << &A[i][j] << endl;
    }
  }
  return 0;
}
