
void MPI_double_layer_convolution(int M, int N, float **input,
                                  int K1, float **kernel1,
                                  int K2, float **kernel2,
                                  float **output)
{

  size_t i, j, ii, jj;
  double temp;

  // Intermediate matrix. The result of a single-layer convolution.
  float **im;

  int output_rows = M - K1 - K2 + 2;
  int output_cols = N - K1 - K2 + 2;

  int im_rows = M - K1 + 1;
  int im_cols = N - K1 + 1;

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Define the division of work among the processes.
  int projections = output_rows/size;
  int remainder   = output_rows%size;

  // Prepare arrays for MPI_Scatterv and MPI_Gatherv
  int n_rows[size],
      Scounts[size],
      Gcounts[size],
      Sdispls[size],
      Gdispls[size];

  Sdispls[0] = 0;
  Gdispls[0] = 0;

  for (i = 0; i < size-1; i++){
    n_rows[i]    = projections + K1 + K2 - 2; // The number of rows of the input matrix that each process 'sees'
    Scounts[i]   = n_rows[i]*N;
    Gcounts[i]   = projections*output_cols;
    Sdispls[i+1] = projections*(i+1)*N;
    Gdispls[i+1] = Gdispls[i] + Gcounts[i];

  }

  n_rows[size-1]  = projections + remainder + K1 + K2 - 2;
  Scounts[size-1] = n_rows[size-1]*N;
  Gcounts[size-1] = (projections + remainder)*output_cols;

  output_rows = n_rows[rank] - K1 - K2 + 2;
  im_rows     = n_rows[rank] - K1 + 1;

  if (rank > 0){
    // Allocate input
    input    = new float*[n_rows[rank]];
    input[0] = new float[n_rows[rank]*N];
    for (i = 0; i < n_rows[rank]; i++){
      input[i] = &input[0][i*N];
    }

    // Allocate output
    output    = new float*[output_rows];
    output[0] = new float[Gcounts[rank]];
    for (i = 1; i < output_rows; i++){
      output[i] = &output[0][i*output_cols];
    }
  }

  // Allocate intermediate matrix
  im    = new float*[im_rows];
  im[0] = new float[im_rows*im_cols];
  for (i = 1; i < im_rows; i++){
    im[i] = &im[0][i*im_cols];
  }

  // Send each process their piece of input
  MPI_Scatterv(input[0], Scounts, Sdispls, MPI_FLOAT,
               input[0], Scounts[rank], MPI_FLOAT,
               0, MPI_COMM_WORLD);

  // Perform the first convolution
  for (i = 0; i < im_rows; i++){
  for (j = 0; j < im_cols; j++){

    temp = 0;

    for (ii = 0; ii < K1; ii++){
    for (jj = 0; jj < K1; jj++){

      temp += input[i+ii][j+jj]*kernel1[ii][jj];

    }}

    im[i][j] = temp;

  }}

  // Perform the second convolution
  for (i = 0; i < output_rows; i++){
  for (j = 0; j < output_cols; j++){

    temp = 0;

    for (ii = 0; ii < K2; ii++){
    for (jj = 0; jj < K2; jj++){

      temp += im[i+ii][j+jj]*kernel2[ii][jj];

    }}

    output[i][j] = temp;

  }}

  // MPI_Gatherv
  MPI_Gatherv(output[0], Gcounts[rank], MPI_FLOAT,
              output[0], Gcounts, Gdispls, MPI_FLOAT,
              0, MPI_COMM_WORLD);

  if (rank > 0){
    output = NULL;
  }

  return;
}
