#include <fstream>

using namespace std;

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

void get_dangling_indices(int *num_dangling_indices, 
                          int **dangling_indices){

    ifstream infile;

    infile.open("num_dangling_webpages.txt");
    infile >> *num_dangling_indices;
    infile.close();

    *dangling_indices = new int[*num_dangling_indices];

    infile.open("dangling_webpages.txt");
    for (int i = 0; i < *num_dangling_indices; i++){
        infile >> (*dangling_indices)[i];
    }
    infile.close();


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

    int num_dangling_indices;
    int *dangling_indices;

    get_dangling_indices(&num_dangling_indices, 
                         &dangling_indices);

    
    // for (int i = 0; i < N; i++){
    //     x[i] = 1./N;
    // }

    // for (int i = 0; i < 20; i++){
    //     CRS_matrix_vector_multiplication(N, 
    //                                      row_ptr, 
    //                                      col_idx, 
    //                                      val, 
    //                                      x);
    // }

    return;
}