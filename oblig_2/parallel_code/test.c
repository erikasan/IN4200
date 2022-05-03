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

        A = malloc(m * sizeof *A);
        A[0] = malloc(m*n * sizeof *A[0]); 
        for (int i = 1; i < m; i++){
            A[i] = &(A[0][i*n]);
        }

        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                A[i][j] = i + j;
            }
        }

        MPI_Send(A[0], m*n, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);

        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                printf("%f ", A[i][j]);
            }
            printf("\n");
        }
    }

    if (rank == 1){

        float **B; 

        B = malloc(m * sizeof *B);
        B[0] = malloc(m*n * sizeof *B[0]); 
        for (int i = 1; i < m; i++){
            B[i] = &(B[0][i*n]);
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
