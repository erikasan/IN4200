#include <iostream>
#include <string>
#include "../header_files/read_graph_from_file2.h"
#include "../header_files/create_SNN_graph2.h"
#include "../header_files/check_node.h"

using namespace std;

int main(){
  int node_id, tau, N, *row_ptr, *col_idx, *SNN_val;

  char *filename = "simple-graph.txt";

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);


  string desired_output;
  desired_output = "As described in the problem text:\n";
  desired_output+= "Nodes 0, 1, 2, 3 form a cluster with tau = 2\n";
  desired_output+= "Nodes 2, 3 form a cluster with tau = 3\n";
  desired_output+= "No nodes form a cluster with tau = 4\n";

  cout << desired_output << endl;

  cout << "Calculated: " << endl << endl;
  cout << "tau = 2" << endl;
  cout << "Nodes" << endl;
  check_node(0, 2, N, row_ptr, col_idx, SNN_val);
  cout << "form a cluster." << endl << endl;

  cout << "tau = 3" << endl;
  cout << "Nodes" << endl;
  check_node(2, 3, N, row_ptr, col_idx, SNN_val);
  cout << "form a cluster." << endl << endl;

  cout << "tau = 4" << endl;
  check_node(0, 4, N, row_ptr, col_idx, SNN_val);
  check_node(1, 4, N, row_ptr, col_idx, SNN_val);
  check_node(2, 4, N, row_ptr, col_idx, SNN_val);
  check_node(3, 4, N, row_ptr, col_idx, SNN_val);
  check_node(4, 4, N, row_ptr, col_idx, SNN_val);


  return 0;
}
