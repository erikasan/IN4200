#include <iostream>
#include <fstream>

using namespace std;

int main(){
  char s1[20], s2[20];
  char s3[20];
  ifstream infile("simple-graph.txt");
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');
  infile.ignore(100, '\n');

  infile >> s1;
  infile >> s2;
  infile >> s3;

  cout << s1 << " " << s2 << endl;
  cout << s3 << endl;
  return 0;
}
