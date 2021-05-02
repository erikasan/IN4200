#include <mpi.h>
#include <cstdlib>
#include "MPI_single_layer_convolution.cpp"

#include <iostream>

using namespace std;

int main(int nargs, char **args)
{
  int M = 0, N = 0, K = 0, rank;

  float **input = NULL, **output = NULL, **kernel = NULL;

  size_t i, j;

  MPI_Init(&nargs, &args);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0){
    // read from command line the values of M, N, and K
    M = atoi(args[1]);
    N = atoi(args[2]);
    K = atoi(args[3]);

    // allocate 2D array 'input' with M rows and N columns
    input    = new float*[M];
    input[0] = new float[M*N];
    for (i = 1; i < M; i++){
      input[i] = &input[0][i*N];
    }

    // allocate 2D array 'output' with M - K + 1 rows and N - K + 1 columns
    output    = new float*[M - K + 1];
    output[0] = new float[(M - K + 1)*(N - K + 1)];
    for (i = 1; i < M - K + 1; i++){
      output[i] = &output[0][i*(N - K + 1)];
    }

    // allocate the convolutional kernel with K rows and K columns
    kernel    = new float*[K];
    kernel[0] = new float[K*K];
    for (i = 1; i < K; i++){
      kernel[i] = &kernel[0][i*K];
    }

    // fill 2D array 'input' with some values
    for (i = 0; i < M; i++){
    for (j = 0; j < N; j++){
      input[i][j] = 1;
    }}

    // fill kernel with some values
    for (i = 0; i < K; i++){
    for (j = 0; j < K; j++){
      kernel[i][j] = 1;
    }}
  }

  // process 0 broadcasts values of M, N, K to all other processes
  MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&K, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank > 0){
    // allocate the convolutional kernel with K rows and K columns
    kernel    = new float*[K];
    kernel[0] = new float[K*K];
    for (i = 1; i < K; i++){
      kernel[i] = &kernel[0][i*K];
    }
  }

  // process 0 broadcasts the content of the kernel to all other processes
  MPI_Bcast(kernel[0], K*K, MPI_FLOAT, 0, MPI_COMM_WORLD);

  // parallel computation of a single-layer convolution
  MPI_single_layer_convolution(M, N, input,
                               K, kernel,
                               output);

  if (rank == 0){
    // For example, compare the content of array 'output' with what is
    // produced by the sequential function single_layer_convolution
    // ...
  }

  MPI_Finalize();
  return 0;
}
