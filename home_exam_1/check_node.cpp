#include <iostream>
#include "read_graph_from_file2.cpp"
#include "create_SNN_graph2.cpp"

using namespace std;

void check_node(int node_id, int tau, int N, int *row_ptr, int *col_idx, int *SNN_val);

int main(){
  int node_id, tau, N, *row_ptr, *col_idx, *SNN_val;

  node_id = 1;
  tau = 2;

  char *filename = "simple-graph.txt";

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);

  check_node(node_id, tau, N, row_ptr, col_idx, SNN_val);

  // for (int i = 0; i < row_ptr[N]; i++){
  //   cout << SNN_val[i] << " ";
  // }
  // cout << endl;

  return 0;
}


void check_node(int node_id, int tau, int N, int *row_ptr, int *col_idx, int *SNN_val){
  int i, start, end;
  start = row_ptr[node_id];
  end   = row_ptr[node_id+1];
  for (i = start; i < end; i++){
    if (SNN_val[i] >= tau){
      cout << col_idx[i] << endl;
    }
  }
  return;
}
