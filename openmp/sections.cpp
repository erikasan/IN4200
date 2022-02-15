#include <omp.h>
#include <cstdio>

using std::printf;

int main(int argc, char const *argv[])
{
    const int N = 100;
    int x[N], i, sum, sum2;
    int upper, lower;

    sum = 0;
    sum2 = 0;

    #pragma omp parallel for
    for (i = 0; i < N; i++){
        x[i] = i;
    }

    #pragma omp parallel private(i) shared(x)
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                upper = x[0];
                lower = x[0];

                for (i = 0; i < N; i++){
                    if (x[i] > upper){
                        upper = x[i];
                    }
                    if (x[i] < lower){
                        lower = x[i];
                    }
                }

                printf("Max value = %d \n", upper);
                printf("Min value = %d \n", lower);
            }

            #pragma omp section
            {
                for (i = 0; i < N; i++){
                    sum += x[i];
                }

                printf("<x> = %.1f \n", (double) sum/N);
            }

            #pragma omp section
            {
                for (i = 0; i < N; i++){
                    sum2 += x[i]*x[i];
                }

                printf("<x^2> = %.1f \n", (double) sum2/N);
            }
        }
    }
    return 0;
}
