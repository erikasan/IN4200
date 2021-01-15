/* Verifying that the limit of 1 - 1/2^2 + 1/2^4 - 1/2^6 + ... is 4/5 */

#include <iostream>

using namespace std;

int main(){

  int N;
  double sum   = 1;
  double term  = 1;
  double exact = (double) 4/5;

  cout << "Enter the number of terms in the sum: ";
  cin  >> N;
  cout << endl;

  for (int i = 0; i < N; i++){
    term /= -4; // Effectively multiplying by -1/2^2
    sum += term;

  }

  cout << "sum = " << sum << endl;
  cout << "exact = " << exact << endl;
  cout << "sum - exact = " << sum - exact << endl;

  return 0;
}
