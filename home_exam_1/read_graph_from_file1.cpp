
#include <iostream>
#include <cstdlib>
#include <fstream>


using namespace std;

void read_graph_from_file1(char *filename, int *N, char ***table2D);

int main(){
  char* filename = "simple-graph.txt";
  int N;
  char** table;

  read_graph_from_file1(filename, &N, &table);

  return 0;
}

void read_graph_from_file1(char *filename, int *N, char ***table2D){
  *N = 2;
  *table2D = (char**) malloc((*N)*sizeof(char));
  for (int i = 0; i < *N; i++){
    **table2D = (char*) malloc((*N)*sizeof(char));
  }

  char FromNodeId[5], ToNodeId[5];

  ifstream infile(filename);

  // Skip the first four lines
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');

  // Get down to business
  while (infile >> FromNodeId >> ToNodeId){
    // Do something
  }

  // infile >> FromNodeId;
  // infile >> ToNodeId;

  cout << FromNodeId << " " << ToNodeId << endl;


  infile.close();



  return;
}
