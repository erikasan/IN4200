#include <iostream> // Remove 
#include <cstdio>
#include <cstdlib>

#include "read_graph_from_file.cpp"
#include "PageRank_iterations.cpp"
#include "top_n_webpages.cpp"

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

    // top_n_webpages(N, 
    //                scores, 
    //                n);

    for (int i = 0; i < N+1; i++){
        cout << row_ptr[i] << ' ';
    }
    cout << '\n';

    for (int i = 0; i < row_ptr[N]; i++){
        cout << col_idx[i] << ' ';
    }
    cout << "\n";

    for (int i = 0; i < row_ptr[N]; i++){
        cout << val[i] << ' ';
    }
    cout << "\n";

    cout << "No runtime errors \n";
    return 0;
}