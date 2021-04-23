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

  int msg_len = 256;
  char msg[msg_len];
  MPI_Status status;

  if (rank > 0){
    sprintf(msg, "Hello world! I'm process %d", rank);
    MPI_Send(msg, msg_len, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }

  else{
    for (int i = 1; i < size; i++){
      MPI_Probe(i, 0, MPI_COMM_WORLD, &status);
      MPI_Get_count(&status, MPI_CHAR, &msg_len);
      MPI_Recv(msg, msg_len, MPI_CHAR, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      cout << msg << endl;
    }
  }

  MPI_Finalize();
  return 0;
}
