
void MPI_single_layer_convolution(int M, int N, float **input,
                                  int K, float **kernel,
                                  float **output)
{

  size_t proc;
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Calculate how many rows of input each process receives
  int rows = (M - K + 1)/size + K - 1;
  //int remainder = (M%size)*K;

  int n_rows[size],
      sendcounts[size],
      Sdispls[size],
      Gdispls[size];

  Sdispls[0] = 0;
  Gdispls[0] = 0;

  for (proc = 0; proc < size-1; proc++){
    n_rows[proc]     = rows;
    sendcounts[proc] = n_rows[proc]*N;
    Sdispls[i+1]     = Sdispls[i] + sendcounts[i];
    // Gdispls[i+1] =
  }
  n_rows[size-1]     = rows + remainder;
  sendcounts[size-1] = n_rows[size-1]*N;

  // MPI_Scatterv

  // MPI_Gatherv
  return;
}
