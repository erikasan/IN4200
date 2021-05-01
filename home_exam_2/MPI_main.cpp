#include <mpi.h>
#include <cstdlib>
#include "test.cpp"

using namespace std;

int main(int nargs, char **args)
{
  int M = 0, N = 0, K = 0, rank, size;

  float **input = NULL, **output = NULL, **kernel = NULL;

  size_t i, j;

  MPI_Init(&nargs, &args);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0){
    // read from command line the values of M, N, and K
    M = atoi(argv[1]);
    N = atoi(argv[2]);
    K = atoi(argv[3]);

    // allocate 2D array 'input' with M rows and N columns
    input = new float*[M];
    for (i = 0; i < M; i++){
      input[i] = new float[N];
    }

    // allocate 2D array 'output' with M - K + 1 rows and N - K + 1 columns
    output = new float*[M - K + 1];
    for (i = 0; i < M - K + 1; i++){
      output[i] = new float[M - K + 1];
    }

    // allocate the convolutional kernel with K rows and K columns
    kernel = new float*[K];
    for (i = 0; i < K; i++){
      kernel[i] = new float[K];
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
    kernel = new float*[K];
    for (i = 0; i < K; i++){
      kernel[i] = new float[K];
    }
  }

  // process 0 broadcasts the content of the kernel to all other processes
  for (i = 0; i < K; i++){
    MPI_Bcast(kernel[i], K, MPI_FLOAT, 0, MPI_COMM_WORLD);
  }


  // parallel computation of a single-layer convolution
  // MPI_single_layer_convolution(M, N, input, K, kernel, output);
  test(rank);

  if (rank == 0){
    // For example, compare the content of array 'output' with what is
    // produced by the sequential function single_layer_convolution
    // ...
  }

  MPI_Finalize();
  return 0;
}
