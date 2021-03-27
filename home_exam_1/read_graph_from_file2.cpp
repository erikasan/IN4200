#include <iostream>
#include <fstream>


using namespace std;

void read_graph_from_file2(char *filename, int *N, int **row_ptr, int **col_idx);

int main(){
  char *filename = "simple-graph.txt";
  int N;
  int *row_ptr, *col_idx;

  read_graph_from_file2(filename, &N, &row_ptr, &col_idx);

  // for (int i = 0; i < N+1; i++){
  //   cout << row_ptr[i] << " ";
  // }
  // cout << endl;
  // for (auto c : col_idx){
  //   cout << c << " ";
  // }
  // cout << endl;

  return 0;
}

void read_graph_from_file2(char *filename, int *N, int **row_ptr, int **col_idx){

  // Open file
  ifstream infile(filename);

  // Skip the first two lines
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');

  // Dummy variable for reading "#" and "Nodes:"
  // 6 bytes allocated because "Nodes:" is 6 characters long
  char dummy[6];

  // Store the number of nodes in N
  infile >> dummy >> dummy >> *N;

  // Skip the rest of the 3rd line and the 4th line
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');

  // Allocate row_ptr
  *row_ptr = new int[*N+1];
  (*row_ptr)[0] = 0;

  int FromNodeId, ToNodeId;

  // Read in pairs of integers
  while (infile >> FromNodeId >> ToNodeId){

    // Check that the values are legal
    if (FromNodeId != ToNodeId){
    if (FromNodeId < *N){
    if (ToNodeId < *N){
    if (FromNodeId >= 0){
    if (ToNodeId >= 0){

      // If so, add 1 to the elements of row_ptr
      // representing FromNodeId and ToNodeId
      (*row_ptr)[FromNodeId+1] += 1;
      (*row_ptr)[ToNodeId+1]   += 1;

    }}}}} // End if
  } // End while

  infile.close();

  // Sum up the elements of row_ptr cumulatively
  for (int i = 2; i < *N+1; i++){
    (*row_ptr)[i] += (*row_ptr)[i-1];
  }

  // Allocate col_idx. It has size 2N_edges which is the last element of row_ptr
  *col_idx = new int[(*row_ptr)[*N]];

  // Open file again and skip first four lines
  infile.open(filename);
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');

  // Array of "counters" for each node that count the number of nearest neighbors
  // Initialized with zeros.
  int counters[*N]{};

  while(infile >> FromNodeId >> ToNodeId){

    if (FromNodeId != ToNodeId){
    if (FromNodeId < *N){
    if (ToNodeId < *N){
    if (FromNodeId >= 0){
    if (ToNodeId >= 0){

      (*col_idx)[ (*row_ptr)[FromNodeId] + counters[FromNodeId] ] = ToNodeId;
      (*col_idx)[ (*row_ptr)[ToNodeId]   + counters[ToNodeId] ]   = FromNodeId;
      counters[FromNodeId]++;
      counters[ToNodeId]++;

    }}}}} // End if
  } // End while

  for (int i = 0; i < (*row_ptr)[*N]; i++){
    cout << (*col_idx)[i] << endl;
  }

  infile.close();
  return;
}
