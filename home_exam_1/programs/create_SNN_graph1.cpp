#include <iostream>
#include "../header_files/read_graph_from_file1.h"
#include "../header_files/create_SNN_graph1.h"

using namespace std;

int main(int argc, char *argv[]){
  char *filename = argv[1];
  int N;
  char **table2D;
  int **SNN_table;

  read_graph_from_file1(filename, &N, &table2D);
  
  create_SNN_graph1(N, table2D, &SNN_table);

  if (argc > 2){
    cout << "SNN_table" << endl;
    for (int i = 0; i < N; i++){
      for (int j = 0; j < N; j++){
        cout << SNN_table[i][j] << " ";
      }
      cout << endl;
    }
  }

  return 0;
}
