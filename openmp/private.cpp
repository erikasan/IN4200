#include <omp.h>
#include <cstdio>

using std::printf;

int main(int argc, char const *argv[])
{
    int num_threads, thread_id;

    #pragma omp parallel private(num_threads, thread_id)
    {
        thread_id = omp_get_thread_num();
        printf("Hello world from thread #%d \n", thread_id);

        if (thread_id == 0){
            num_threads = omp_get_num_threads();
            printf("Total number of threads is %d \n", num_threads);
        }
    }
    return 0;
}
