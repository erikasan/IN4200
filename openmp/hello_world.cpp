#include <omp.h>
#include <iostream>

using std::cout;

int main(int argc, char const *argv[])
{
  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    cout << "Hello world from thead #" << id << "\n";
  }
  return 0;
}
