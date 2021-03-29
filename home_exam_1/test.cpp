#include <iostream>
#include "read_graph_from_file2.cpp"

#include "omp.h"

using namespace std;

void create_SNN_graph2(int N, int *row_ptr, int *col_idx, int **SNN_val);

int main(){
  char *filename = "simple-graph.txt";
  int N;
  int *row_ptr, *col_idx;

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  int *SNN_val;
  //create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);

  double start;
  double result = 0;
  int iter = (int) 1e5;
  int n = 10;
  for(int i = 0; i < n; i++){
    start = omp_get_wtime();
    for (int j = 0; j < iter; j++){
      create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);
    }
    result += omp_get_wtime() - start;
  }
  cout << (double) result/N << endl;

  // for (int i = 0; i < row_ptr[N]; i++){
  //   cout << SNN_val[i] << " ";
  // }
  // cout << endl;

  return 0;
}


void create_SNN_graph2(int N, int *row_ptr, int *col_idx, int **SNN_val){

  // Allocate SNN_val and fill with zeros;
  (*SNN_val) = new int[row_ptr[N]]{};

  int z, z2, to_n, shared_node;
  for (int k = 0; k < N; k++){
    z = row_ptr[k];
    z2 = row_ptr[k+1];

    for (int m = z; m < z2; m++){
      to_n = col_idx[m];

      for (int j = z; j < z2; j++){
        shared_node = col_idx[j];

        for (int i = row_ptr[to_n]; i < row_ptr[to_n+1]; i++){
          if (col_idx[i] == shared_node){
            (*SNN_val)[j] += 1;
          }
        }
      }
    }
  }


  return;
}
