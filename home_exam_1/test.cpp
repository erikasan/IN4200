#include <iostream>
#include <valarray>

using namespace std;

int main(){
  valarray<int> a = {1,2,3,4,5,6,7,8};
  //int b[] = a[0 .. 2 : 1
  //cout << a.end() << endl;
  //valarray<int> b = a[std::slice(0,3,1)];
  int b[8];
  b = a[std::slice(0,3,1)];
  for (auto c : b){
    cout << c << endl;
  }
  return 0;
}
