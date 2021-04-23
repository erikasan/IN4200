#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  int rank, size, i;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_size, &size);

  double A[size]; // pregather
  double B[size]; // postgather

  int numbers[] = {1,2,3};

  for (i = 0; i < 3; i++){
    A[0] += numbers[i];
  }

  MPI_Gather(A, 1, MPI_INT, B, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank == 0){
    double sum = 0;
    for (i = 0; i < 3; i++){
      sum += B[i];
    }
    cout << "Sum = " << sum << endl;
    cout << "Expected = " << 6*size << endl;
  }

  MPI_Finalize();
  return 0;
}
