#include <iostream>
#include <mpi.h>

using namespace std;

int main(int nargs, char **args)
{

  size_t i, j;

  int M = 3, N = 3;
  int **A;

  int rank, size;
  MPI_Init(&nargs, &args);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0){
    A    = new int*[M];
    A[0] = new int[M*N];
    for (i = 1; i < M; i++){
      A[i] = &A[0][i*N];
    }

    for (i = 0; i < M; i++){
      for (j = 0; j < N; j++){
        A[i][j] = i+1;
      }
    }
  }

  if (rank == 1){
    A = new int*[M-1];
    A[0] = new int[(M-1)*N];
    for (i = 1; i < M-1; i++){
      A[i] = &A[0][i*N];
    }
  }

  int counts_send[size], displacements[size];

  counts_send[0] = (M-1)*N;
  counts_send[1] = counts_send[0];

  displacements[0] = 0;
  displacements[1] = N;

  MPI_Scatterv(A[0], counts_send, displacements, MPI_INT, A[0], counts_send[rank], MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == 0){
    cout << "A on process 0" << endl;
    for (i = 0; i < M; i++){
      for (j = 0; j < N; j++){
        cout << A[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }

  if (rank == 1){
    cout << "A on process 1" << endl;
    for (i = 0; i < M-1; i++){
      for (j = 0; j < N; j++){
        cout << A[i][j] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }

  return 0;
}
