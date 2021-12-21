#include <iostream>
#include <string>
#include "../header_files/read_graph_from_file1.h"

using namespace std;

int main(){
  char *filename = "simple-graph.txt";
  int N;
  char **table2D;
  
  read_graph_from_file1(filename, &N, &table2D);

  string desired_output;

  desired_output = "0 1 1 1 0\n";
  desired_output+= "1 0 1 1 0\n";
  desired_output+= "1 1 0 1 1\n";
  desired_output+= "1 1 1 0 1\n";
  desired_output+= "0 0 1 1 0\n";

  cout << "Desired output:" << endl;
  cout << desired_output << endl << endl;

  cout << "Calculated:" << endl;
  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      printf("%d ", table2D[i][j]);
    }
    cout << endl;
  }




  return 0;
}
