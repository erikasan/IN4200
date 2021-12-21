#include <iostream>
#include <string>
#include "../header_files/read_graph_from_file1.h"
#include "../header_files/create_SNN_graph1.h"

using namespace std;

int main(){
  char *filename = "simple-graph.txt";
  int N;
  char **table2D;
  int **SNN_table;

  read_graph_from_file1(filename, &N, &table2D);

  create_SNN_graph1(N, table2D, &SNN_table);

  string desired_output;
  desired_output = "0 2 2 2 0\n";
  desired_output+= "2 0 2 2 0\n";
  desired_output+= "2 2 0 3 1\n";
  desired_output+= "2 2 3 0 1\n";
  desired_output+= "0 0 1 1 0\n";

  cout << "Desired output:" << endl;
  cout << desired_output << endl;

  cout << "Calculated:" << endl;

  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      cout << SNN_table[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
