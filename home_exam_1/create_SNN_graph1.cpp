#include <iostream>
#include "read_graph_from_file1.cpp"
#include <omp.h>

using namespace std;

void create_SNN_graph1(int N, char **table2D, int ***SNN_table);

int main(){
  char *filename = "simple-graph.txt";
  int N;
  char **table2D;

  read_graph_from_file1(filename, &N, &table2D);

  int **SNN_table;

  int iter = (int) 1e5;
  double start, result;

  start = omp_get_wtime();

  for (int i = 0; i < iter; i++){
    create_SNN_graph1(N, table2D, &SNN_table);
  }

  result = omp_get_wtime() - start;

  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      cout << SNN_table[i][j] << " ";
    }
    cout << endl;
  }

  cout << result << endl;

  return 0;
}

void create_SNN_graph1(int N, char **table2D, int ***SNN_table){

  // Allocate SNN_table and fill with zeros;
  (*SNN_table) = new int*[N];
  for (int i = 0; i < N; i++){
    (*SNN_table)[i] = new int[N]{};
  }

  int s = 0;
  for (int i = 0; i < N; i++){
    for (int j = i + 1; j < N; j++){
      if (table2D[i][j]){
        for (int k = 0; k < N; k++){
          s += table2D[i][k]*table2D[j][k];
        }
      }
      (*SNN_table)[i][j] = (*SNN_table)[j][i] = s;
      s = 0;
    }
  }

  return;
}
