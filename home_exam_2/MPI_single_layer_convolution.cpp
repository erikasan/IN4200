#include <iostream>

using namespace std;

void MPI_single_layer_convolution(int M, int N, float **input,
                                  int K, float **kernel,
                                  float **output)
{

  size_t i, j, ii, jj;
  double temp;

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // The row-wise projections of the kernel onto
  // input is divided among the processes

  // A process gets at least this many projections
  int projections = (M - K + 1)/size;

  // Calculate how many (unique) rows of input each process receives
  int rows      = projections + K - 1;
  int remainder = (M - K + 1)%size;

  // Prepare arrays for MPI_Scatterv and MPI_Gatherv
  int n_rows[size],
      Scounts[size],
      Gcounts[size],
      Sdispls[size],
      Gdispls[size];

  Sdispls[0] = 0;
  Gdispls[0] = 0;

  for (i = 0; i < size-1; i++){
    n_rows[size] = rows;
    Scounts[i]   = rows*N;
    Gcounts[i]   = projections*(N - K + 1);
    Sdispls[i+1] = Sdispls[i] + Scounts[i];
    Gdispls[i+1] = Gdispls[i] + Gcounts[i];
  }

  n_rows[size-1]  = rows + remainder;
  Scounts[size-1] = (rows + remainder)*N;
  Gcounts[size-1] = (projections + remainder)*(N - K + 1);


  if (rank > 0){
    // Allocate input and output
    input    = new float*[n_rows[rank]];
    input[0] = new float[n_rows[rank]*N];
    for (i = 0; i < n_rows[rank]; i++){
      input[i] = &input[0][i*N];
    }

    output    = new float*[n_rows[rank] - (K - 1)];
    output[0] = new float[Gcounts[rank]];
    for (i = 1; i < projections/size; i++){
      output[i] = &output[0][i*(N - K + 1)];
    }
  }

  //Send each process their piece of input
  MPI_Scatterv(input[0], Scounts, Sdispls, MPI_FLOAT,
               input[0], Scounts[rank], MPI_FLOAT,
               0, MPI_COMM_WORLD);


  // Test

  if (rank == 0){
    for (i = 0; i < size; i++){
      cout << n_rows[i] << endl;
    }
  }

  // for (int proc = 1; proc < size; proc++){
  //   if (rank == proc){
  //     cout << "Process " << rank << " has input" << endl;
  //     for (i = 0; i < n_rows[rank]; i++){
  //       for (j = 0; j < N; j++){
  //         cout << input[i][j] << " ";
  //       }
  //       cout << endl;
  //     }
  //     cout << endl;
  //   }
  // }

  // Perform the convolution
  // for (i = 0; i <= n_rows[rank] - K; i++){
  // for (j = 0; j <= N - K; j++){
  //
  //   temp = 0;
  //
  //   for (ii = 0; ii < K; ii++){
  //   for (jj = 0; jj < K; jj++){
  //
  //     temp += input[i+ii][j+jj]*kernel[ii][jj];
  //
  //   }}
  //
  //   output[i][j] = temp;
  //
  // }}

  // MPI_Gatherv
  // MPI_Gatherv(output[0], Gcounts[rank], MPI_FLOAT,
  //             output[0], Gcounts, Gdispls, MPI_FLOAT,
  //             0, MPI_COMM_WORLD);

  return;
}
