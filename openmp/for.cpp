#include <omp.h>
#include <cstdio>

using std::printf;

int main(int argc, char const *argv[])
{
    const int N = 300000;
    int i, n;
    double a[N], b[N], result[N];
    double start, total;

    double iterations = 2000;

    // Initialize
    for (i = 0; i < N; i++){
        a[i] = 1.*i;
        b[i] = 2.*i;
    }

    start = omp_get_wtime();

    for (n = 0; n < iterations; n++){
        #pragma omp parallel
        {
            #pragma omp for
            for (i = 0; i < N; i++){
                result[i] = a[i] + b[i];
            }

        }
    }

    
    total = omp_get_wtime() - start;

    printf("Time = %f \n", total);
    
    return 0;
}
