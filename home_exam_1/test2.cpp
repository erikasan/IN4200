#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){

  return 0;
}

void create_SNN_graph2(int N, int *row_ptr, int *col_idx, int **SNN_val){

  // Allocate SNN_val and fill with zeros;
  (*SNN_val) = new int[row_ptr[N]]{};

  int d[N]{};
  int result[N]{};

  int m = 0;
  for (int i = 0; i < N; i++){

    for (int p = row_ptr[i]; p < row_ptr[i+1]; p++){
      d[col_idx[p]] = 1;
    }

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
