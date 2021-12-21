#include <iostream>
#include <string>
#include "../header_files/read_graph_from_file2.h"

using namespace std;

int main(){

  char *filename = "simple-graph.txt";
  int N;
  int *row_ptr, *col_idx;

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  string desired_output;

  desired_output = "row_ptr = [ 0 3 6 10 14 16 ]\n";
  desired_output+= "col_idx = [ 1 2 3 0 2 3 0 1 3 4 0 1 2 4 2 3 ]\n";

  cout << "Desired output:" << endl;
  cout << desired_output << endl;

  cout << "Calculated:" << endl;

  cout << "row_ptr = [ ";
  for (int i = 0; i < N+1; i++){
    cout << row_ptr[i] << " ";
  }
  cout << "]" << endl;

  cout << "col_idx = [ ";
  for (int i = 0; i < row_ptr[N]; i++){
    cout << col_idx[i] << " ";
  }
  cout << "]" << endl << endl;;

  cout << "NOTE: read_graph_from_file2 does not have sorting implemented.";
  cout << " Some elements of col_idx may be in a different order than the desired output";
  cout << " and still be a valid representation of the connectivity graph.";
  cout << endl;

  return 0;
}
