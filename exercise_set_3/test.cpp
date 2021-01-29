#include <iostream>
#include <ctime>

using namespace std;

int main(){

  double x;
  double iterations = 1e4;
  clock_t start_time, total_time;

  start_time = clock();
  for (int i = 0; i < iterations; i++){
    x = 1.49348/2.273774;
  }

  total_time = (clock() - start_time);

  double elapsed_time = total_time/(CLOCKS_PER_SEC*iterations);
  double CPU_speed = 2.1e9;

  double clock_cycles = CPU_speed*elapsed_time;


  cout << clock_cycles << endl;
  cout << elapsed_time << endl;
  return 0;
}
