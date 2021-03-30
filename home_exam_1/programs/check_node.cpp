#include <iostream>
#include <cstdlib>
#include "../header_files/read_graph_from_file2.h"
#include "../header_files/create_SNN_graph2.h"
#include "../header_files/check_node.h"

using namespace std;


int main(int argc, char *argv[]){
  int node_id, tau, N, *row_ptr, *col_idx, *SNN_val;

  char *filename = argv[1];
  node_id        = atoi(argv[2]);
  tau            = atoi(argv[3]);

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);

  check_node(node_id, tau, N, row_ptr, col_idx, SNN_val);
  return 0;
}
