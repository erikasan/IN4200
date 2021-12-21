#include <iostream>
#include "../header_files/read_graph_from_file2.h"
#include "../header_files/create_SNN_graph2.h"

using namespace std;

int main(int argc, char *argv[]){
  char *filename = argv[1];
  int N;
  int *row_ptr, *col_idx;
  int *SNN_val;

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  create_SNN_graph2(N, row_ptr, col_idx, &SNN_val);

  if (argc > 2){
    cout << "SNN_val = [ ";
    for (int i = 0; i < row_ptr[N]; i++){
      cout << SNN_val[i] << " ";
    }
    cout << " ]" << endl;
  }

  return 0;
}
