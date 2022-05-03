#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>

void allocate_array2d(double ***x, int m, int n);

void copy_u_to_u_bar(double **u, double **u_bar, int m, int n);

void print_array2d(double **x, int m, int n);

int main(int argc, char *argv[])
{
    int rank, size;

    int m = 2, n = 2;
    int M = 4, N = 2;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double **u, **u_bar;
    allocate_array2d(&u, m, n);
    allocate_array2d(&u_bar, m, n);

    double **whole_array;
    allocate_array2d(&whole_array, M, N);

    int *counts_send = malloc(size * sizeof *counts_send);
    counts_send[0] = m*n;
    counts_send[1] = m*n;

    int *displacements = malloc(size * sizeof *displacements);
    displacements[0] = 0;
    displacements[1] = m*n;

    if (rank == 0){
        for (int i = 0; i < M; i++){
            for (int j = 0; j < N; j++){
                whole_array[i][j] = i + j;
            }
        }
    }

    MPI_Scatterv(whole_array[0],
                 counts_send,
                 displacements,
                 MPI_DOUBLE,
                 u[0],
                 m*n,
                 MPI_DOUBLE,
                 0,
                 MPI_COMM_WORLD);

    copy_u_to_u_bar(u, u_bar, m, n);

    MPI_Gatherv(u[0],
                m*n,
                MPI_DOUBLE,
                whole_array[0],
                counts_send,
                displacements,
                MPI_DOUBLE,
                0,
                MPI_COMM_WORLD);

    if (rank == 0){
        print_array2d(whole_array, M, N);
    }

    MPI_Finalize();
    return 0;
}

void allocate_array2d(double ***x, int m, int n){
    (*x) = malloc(m * sizeof *(*x));
    (*x)[0] = malloc(m*n * sizeof *(*x)[0]);
    for (int i = 1; i < m; i++){
        (*x)[i] = &((*x)[0][i*n]);
    }
    return;
}


void copy_u_to_u_bar(double **u, double **u_bar, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            u_bar[i][j] = u[i][j];
        }
    }
    return;
}

void print_array2d(double **x, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("%f ", x[i][j]);
        }
        printf("\n");
    }
    return;
}