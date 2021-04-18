#include <mpi.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  int rank, size, i, id;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (size != 4){
    printf("This example is designed for 4 processes\n");
    MPI_Finalize();
    exit(0);
  }

  int A[4], B[4];
  for (i = 0; i < 4; i++){
    A[i] = i + 1 + 4*rank;
  }

  // Note that the send number and receive number are both one.
  // This reflects the fact that the send size and receive size
  // refer to the distinct data size sent to each process.
  MPI_Alltoall(A, 1, MPI_INT, B, 1, MPI_INT, MPI_COMM_WORLD);

  for (id = 0; id < size; id++){
    for (i = 0; i < 4; i++){
      if (rank == id){
        printf("%d ", A[i]);
      }
    }
    printf("\n");
  }

  return 0;
}
