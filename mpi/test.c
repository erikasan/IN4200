#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  int rank, size, i;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int A[4];

  // Initialize array
  for (i = 0; i < 4; i++){
    A[i] = 0;
  }

  if (rank == 0){
    A[0] = 3;
    A[1] = 5;
    A[2] = 4;
    A[3] = 1;
  }

  MPI_Bcast(A, 4, MPI_INT, root, MPI_COMM_WORLD);

  printf("Rank &d: A = {%d, %d, %d, %d} \n", rank, A[0], A[1], A[2], A[3]);

  MPI_Finalize();
  return 0;
}
