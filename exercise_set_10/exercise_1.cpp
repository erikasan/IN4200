#include <mpi.h>
#include <iostream>
#include <cstdio>

using namespace std;

int main(int argc, char **argv)
{
  int rank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int message_len = 20;
  char message[message_len];
  MPI_Status *status;

  if (rank > 0){
    sprintf(message, "Hello world! I'm process %d", rank);
    MPI_Send(message, message_len, MPI_CHAR, 0, MPI_ANY_TAG, MPI_COMM_WORLD);
  }

  if (rank == 0){
    for (int i = 1; i < size; i++){
      MPI_Recv(message, message_len, MPI_CHAR, i, MPI_ANY_TAG, MPI_COMM_WORLD, status);
      printf(message);
    }
  }

  MPI_Finalize();
  return 0;
}
