
void MPI_single_layer_convolution(int M, int N, float **input,
                                  int K, float **kernel,
                                  float **output)
{

  size_t i, j, ii, jj;
  double temp;

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Calculate how many rows of input each process receives
  int rows = ((M - K + 1)/size)*K;
  int remainder = (M%size)*K;

  int n_rows[size],
      Scounts[size],
      Gcounts[size],
      Sdispls[size],
      Gdispls[size];

  Sdispls[0] = 0;
  Gdispls[0] = 0;

  for (i = 0; i < size-1; i++){
    n_rows[i]    = rows;
    Scounts[i]   = n_rows[i]*N;
    Sdispls[i+1] = Sdispls[i] + Scounts[i];
  }

  n_rows[size-1]  = rows + remainder;
  Scounts[size-1] = n_rows[size-1]*N;

  // Send each process their piece of input
  MPI_Scatterv(input[0], Scounts, Sdispls, MPI_FLOAT,
               input[0], Scounts[rank], MPI_FLOAT,
               0, MPI_COMM_WORLD);

  if (rank > 0){
    // Allocate output
    output = new float*[(M - K + 1)/size];
    output[0] = new float[((M - K + 1)/size)*(N - K + 1)];
    for (i = 1; i < M - K + 1; i++){
      output[i] = &output[0][i*(N - K + 1)];
    }
  }

  // Perform the convolution
  for (i = 0; i <= n_rows[rank] - K; i++){
  for (j = 0; j <= N - K; j++){

    temp = 0;

    for (ii = 0; ii < K; ii++){
    for (jj = 0; jj < K; jj++){

      temp += input[i+ii][j+jj]*kernel[ii][jj];

    }}

    output[i][j] = temp;

  }}


  // MPI_Gatherv
  return;
}
