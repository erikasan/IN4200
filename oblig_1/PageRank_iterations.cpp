void PageRank_iterations(int N, 
                         int *row_ptr, 
                         int *col_idx, 
                         double *val, 
                         double d, 
                         double epsilon, 
                         double *scores){

    // for (int i = 0; i < N+1; i++){
    //     cout << row_ptr[i] << ' ';
    // }
    // cout << '\n';

    // for (int i = 0; i < row_ptr[N]; i++){
    //     cout << col_idx[i] << ' ';
    // }
    // cout << "\n";

    // for (int i = 0; i < row_ptr[N]; i++){
    //     cout << val[i] << ' ';
    // }
    // cout << "\n";

    int i, j, 
        start, stop;

    double x[N];

    for (i = 0; i < N; i++){
        x[i] = 1;
    }

    // Is this needed?
    for (i = 0; i < N; i++){
        scores[i] = 0;
    }

    //CRS matrix-vector product
    for (i = 0; i < N; i++){
        start = row_ptr[i];
        stop  = row_ptr[i+1];
        for (j = start; j < stop; j++){
            scores[i] += val[j]*x[col_idx[j]];
        }
    }


    // Temporary print thingy to check that the matrix-vector product works
    for (i = 0; i < N; i++){
        cout << scores[i] << " ";
    }
    cout << '\n';

    return;
}