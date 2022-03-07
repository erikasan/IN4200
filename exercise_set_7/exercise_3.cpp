 #include <omp.h>
 #include <cstdio>
 #include <cstdlib>

using namespace std;

void dense_mat_vec(int m, int n, double *x, double *A, double *y);

 int main(int argc, char const *argv[])
 {
    int m, n;
    int i, j;

    m = atof(argv[1]);
    n = atof(argv[2]);

    double A[m*n], x[m], y[n];

    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            A[i*n + j] = i*j;
        }
    }

    for (j = 0; j < n; j++){
        y[j] = (double) j*j/2;
    }
    
    dense_mat_vec(m, n, x, A, y);

    // for (i = 0; i < m; i++){
    //     for (j = 0; j < n; j++){
    //         printf("%.1f ", A[i*n + j]);
    //     }
    //     printf("\n");
    // }

    // for (i = 0; i < m; i++){
    //     printf("%.1f \n", x[i]);
    // }

    // for (j = 0; j < n; j++){
    //     printf("%.1f \n", y[j]);
    // }

    return 0;
 }
 
 void dense_mat_vec(int m, int n, double *x, double *A, double *y){
     int i, j;
     double tmp;
     #pragma omp parallel for private(i, j, tmp, y) schedule(static, m)
     for (i = 0; i < m; i++){
         tmp = 0.;
         for (j = 0; j < n; j++){
             tmp += A[i*n + j]*y[j];
         }
         x[i] = tmp;
     }
     return;
 }