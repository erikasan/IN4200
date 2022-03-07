#include <omp.h>
#include <cstdio>
#include <cmath>

double foo(int i);

int main(int argc, char const *argv[])
{
    int i;
    int n = 200000;
    double dotp;

    double a[n], b[n];

    for (i = 0; i < n; i++){
        a[i] = sin(i);
        b[i] = sin(2*i);
    }

    int chunk = 10000;
    dotp = 0;
    double start = omp_get_wtime();

    

    #pragma omp parallel for schedule(auto) reduction(+: dotp)
    for (i = 0; i < n; i++){
        dotp += a[i]*b[i];
    }

    double stop = omp_get_wtime() - start;

    printf("%f \n", stop);

    return 0;
}

double foo(int i){
    return sin(i);
}