#include <mpi.h>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);

  int rank, i, p, root = 0;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  // Make the local vector size constant
  int local_vector_size = 100;

  // compute the global vector size
  int n = p*local_vector_size;

  // initialize the vectors
  double *a, *b;
  a = new double[local_vector_size];
  b = new double[local_vector_size];

  for (i = 0; i < local_vector_size; i++){
    a[i] = 3.14*rank;
    b[i] = 6.67*rank;
  }

  // compute the local dot product
  double partial_sum = 0.0;
  for (i = 0; i < local_vector_size; i++){
    partial_sum += a[i]*b[i];
  }

  double sum = 0;
  MPI_Reduce(&partial_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);

  if (rank == root){
    printf("The dot product is %g \n", sum);
  }

  free(a);
  free(b);

  MPI_Finalize();
  return 0;
}
