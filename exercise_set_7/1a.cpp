#include <omp.h>
#include <cstdio>
#include <cmath>

using namespace std;

int main(int argc, char const *argv[])
{
    int i;
    double x = 3000000.;

    double a[(int) sqrt(x)], 
           b[10];

    double start = omp_get_wtime();
    
    #pragma omp parallel for
    for (i = 0; i < (int) sqrt(x); i++){
        a[i] = 2.3*x;
        if (i < 10){
            b[i] = a[i];
        }
    }

    double stop = omp_get_wtime() - start;

    printf("%f \n", stop);

    return 0;
}

