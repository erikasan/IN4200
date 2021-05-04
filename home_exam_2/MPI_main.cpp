#include <mpi.h>
#include <cstdlib>
#include "MPI_single_layer_convolution.cpp"
#include "MPI_double_layer_convolution.cpp"
#include "example_programs/single_layer_convolution.cpp"

#include <iostream>

using namespace std;

int main(int nargs, char **args)
{
  int M, N, K1, K2, rank;

  float **input = NULL, **output = NULL, **kernel1 = NULL, **kernel2 = NULL;

  size_t i, j;

  MPI_Init(&nargs, &args);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0){
    // read from command line the values of M, N, and K
    M  = atoi(args[1]);
    N  = atoi(args[2]);
    K1 = atoi(args[3]);
    K2 = atoi(args[4]);

    // allocate 2D array 'input' with M rows and N columns
    input    = new float*[M];
    input[0] = new float[M*N];
    for (i = 1; i < M; i++){
      input[i] = &input[0][i*N];
    }

    // allocate 2D array 'output' with M - K + 1 rows and N - K + 1 columns
    output    = new float*[M - K1 - K2 + 2];
    output[0] = new float[(M - K1 - K2 + 2)*(N - K1 - K2 + 2)];
    for (i = 1; i < M - K1 - K2 + 2; i++){
      output[i] = &output[0][i*(N - K1 - K2 + 2)];
    }

    // allocate the first convolutional kernel with K1 rows and K1 columns
    kernel1    = new float*[K1];
    kernel1[0] = new float[K1*K1];
    for (i = 1; i < K1; i++){
      kernel1[i] = &kernel1[0][i*K1];
    }

    // allocate the second convolutional kernel with K2 rows and K2 columns
    kernel2    = new float*[K2];
    kernel2[0] = new float[K2*K2];
    for (i = 1; i < K2; i++){
      kernel2[i] = &kernel2[0][i*K2];
    }

    // fill 2D array 'input' with some values
    for (i = 0; i < M; i++){
    for (j = 0; j < N; j++){
      input[i][j] = 1;
    }}

    // fill kernel1 with some values
    for (i = 0; i < K1; i++){
    for (j = 0; j < K1; j++){
      kernel1[i][j] = 1;
    }}

    // fill kernel2 with some values
    for (i = 0; i < K2; i++){
    for (j = 0; j < K2; j++){
      kernel2[i][j] = 1./3;
    }}
  }

  // process 0 broadcasts values of M, N, K1, K2 to all other processes
  MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&K1, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&K2, 1, MPI_INT, 0, MPI_COMM_WORLD);

  if (rank > 0){
    // allocate the first convolutional kernel with K1 rows and K1 columns
    kernel1    = new float*[K1];
    kernel1[0] = new float[K1*K1];
    for (i = 1; i < K1; i++){
      kernel1[i] = &kernel1[0][i*K1];
    }

    // allocate the second convolutional kernel with K2 rows and K2 columns
    kernel2    = new float*[K2];
    kernel2[0] = new float[K2*K2];
    for (i = 1; i < K2; i++){
      kernel2[i] = &kernel2[0][i*K2];
    }
  }

  // process 0 broadcasts the content of the kernels to all other processes
  MPI_Bcast(kernel1[0], K1*K1, MPI_FLOAT, 0, MPI_COMM_WORLD);
  MPI_Bcast(kernel2[0], K2*K2, MPI_FLOAT, 0, MPI_COMM_WORLD);

  // parallel computation of a single-layer convolution
  // MPI_single_layer_convolution(M, N, input,
  //                              K, kernel,
  //                              output);

  // parallel computation of a double-layer convolution
  MPI_double_layer_convolution(M, N, input,
                               K1, kernel1,
                               K2, kernel2,
                               output);

  if (rank == 0){
    // For example, compare the content of array 'output' with what is
    // produced by the sequential function single_layer_convolution
    // ...

    for (i = 0; i < M - K1 - K2 + 2; i++){
      for (j = 0; j < N - K1 - K2 + 2; j++){
        cout << output[i][j] << " ";
      }
      cout << endl;
    }

  }

  MPI_Finalize();
  return 0;
}
