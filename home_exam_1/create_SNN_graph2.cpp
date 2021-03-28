#include <iostream>
#include "read_graph_from_file2.cpp"

using namespace std;

void create_SNN_graph2(int N, int *row_ptr, int *col_idx, int **SNN_val);

int main(){
  char *filename = "simple-graph.txt";
  int N;
  int *row_ptr, *col_idx;

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  int *SNN_val;
  create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);

  return 0;
}

void create_SNN_graph2(int N, int *row_ptr, int *col_idx, int **SNN_val){

  // Allocate SNN_val and fill with zeros;
  (*SNN_val) = new int[N]{};

  return;
}
