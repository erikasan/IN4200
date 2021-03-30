void create_SNN_graph1(int N, char **table2D, int ***SNN_table){

  int i, j, k;

  // Allocate SNN_table and fill with zeros;
  (*SNN_table) = new int*[N];
  for (i = 0; i < N; i++){
    (*SNN_table)[i] = new int[N]{};
  }

  int s = 0;
  for (i = 0; i < N; i++){
    for (j = i + 1; j < N; j++){
      if (table2D[i][j]){
        for (k = 0; k < N; k++){
          s += table2D[i][k]*table2D[j][k];
        }
      }
      (*SNN_table)[i][j] = (*SNN_table)[j][i] = s;
      s = 0;
    }
  }

  return;
}
