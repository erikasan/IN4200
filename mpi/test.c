#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  int rank, size, i;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int A[4], B[4];

  for (i = 0; i < 4; i++){
    A[i] = 0;
    B[i] = 0;
  }

  int root = 0;

  if (rank == root){
    A[0] = 3;
    A[1] = 5;
    A[2] = 4;
    A[3] = 1;
  }

  MPI_Scatter(A, 1, MPI_INT, B, 1, MPI_INT, root, MPI_COMM_WORLD);

  printf("Rank %d: B = {%d, %d, %d, %d} \n", rank, B[0], B[1], B[2], B[3]);

  MPI_Finalize();
  return 0;
}
