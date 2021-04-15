#include <mpi.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int message[2]; // buffer for sending and receiving messages
  int dest, src;  // destination and source process variables
  int tag = 0;
  MPI_Status status;

  // This example has to be run on more than one process
  if (size == 1){
    cout << "This example requires more than one process to execute" << endl;
    MPI_Finalize();
    exit(0);
  }

  // If not rank 0, send message to rank 0
  if (rank != 0){
    message[0] = rank;
    message[1] = size;
    dest = 0; // send all messages to rank 0
    MPI_Send(message, 2, MPI_INT, dest, tag, MPI_COMM_WORLD);
  }

  // If rank 0, receive messages from everybody else
  else{
    for (src = 1; src < size; src++){
      MPI_Recv(message, 2, MPI_INT, src, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      rank = message[0];
      size = message[1];
      cout << "Hello from process " << rank << " out of " << size << endl;
    }
  }

  MPI_Finalize();
  return 0;
}
