#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  int root = 0;
  int rank, size, i;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  double partial_sum = 0;
  double sum = 0;

  int A[] = {1,2,3};
  for (i = 0; i < 3; i++){
    partial_sum += A[i];
  }

  MPI_Reduce(&send_data, &sum, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);

  if (rank == root){
    cout << "Sum = " << sum << endl;
    cout << "Expected = " << 6*size << endl;
  }

  MPI_Finalize();
  return 0;
}
