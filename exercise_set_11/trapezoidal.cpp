#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int nargs, char **args)
{
  int n = atoi(args[1]);
  double result = 0;
  double h = 1./n;
  double x;
  int i;
  int root = 0;

  int rank, size;
  MPI_Init(&nargs, &args);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int range[size+1];
  int interval = n/size;
  int remainder = n%size;

  range[0] = 0;
  for (i = 1; i < size-1; i++){
    range[i] = range[i-1] + interval;
  }
  range[size-1] = range[size-2] + remainder;
  range[size]   = n;

  for (i = range[rank]; i < range[rank+1]; i++){
    x = i*h;
    result += 0.5*(exp(5*x) + sin(x) - x*x);
  }

  double sum = 0;
  MPI_Reduce(&sum, &result, 1, MPI_DOUBLE, MPI_SUM, root, MPI_COMM_WORLD);

  if (rank == root){
    cout << h*sum << endl;
  }
  MPI_Finalize();

  return 0;
}
