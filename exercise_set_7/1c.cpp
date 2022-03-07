#include <omp.h>
#include <cstdio>
#include <cmath>

using namespace std;

double foo(int i);

int main(int argc, char const *argv[])
{
    int i;
    int n = 1000000;
    double a[n];

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < n; i++){
        a[i] = foo(i);
    }

    double stop = omp_get_wtime() - start;

    printf("%f \n", stop);

    return 0;
}

double foo(int i){
    return sin(i);
}