#include <mpi.h>

int main(int nargs, char **args)
{
  int M = 0, N = 0, K = 0, my_rank;
  float **input = NULL, **output = NULL, **kernel = NULL;

  MPI_Init(&nargs, &args);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0){
    // read from command line the values of M, N and K
    // allocate 2D array 'input' with M rows and N columns
    // allocate 2D array 'output' with M - K + 1 rows and N - K + 1 columns
    // fill 2D array 'input' with some values
    // fill kernel with some values
    // ....
  }

  // process 0 broadcasts values of M, N, K to all the other processes
  // ...

  if (my_rank > 0){
    // allocated the convolutional kernel with K rows and K columns
    // ...
  }

  // process 0 broadcasts the content of the kernel to all the other processes
  // ...

  // parallel computation of the double-layer convolution
  MPI_double_layer_convolution(M, N, input, K, kernel, output);

  if (my_rank == 0){
    // For example, compare the content of array 'output' with what is
    // produced by the sequential function single_layer_convolution
    // ...
  }

  MPI_Finalize();
  return 0;
}
