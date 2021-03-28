#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){
  for (int i = 0; i < edges;i++){
    (*col_idx)[(*row_ptr)[from[i]] + indx[from[i]]] = to[i];
    (*col_idx)[(*row_ptr)[to[i]] + indx[to[i]]] = from[i];
    indx[from[i]] += 1;
    indx[to[i]]   += 1;
  }
  return 0;
}
