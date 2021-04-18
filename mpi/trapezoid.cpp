#include <mpi.h>
#include <cstdio>

using namespace std;

int main(int argc, char **argv)
{
  int rank, size;
  double a = 0, b = 1, mya, myb, psum;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  mya = a + rank*(b - a)/size;
  myb = mya + (b - a)/size;
  psum = integrate(mya, myb);

  if (rank == 0){
    double res = psum;
    for (int i = 1; i < size; i++){
      MPI_Recv(&psum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
      res += psum;
    }
    printf("Result: %g\n", res);
  }

  else{
    MPI_Send(&psum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  }
  return 0;
}
