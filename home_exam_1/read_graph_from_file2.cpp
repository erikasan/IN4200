void read_graph_from_file2(char *filename, int *N, int **row_ptr, int **col_idx);

int main(){
  char *filename = "simple-graph.txt";
  int N;
  int *row_ptr, *col_idx;

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  return 0;
}

void read_graph_from_file2(char *filename, int *N, int **row_ptr, int **col_idx){
  return;
}
