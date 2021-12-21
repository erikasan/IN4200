#include <vector>

using namespace std;

void check_node(int node_id, int tau, int N, int *row_ptr, int *col_idx, int *SNN_val){
  vector<int> queue;
  int discovered[N]{};
  
  bool no_cluster = true;
  int node, discovered_node;

  queue.push_back(node_id);
  int nodes_in_queue = 1;

  while(nodes_in_queue){
    node = queue[0];
    queue.erase(queue.begin());
    nodes_in_queue--;

    for (int i = row_ptr[node]; i < row_ptr[node+1]; i++){
      discovered_node = col_idx[i];

      if (discovered[discovered_node] == 0 & SNN_val[i] >= tau){
        cout << discovered_node<< endl;
        discovered[discovered_node] = 1;
        queue.push_back(discovered_node);
        nodes_in_queue++;
        no_cluster = false;

      } // Endif
    } // End for
  } // End while

  if (no_cluster){
    cout << node_id << " does not belong in a cluster when threshold = " << tau << endl;
  }

  return;
}
