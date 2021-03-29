#include <iostream>
//#include "read_graph_from_file2.cpp"

#include "omp.h"

using namespace std;

void create_SNN_graph2(int N, int *row_ptr, int *col_idx, int **SNN_val);

// int main(){
//   char *filename = "simple-graph.txt";
//   int N;
//   int *row_ptr, *col_idx;
//
//   read_graph_from_file2(filename, &N, &row_ptr, &col_idx);
//
//   int *SNN_val;
//   create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);
//
//   double start;
//   double result = 0;
//   int iter = (int) 1e5;
//   int n = 10;
//   for(int i = 0; i < n; i++){
//     start = omp_get_wtime();
//     for (int j = 0; j < iter; j++){
//       create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);
//     }
//     result += omp_get_wtime() - start;
//   }
//   cout << (double) result/N << endl;
//
//   for (int i = 0; i < row_ptr[N]; i++){
//     cout << SNN_val[i] << " ";
//   }
//   cout << endl;
//
//   return 0;
// }

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
