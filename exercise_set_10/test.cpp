#include <mpi.h>
#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc, char **argv)
{
  int rank, size;
  int root = 0;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int B[3];
  if (rank == 0){
    int A[] = {1,2,3};
  }

  MPI_Scatter(A, 1, MPI_INT, B, 1, root, MPI_COMM_WORLD);

  cout << B[0] << endl;

  MPI_Finalize();
  return 0;
}
