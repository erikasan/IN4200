#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
    double sum = 1;
    double denom = 1;
    int N = 100;
    
    double ans = 4./5;

    for (size_t i = 0; i < N; i++)
    {
        denom *= -2*2;
        sum += 1./denom;
    }

    cout << sum << "\n";
    cout << ans << "\n";
    
    return 0;
}
