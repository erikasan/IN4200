#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int rank, size;

    int m = 3, n = 3;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){

        float **A;

        A = (float **) malloc(m*sizeof(float *));
        for (int i = 0; i < m; i++){
            A[i] = (float *) malloc(n*sizeof(float));
        }

        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                A[i][j] = i + j;
            }
        }

        MPI_Send(A[0], m*n, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
    }

    if (rank == 1){

        float **B; 

        B = (float **) malloc(m*sizeof(float *));
        for (int i = 0; i < m; i++){
            B[i] = (float *) malloc(n*sizeof(float));
        }

        MPI_Status status;
        MPI_Recv(B[0], m*n, MPI_FLOAT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                printf("%f ", B[i][j]);
            }
            printf("\n");
        }
    }
    


    MPI_Finalize();
    return 0;
}
