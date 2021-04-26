#include <mpi.h>
#include <iostream>
#include <cstdlib>

using namespace std;

#define idx(i,j) (i*N + j)

void mat_vec_mult(double *A, double *x, double *y, int N);

int main(int argc, char **argv)
{
  int i, j, N;
  int rank, size;
  int root = 0;

  N = atoi(argv[1]);

  double *A, x[N];

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == root){
    A = new double[N*N];
    for (i = 0; i < N; i++){
      for (j = 0; j < N; j++){
        A[idx(i,j)] = 0;
      }
      A[idx(i,j)] = 1;
      x[i]        = i;
    }
  }

  //Broadcast x to all processes
  MPI_Bcast(x, N, MPI_DOUBLE, root, MPI_COMM_WORLD);


  // Split up A
  //MPI_Scatter();

  int rows = N/size;
  int remainder = N%size;
  int n_rows[N];
  int sendcounts[N];
  int Sdispls[N];
  int Gdispls[N];

  for (i = 0; i < size-1; i++){
    n_rows[i] = rows; //+ ((i >= (size - remainder)) ? 1:0);
    sendcounts[i] = n_rows[i]*N;
    Sdispls[i+1] = Sdispls[i] + sendcounts[i];
    Gdispls[i+1] = Gdispls[i] + n_rows[i];
  }
  n_rows[size-1] = rows + remainder;//+ ((size-1) >= (size - remainder) ? 1:0);
  sendcounts[size-1] = n_rows[size-1]*N;

  MPI_Scatterv(A, sendcounts, Sdispls, MPI_DOUBLE, A, N*n_rows[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

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
