#include <mpi.h>
#include <iostream>
#include <cstdlib>

using namespace std;

void mat_vec_mult(double *A, double *x, double *y, int N);

int main(int argc, char **argv)
{
  int i, j;
  int rank, size;
  int root = 0;

  cout << "Enter N = " << endl;
  cin >> N;

  double **A, *x;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == root){
    A = new double*[N];
    x = new double[N];

    for (i = 0; i < N; i++){
      A[i] = new double[N]{};
      A[i][i] = 1;
      x[i] = i;
    }
  }

  //Broadcast x to all processes
  MPI_Bcast(x, N, MPI_INT, root, MPI_COMM_WORLD);

  //Test that broadcast works
  for (i = 0; i < size; i++){
    if (rank == i){
      for (j = 0; j < N; j++){
        cout << x[j] << " ";
      }
      cout << endl;
    }
  }

  // Split up A
  //MPI_Scatter();

  MPI_Finalize();
  return 0;
}

void mat_vec_mult(double *A, double *x, double *y, int N)
{
  *y = 0;
  for (int j = 0; j < N; j++){
    *y += A[j]*x[j];
  }
  return;
}
