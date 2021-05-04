
void MPI_double_layer_convolution(int M, int N, float **input
                                  int K1, float **kernel1,
                                  int K2, float **kernel2,
                                  int **output)
{

  size_t i, j, ii, jj;
  double temp;

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int projections = (M - K1 - K2 + 2)/size;
  int remainder   = (M - K1 - K2 + 2)%size;

  int n_rows[size],
      Scounts[size],
      Gcounts[size],
      Sdispls[size],
      Gdispls[size];

  Sdispls[0] = 0;
  Gdispls[0] = 0;

  for (i = 0; i < size-1; i++){
    n_rows[i]    = projections + K1 + K2 - 2;
    Scounts[i]   = n_rows[i]*N;
    Gcounts[i]   = projections*(N - K1 - K2 + 2);
    Sdispls[i+1] = projections*(i+1)*N;
    Gdispls[i+1] = Gdispls[i] + Gcounts[i];

  }

  n_rows[size-1]  = projections + remainder + K - 1;
  Scounts[size-1] = n_rows[size-1]*N;
  Gcounts[size-1] = (projections + remainder)*(N - K1 - K2 + 2);

  if (rank > 0){
    // Allocate input
    input    = new float*[n_rows[rank]];
    input[0] = new float[n_rows[rank]*N];
    for (i = 0; i < n_rows[rank]; i++){
      input[i] = &input[0][i*N];
    }

    // Allocate output
    output    = new float*[n_rows[rank] - K1 - K2 + 2)];
    output[0] = new float[Gcounts[rank]];
    for (i = 1; i < n_rows[rank] - K1 - K2 + 2); i++){
      output[i] = &output[0][i*(N - K1 - K2 + 2)];
    }
  }

  // Allocate intermediate matrix
  im = new float*[n_rows[rank] - K1 + 1];
  im = new float[N - K1 + 1];
  for (i = 1; i < n_rows[rank] - K1 + 1; i++){
    im[i] = &im[0][i*(N - K1 + 1)];
  }

  // Send each process their piece of input
  MPI_Scatterv(input[0], Scounts, Sdispls, MPI_FLOAT,
               input[0], Scounts[rank], MPI_FLOAT,
               0, MPI_COMM_WORLD);

  // Perform the first convolution
  for (i = 0; i <= n_rows[rank] - K1; i++){
  for (j = 0; j <= N - K1; j++){

    temp = 0;

    for (ii = 0; ii < K1; ii++){
    for (jj = 0; jj < K1; jj++){

      temp += input[i+ii][j+jj]*kernel[ii][jj];

    }}

    im[i][j] = temp;

  }}

  // Perform the second convolution
  for (i = 0; i <= n_rows[rank] - K1 - K2 + 1; i++){
  for (j = 0; j <= N - K1 - K2 + 1; j++){

    temp = 0;

    for (ii = 0; ii < K2; ii++){
    for (jj = 0; jj < K2; jj++){

      temp += im[i+ii][j+jj]*kernel[ii][jj];

    }}

    output[i][j] = temp;

  }}

  // MPI_Gatherv
  MPI_Gatherv(output[0], Gcounts[rank], MPI_FLOAT,
              output[0], Gcounts, Gdispls, MPI_FLOAT,
              0, MPI_COMM_WORLD);
              
  return;
}
