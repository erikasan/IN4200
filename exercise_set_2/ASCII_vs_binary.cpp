#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

int main(){

  int N_fibonacci = (int) 100;

  long int a = 1;
  long int b = 1;
  long int temp;
  long int in_number;

  ifstream infile;
  ofstream outfile;

  time_t start_ASCII;
  time_t stop_ASCII;
  time_t start_binary;
  time_t stop_binary;

  string binary_file = "binary_file.bin";
  string ASCII_file  = "ASCII_file.txt";

  // Write and read ASCII

  start_ASCII = clock();
  outfile.open(ASCII_file, ios::out);
  for (int i = 0; i < N_fibonacci; i++){
    temp = a;
    a = a + b;
    b = temp;
    outfile << a << endl;
  }
  outfile.close();

  infile.open(ASCII_file, ios::out);
  for (int i = 0; i < N_fibonacci; i++){
    infile >> in_number;
  }
  infile.close();
  stop_ASCII = clock();

  a = 1; b = 1;

  // Write and read Binary
  start_binary = clock();
  outfile.open(binary_file, ios::out | ios::binary);
  for (int i = 0; i < N_fibonacci; i++){
    temp = a;
    a = a + b;
    b = temp;
    outfile << a << endl;
  }
  outfile.close();

  infile.open(binary_file, ios::out | ios::binary);
  for (int i = 0; i < N_fibonacci; i++){
    infile >> in_number;
  }
  infile.close();
  stop_binary = clock();

  double diff_ASCII  = difftime(stop_ASCII, start_ASCII);
  double diff_binary = difftime(stop_binary, start_binary);

  double ratio = diff_ASCII/diff_binary;

  cout << "ASCII clock cycles: " << diff_ASCII << endl;
  cout << "Binary clock cycles: " << diff_binary << endl;
  cout << "ASCII to binary ratio: " << ratio << endl;

  return 0;
}
