#include <iostream>
#include "read_graph_from_file2.cpp"

using namespace std;

void create_SNN_graph2(int N, int *row_ptr, int *col_idx, int **SNN_val);

int main(){
  char *filename = "simple-graph.txt";
  int N;
  int *row_ptr, *col_idx2;

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx2);

  int col_idx[] = {1,2,3,0,2,3,0,1,3,4,0,1,2,4,2,3};
  int *SNN_val;
  create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);



  for (int i = 0; i < row_ptr[N]; i++){
    cout << SNN_val[i] << " ";
  }
  cout << endl;

  return 0;
}

void create_SNN_graph2(int N, int *row_ptr, int *col_idx, int **SNN_val){

  // Allocate SNN_val and fill with zeros;
  (*SNN_val) = new int[row_ptr[N]]{};

  int d[N];
  int result[N]{};

  int m = 0;
  for (int i = 0; i < N; i++){
    // Make d here
    for (int j = 0; j < N; j++){
      for (int k = row_ptr[j]; k < row_ptr[j+1]; k++){
        result[j] += d[col_idx[k]];
    }}

    for (int l = 0; l < N; l++){
      if (result[l]){
        (*SNN_val)[m] = result[l];
        m++;
      }
      result[l] = d[l] = 0;
    }
  }

  // Lag Matrise - vektor multiplikasjon metoden i test.cpp

  return;
}
