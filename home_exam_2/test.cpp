#include <mpi.h>
#include <iostream>

using namespace std;

int main(int nargs, char **args)
{
  size_t i, j;
  int M = 2, N = 2, rank;
  double **A = NULL;

  MPI_Init(&nargs, &args);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0){
    cout << "A allocated on process " << rank << endl;
    A = new double*[M];
    for (i = 0; i < M; i++){
      A[i] = new double[N]{};
      A[i][i] = 1;
    }
  }

  if (rank > 0){
    cout << "A allocated on process " << rank << endl;
    A = new double*[M];
    for (i = 0; i < M; i++){
      A[i] = new double[N];
    }
  }

  MPI_Bcast(&A, M*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if (rank > 0){
    cout << "A on process " << rank << endl;
    for (i = 0; i < M; i++){
      for (j = 0; j < N; j++){
        cout << A[i][j] << " ";
      }
      cout << endl << endl;
    }
  }

  MPI_Finalize();
  return 0;
}
