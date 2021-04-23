#include <mpi.h>
#include <iostream>
#include <random>

using namespace std;

int main(int argc, char *argv)
{
  int rank, size, i;
  double sum = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int A[] = {1,2,3};
  for (i = 0; i < 3; i++){
    sum += A[i]; // sum = 6
  }

  if (rank > 0){
    MPI_Send(&sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }

  if (rank == 0){
    double tmp = 0;
    MPI_Status status;
    for (i = 1; i < size; i++){
      MPI_Recv(&tmp, 1, MPI_DOUBLE, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      sum += tmp;
    }
    cout << "Sum = " << sum << endl;
    cout << "Expected = " << 6*size << endl;
  }

  MPI_Finalize();
  return 0;
}
