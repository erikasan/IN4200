#include <iostream>
#include <cstdlib>

using namespace std;

void print_matrix(int **A, int m, int n);

int main(int argc, char const *argv[])
{
    int m = 5;
    int n = 2;
    
    int **A;
    A = (int **) malloc(m*sizeof(int *));
    for (size_t i = 0; i < m; i++)
    {
        A[i] = (int *) malloc(n*sizeof(int));
    }
    

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            A[i][j] = n*i + j;
        }
    }
    
    print_matrix(A, m, n);
    

    return 0;
}

void print_matrix(int **A, int m, int n){

    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << "\n";
    }
    

    return;
}
