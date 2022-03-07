#include <omp.h>
#include <cstdio>
#include <cmath>

using namespace std;

double foo(int i);

int main(int argc, char const *argv[])
{
    int i;
    int n = 100000;

    double a[n], b[n];

    for (i = 0; i < n; i++){
        b[i] = foo(2*i);
    }


    double start = omp_get_wtime();

    #pragma omp parallel for
    for (i = 0; i < n; i++){
        a[i] = foo(i);
        if(a[i] < b[i]){
            a[i] = b[i];
        }
    }

    double stop = omp_get_wtime() - start;

    printf("%f \n", stop);

    return 0;
}

double foo(int i){
    return sin(i);
}