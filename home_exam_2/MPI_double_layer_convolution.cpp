
void MPI_double_layer_convolution(int M, int N, float **input
                                  int K1, float **kernel1,
                                  int K2, float **kernel2,
                                  int **output)
{

  size_t i;

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
    //Sdispls[i+1] = *(i+1)*N;
    Gdispls[i+1] = Gdispls[i] + Gcounts[i];

  }
  n_rows[size-1]  = projections + remainder + K - 1;
  Scounts[size-1] = n_rows[size-1]*N;
  Gcounts[size-1] = (projections + remainder)*(N - K1 - K2 + 2);
  return;
}
