#include <iostream>
//#include <fstream>
#include "../header_files/read_graph_from_file1.h"

using namespace std;

int main(int argc, char *argv[]){

  char *filename = argv[1];
  int N;
  char **table2D;

  read_graph_from_file1(filename, &N, &table2D);

  if (argc > 2){
    cout << "table2D" << endl;
    for (int i = 0; i < N; i++){
      for (int j = 0; j < N; j++){
        printf("%d ", table2D[i][j]);
      }
      cout << endl;
    }
  }

  return 0;
}

// void read_graph_from_file1(char *filename, int *N, char ***table2D){
//
//   // Open file
//   ifstream infile(filename);
//
//   // Skip the first two lines
//   infile.ignore(100, '\n');
//   infile.ignore(100, '\n');
//
//   // Dummy variable for reading "#" and "Nodes:"
//   // 6 bytes allocated because "Nodes:" is 6 characters long
//   char dummy[6];
//
//   // Store the number of nodes in N
//   infile >> dummy >> dummy >> *N;
//
//   // Skip the rest of the 3rd line and the 4th line
//   infile.ignore(100, '\n');
//   infile.ignore(100, '\n');
//
//   // Allocate table2D
//   // NOTE: char instances are automatically initialized to zero.
//   *table2D = new char*[*N];
//   for (int i = 0; i < *N; i++){
//     (*table2D)[i] = new char[*N];
//   }
//
//   int FromNodeId, ToNodeId;
//
//   // Read in pairs of integers
//   while (infile >> FromNodeId >> ToNodeId){
//
//     // Check that the values are legal
//     if (FromNodeId != ToNodeId){
//     if (FromNodeId < *N){
//     if (ToNodeId < *N){
//     if (FromNodeId >= 0){
//     if (ToNodeId >= 0){
//
//       // If so, set the corresponding matrix elements to 1
//       (*table2D)[FromNodeId][ToNodeId] = (*table2D)[ToNodeId][FromNodeId] = 1;
//
//     }}}}} // End if
//   } // End while
//
//   infile.close();
//   return;
// }
