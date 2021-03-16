#include <iostream>
#include <string>

using namespace std;

void read_graph_from_file1(string*** table2D);

int main(){
  string** table2D;
  read_graph_from_file1(&table2D);
  //cout << table2D[0][0] << endl;

  char i = 50;
  return 0;
}

void read_graph_from_file1(string*** table2D){
  (*table2D) = new string*;
  for (int i = 0; i < 2; i++){
    (*table2D)[i] = new string;
  }

  (*table2D)[0][0] = "0fjeifeji";

  return;
}
