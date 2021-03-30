void create_SNN_graph2(int N, int *row_ptr, int *col_idx, int **SNN_val){

  // Allocate SNN_val and fill with zeros;
  (*SNN_val) = new int[row_ptr[N]]{};

  int i, j, k, node1, node2, node3, start, end;

  // Loop over each node
  for (node1 = 0; node1 < N; node1++){
    start = row_ptr[node1];
    end   = row_ptr[node1+1];

    // Find each node (node2) connected to node1
    for (i = start; i < end; i++){
      node2 = col_idx[i];

      // Loop over each node connected to node1
      for (j = start; j < end; j++){
        node3 = col_idx[j];

        // Loop over each node conntected to node2
        for (k = row_ptr[node2]; k < row_ptr[node2+1]; k++){

          // If both are connected to node3
          if (node3 == col_idx[k]){
            (*SNN_val)[j]++;
  }}}}}

  return;
}
