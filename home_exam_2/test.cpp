#include <iostream>
#include <chrono>

using namespace std;

int main(int nargs, char **args)
{
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  return 0;
}
