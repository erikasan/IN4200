#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){
  char str1[10], str2[10];
  FILE* fp;
  fp = fopen("file.txt", "r");
  fscanf(fp, "%s %s", str1, str2);

  cout << str1 << " " << str2 << endl;

  fclose(fp);
  return 0;
}
