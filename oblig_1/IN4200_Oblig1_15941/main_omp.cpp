#include <iostream> // Remove 
#include <cstdio>
#include <cstdlib>

#include <omp.h>

#include "read_graph_from_file.cpp"
#include "PageRank_iterations_omp.cpp"
#include "top_n_webpages_omp.cpp"

using namespace std; // Remove

int main(int argc, char *argv[])
{
    char *filename;
    double d, epsilon;
    int n;

    int N;
    int *row_ptr, *col_idx;
    double *val; 

    filename = argv[1];
    d        = atof(argv[2]);
    epsilon  = atof(argv[3]);
    n        = atoi(argv[4]);

    read_graph_from_file(filename, 
                         &N, 
                         &row_ptr, 
                         &col_idx, 
                         &val);

    double scores[N];

    PageRank_iterations(N, 
                        row_ptr, 
                        col_idx, 
                        val, 
                        d, 
                        epsilon, 
                        scores);

    top_n_webpages(N, 
                   scores, 
                   n);

    return 0;
}