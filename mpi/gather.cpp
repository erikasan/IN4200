#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int argc, char **argv)
{
  int rank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size != 4){
    cout << "Example is designed for 4 processes" << endl;
    MPI_Finalize();
    exit(0);
  }

  // A is the send buffer and B is the receive buffer
  int A[4]{}, B[4]{};

  A[0] = rank;

  int root = 0; // Define a root process

  MPI_Gather(A, 1, MPI_INT, B, 1, MPI_INT, root, MPI_COMM_WORLD);

  printf("Rank %d B = {%d, %d, %d, %d}\n", rank, B[0], B[1], B[2], B[3]);

  MPI_Finalize();
  return 0;
}
