void CRS_matrix_vector_multiplication(int N, 
                                         int *row_ptr, 
                                         int *col_idx, 
                                         double *val, 
                                         double *x){
    
    int i, j, 
        start, stop;

    // Temporary store the result of the multiplication
    double temp[N]{};

    for (i = 0; i < N; i++){
        start = row_ptr[i];
        stop  = row_ptr[i+1];
        for (j = start; j < stop; j++){
            temp[i] += val[j]*x[col_idx[j]];
        }
    }

    // Copy the result into x
    for (i = 0; i < N; i++){
        x[i] = temp[i];
    }

    return;
}

double sum_dangling_PageRank_scores(){
    return 2;
}

void PageRank_iterations(int N, 
                         int *row_ptr, 
                         int *col_idx, 
                         double *val, 
                         double d, 
                         double epsilon, 
                         double *scores){


    double x[N];
    
    for (int i = 0; i < N; i++){
        x[i] = 1./N;
    }

    for (int i = 0; i < 20; i++){
        CRS_matrix_vector_multiplication(N, 
                                         row_ptr, 
                                         col_idx, 
                                         val, 
                                         x);
    }

    return;
}