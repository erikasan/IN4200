#include <iostream>
#include <string>
#include "../header_files/read_graph_from_file2.h"
#include "../header_files/create_SNN_graph2.h"

using namespace std;

int main(){
  char *filename = "simple-graph.txt";
  int N;
  int *row_ptr, *col_idx;
  int *SNN_val;

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);

  string desired_output;
  desired_output = "SNN_val = [ 2 2 2 2 2 2 2 2 3 1 2 2 3 1 1 1 ]\n";

  cout << "Desired output:" << endl;
  cout << desired_output << endl;

  cout << "Calculated:" << endl;

  cout << "SNN_val = [ ";
  for (int i = 0; i < row_ptr[N]; i++){
    cout << SNN_val[i] << " ";
  }
  cout << " ]" << endl << endl;

  cout << "NOTE: read_graph_from_file2 does not have sorting implemented.";
  cout << " Some elements of SNN_val may be in a different order than the desired output";
  cout << " and still be a valid representation of the SNN graph.";
  cout << endl;

  return 0;
}
