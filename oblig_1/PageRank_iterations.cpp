#include <fstream>
#include <cmath>

using namespace std;

void CRS_matrix_vector_multiplication(int N, 
                                      int *row_ptr, 
                                      int *col_idx, 
                                      double *val, 
                                      double *x,
                                      bool check_convergence,
                                      bool *converged,
                                      double epsilon){
    
    int i, j, 
        start, stop;

    // Temporarily store the result of the multiplication
    double temp[N]{};

    for (i = 0; i < N; i++){
        start = row_ptr[i];
        stop  = row_ptr[i+1];
        for (j = start; j < stop; j++){
            temp[i] += val[j]*x[col_idx[j]];
        }
    }

    if (check_convergence){
        double distance = 0;
        for (i = 0; i < N; i++){
            distance += abs(x[i] - temp[i]); // Taxicab norm
        }
        if (distance < epsilon){
            *converged = 1;
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

double sum_dangling_PageRank_scores(int num_dangling_indices, 
                                    int *dangling_indices, 
                                    double *x){
    
    double W = 0;
    int index;

    for (int i = 0; i < num_dangling_indices; i++){
        index = dangling_indices[i];
        W += x[index];
    }

    return W;
}

void PageRank_iterations(int N, 
                         int *row_ptr, 
                         int *col_idx, 
                         double *val, 
                         double d, 
                         double epsilon, 
                         double *scores){


    //double x[N];
    double W = 0;
    double one_div_N = 1./N;
    double d_div_N = d*one_div_N;
    double one_minus_d_div_N = (1 - d)*one_div_N;

    int num_dangling_indices;
    int *dangling_indices;

    int k = 1;
    int max_iterations = 100000;

    // The program will check for convergence when k is a multiple of batch_size
    int batch_size = 25;

    bool converged = 0;

    for (int i = 0; i < N; i++){
        scores[i] = one_div_N;
    }

    get_dangling_indices(&num_dangling_indices, 
                         &dangling_indices);

    // Main loop

    if (num_dangling_indices == 0){

        while (k <= max_iterations ^ converged){ // ^ = XOR operator
            CRS_matrix_vector_multiplication(N, 
                                            row_ptr, 
                                            col_idx, 
                                            val, 
                                            scores,
                                            !(k%batch_size),
                                            &converged,
                                            epsilon);

            for (int i = 0; i < N; i++){
                scores[i] *= d;
                scores[i] += one_minus_d_div_N;
            }

            k++;
        }
    }
    
    else if (num_dangling_indices > 0){
        while (k <= max_iterations ^ converged){

            W = sum_dangling_PageRank_scores(num_dangling_indices, 
                                             dangling_indices, 
                                             scores);

            CRS_matrix_vector_multiplication(N, 
                                            row_ptr, 
                                            col_idx, 
                                            val, 
                                            scores,
                                            !(k%batch_size),
                                            &converged,
                                            epsilon);

            for (int i = 0; i < N; i++){
                scores[i] *= d;
                scores[i] += one_minus_d_div_N + d_div_N*W;
            }

            k++;
        }
    }
    
    delete[] row_ptr;
    delete[] col_idx;
    delete[] val;
    delete[] dangling_indices;

    return;
}