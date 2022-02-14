#include <omp.h>
#include <cstdio>

using std::printf;

int main(int argc, char const *argv[])
{
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    printf("Hello world from thread #%d! \n", id);
  }
  return 0;
}
