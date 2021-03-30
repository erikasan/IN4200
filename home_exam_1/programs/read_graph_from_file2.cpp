#include <iostream>
#include <fstream>
#include "../header_files/read_graph_from_file2.h"

using namespace std;

int main(int argc, char *argv[]){
  char *filename = argv[1];
  int N;
  int *row_ptr, *col_idx;

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  if (argc > 2){
    cout << "row_ptr = [ ";
    for (int i = 0; i < N+1; i++){
      cout << row_ptr[i] << " ";
    }
    cout << "]" << endl;

    cout << "col_idx = [ ";
    for (int i = 0; i < row_ptr[N]; i++){
      cout << col_idx[i] << " ";
    }
    cout << "]" << endl;
  }


  return 0;
}
