/* Allocating values to a 3D array. */

#include <iostream>

using namespace std;

int main(){

  int nx, ny, nz;

  cout << "nx = "; cin >> nx;
  cout << "ny = "; cin >> ny;
  cout << "nz = "; cin >> nz;

  int*** u;

  u = new int**[nx];
  for (int i = 0; i < nx; i++){
    u[i] = new int*[ny];
    for (int j = 0; j < ny; j++){
      u[i][j] = new int[nz];
    }
  }

  for (int i = 0; i < nx; i++){
  for (int j = 0; j < ny; j++){
  for (int k = 0; k < nz; k++){
    u[i][j][k] = i*ny*nz + j*nz + k;
  }}}

  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      delete[] u[i][j];
    }
    delete[] u[i];
  }

  delete[] u;

  return 0;
}
