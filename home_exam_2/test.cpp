#include <mpi.h>
#include <iostream>

using namespace std;

int main(int nargs, char **args)
{
  size_t i, j;
  int M = 2, N = 2, rank, size;
  double **A = NULL;

  MPI_Init(&nargs, &args);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0){
    A = new double*[M];
    for (i = 0; i < M; i++){
      A[i] = new double[N]{};
      A[i][i] = 1;
    }
  }

  if (rank > 0){
    A = new double*[M];
    for (i = 0; i < M; i++){
      A[i] = new double[N];
    }
  }

  //MPI_Bcast(A, M*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  for (i = 0; i < size; i++){
    if (rank == i){
      cout << "A on process " << rank << endl;
      for (i = 0; i < M; i++){
        for (j = 0; j < N; j++){
          cout << A[i][j] << " ";
        }
        cout << endl << endl;
      }
    }
  }


  MPI_Finalize();
  return 0;
}
