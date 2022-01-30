#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char const *argv[])
{
    int n_x, n_y, n_z;
    
    n_x = 2;
    n_y = 3;
    n_z = 4;


    // Allocation
    int ***A;
    A = (int ***) malloc(n_x*sizeof(int **));
    for (size_t i = 0; i < n_x; i++)
    {
        A[i] = (int **) malloc(n_y*sizeof(int *));
        for (size_t j = 0; j < n_y; j++)
        {
            A[i][j] = (int *) malloc(n_z*sizeof(int));
        }
        
    }

    // Assigning elements
    int l = 0;
    for (size_t i = 0; i < n_x; i++)
    {
        for (size_t j = 0; j < n_y; j++)
        {
            for (size_t k = 0; k < n_z; k++)
            {
                //A[i][j][k] = i*n_y*n_z + j*n_z + k;
                A[i][j][k] = l;
                l++;
            }
            
        }
        
    }

    // Assigning elements
    for (size_t i = 0; i < n_x; i++)
    {
        for (size_t j = 0; j < n_y; j++)
        {
            for (size_t k = 0; k < n_z; k++)
            {
                cout << A[i][j][k] << "\n";
            }
            
        }
        
    }
    
    // Freeing memory
    for (size_t i = 0; i < n_x; i++)
    {
        for (size_t j = 0; j < n_y; j++)
        {
            free(A[i][j]);
        }
        free(A[i]);
    }
    free(A);
    
    
    return 0;
}
