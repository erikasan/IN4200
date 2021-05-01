#include <mpi.h>
#include <cstdlib>

using namespace std;

int main(int nargs, char **args)
{
  int M = 0, N = 0, K = 0, rank, size;

  float **input = NULL, **output = NULL, **kernel = NULL;

  MPI_Init(&nargs, &args);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0){
    // read from command line the values of M, N, and K
    M = atoi(argv[1]);
    N = atoi(argv[2]);
    K = atoi(argv[3]);

    // allocate 2D array 'input' with M rows and N columns


    // allocate 2D array 'output' with M - K + 1 rows and N - K + 1 columns
    // allocate the convolutional kernel with K rows and K columns
    // fill 2D array 'input' with some values
    // fill kernel with some values
    // ....
  }

  // process 0 broadcasts values of M, N, K to all other processes
  // ....

  if (rank > 0){
    // allocate the convolutional kernel with K rows and K columns
    // ...
  }

  // process 0 broadcasts the content of the kernel to all other processes
  // ...

  // parallel computation of a single-layer convolution
  // MPI_single_layer_convolution(M, N, input, K, kernel, output);

  if (rank == 0){
    // For example, compare the content of array 'output' with what is
    // produced by the sequential function single_layer_convolution
    // ...
  }

  MPI_Finalize();
  return 0;
}
