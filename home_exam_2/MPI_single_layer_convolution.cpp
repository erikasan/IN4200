
void MPI_single_layer_convolution(int M, int N, float **input,
                                  int K, float **kernel,
                                  float **output)
{

  // Calculate how many rows of input each process receives

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int rows = M/size;
  int remainder = M%size;

  // MPI_Scatterv

  // MPI_Gatherv
  return;
}
