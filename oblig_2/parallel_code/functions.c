
void allocate_image(image *u, int m, int n){
    // (*u).image_data = (float **) malloc(m*sizeof(float *));
    // for (int i = 0; i < m; i++)
    // {
    //     (*u).image_data[i] = (float *) malloc(n*sizeof(float));
    // }

    (*u).image_data = malloc(m * sizeof *((*u).image_data));
    (*u).image_data[0] = malloc(m*n * sizeof *((*u).image_data[0]));
    for (int i = 1; i < m; i++){
        (*u).image_data[i] = &((*u).image_data[0][i*n]);
    }

    (*u).m = m;
    (*u).n = n;
    
    return;
}

void deallocate_image(image *u){
    int m = (*u).m;

    for (int i = 0; i < m; i++){
        free((*u).image_data[i]);
    }

    free((*u).image_data);
    
    return;
}

void convert_jpeg_to_image(const unsigned char* image_chars, image*u){
    int i, j;
    int m, n;

    m = (*u).m;
    n = (*u).n;

    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            (*u).image_data[i][j] = image_chars[i*n + j];
        }
    }

    return;
}

void convert_image_to_jpeg(const image *u, unsigned char* image_chars){

    
    int i, j;
    int m, n;

    m = (*u).m;
    n = (*u).n;

    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            image_chars[i*n + j] = (*u).image_data[i][j];
        }
    }

    return;
}

void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters){
    int i, j;
    int m, n;

    m = (*u).m;
    n = (*u).n;

    int iter;
    float temp;

    float *top_row = malloc(n * sizeof *top_row);
    float *bottom_row = malloc(n * sizeof *bottom_row);

    int iters_min_1 = iters - 1;
    int m_min_1     = m - 1;
    int n_min_1     = n - 1;

    int my_rank, num_procs;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    MPI_Status status;

    // Copy boundary pixels
    if (my_rank == 0){
        for (i = 1; i < m; i++){
            (*u_bar).image_data[i][0]   = (*u).image_data[i][0];
            (*u_bar).image_data[i][n_min_1] = (*u).image_data[i][n_min_1];
        }

        for (j = 0; j < n; j++){
            (*u_bar).image_data[0][j] = (*u).image_data[0][j];
        }
        
    }
    else if (my_rank == num_procs - 1){
        for (i = 0; i < m_min_1; i++){
            (*u_bar).image_data[i][0]   = (*u).image_data[i][0];
            (*u_bar).image_data[i][n_min_1] = (*u).image_data[i][n_min_1];
        }

        for (j = 0; j < n; j++){
            (*u_bar).image_data[m_min_1][j] = (*u).image_data[m_min_1][j];
        }
    }
    else {
        for (i = 0; i < m; i++){
            (*u_bar).image_data[i][0]   = (*u).image_data[i][0];
            (*u_bar).image_data[i][n_min_1] = (*u).image_data[i][n_min_1];
        }
    }

    // // Main algorithm
    // for (iter = 0; iter < iters; iter++){

    //     MPI_Barrier(MPI_COMM_WORLD);

    //     if (my_rank == 0){
    //         // Process 0 sends its last row to process 1
    //         MPI_Send((*u).image_data[m_min_1], n, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD);
    //         // Process 0 receives the first row of process 1
    //         MPI_Recv(bottom_row, n, MPI_FLOAT, my_rank+1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    //     }
    //     else if (my_rank == num_procs - 1){
    //         // Last process sends its first row to the previous process
    //         MPI_Send((*u).image_data[0], n, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD);
    //         // Last process receives the last row of the previous process
    //         MPI_Recv(top_row, n, MPI_FLOAT, my_rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    //     }
    //     else {
    //         // Process i sends its first row to process i-1
    //         MPI_Send((*u).image_data[0], n, MPI_FLOAT, my_rank-1, 0, MPI_COMM_WORLD);
    //         // Process i sends its last row to process i+1
    //         MPI_Send((*u).image_data[m_min_1], n, MPI_FLOAT, my_rank+1, 0, MPI_COMM_WORLD);
    //         // Process i receives the last row of process i-1
    //         MPI_Recv(top_row, n, MPI_FLOAT, my_rank-1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    //         // Process i receives the first row of process i+1
    //         MPI_Recv(bottom_row, n, MPI_FLOAT, my_rank+1, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    //     }

    //     // Process i updates its last row if it needs the first row of process i+1
    //     if (my_rank < num_procs - 1){
    //         for (j = 1; j < n_min_1; j++){
    //             temp = (*u).image_data[m-2][j] + (*u).image_data[m-1][j-1] - 4*(*u).image_data[m-1][j] + (*u).image_data[m-1][j+1] + bottom_row[j];
    //             (*u_bar).image_data[m-1][j] = (*u).image_data[m-1][j] + kappa*temp;
    //         }
    //     }

    //     // Process i updates its first row if it needs the last row of process i-1
    //     if (my_rank > 0){
    //         for (j = 1; j < n_min_1; j++){
    //             temp = top_row[j] + (*u).image_data[0][j-1] - 4*(*u).image_data[0][j] + (*u).image_data[0][j+1] + (*u).image_data[1][j];
    //             (*u_bar).image_data[0][j] = (*u).image_data[0][j] + kappa*temp;
    //         }
    //     }

    //     for (i = 1; i < m_min_1; i++){
    //     for (j = 1; j < n_min_1; j++){
    //         temp = (*u).image_data[i-1][j] + (*u).image_data[i][j-1] - 4*(*u).image_data[i][j] + (*u).image_data[i][j+1] + (*u).image_data[i+1][j];
    //         (*u_bar).image_data[i][j] = (*u).image_data[i][j] + kappa*temp;
    //     }}

    //     // Copy u_bar into u if not last iteration
    //     if (iter < iters_min_1){
    //         for (i = 1; i < m_min_1; i++){
    //         for (j = 1; j < n_min_1; j++){
    //             (*u).image_data[i][j] = (*u_bar).image_data[i][j];
    //         }}

    //         // Everyone except process 0 must copy its first row from u_bar to u
    //         if (my_rank > 0){
    //             for (j = 1; j < n_min_1; j++){
    //                 (*u).image_data[0][j] = (*u_bar).image_data[0][j];
    //             }
                
    //         }

    //         // Everyone except the last process must copy its last row from u_bar to u
    //         if (my_rank < num_procs - 1){
    //             for (j = 1; j < n_min_1; j++){
    //                 (*u).image_data[m-1][j] = (*u_bar).image_data[m-1][j];
    //             }
    //         }
    //     }
    // }
    return;
}