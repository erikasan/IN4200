#include <iostream>
#include <exception>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]);

    int* a;

    try
    {
        a = new int[n];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (size_t i = 0; i < n; i++)
    {
        a[i] = rand() % 10;
        //a[i] = i;
    }

    int *min, *max;

    min = min_element(a, a+n);
    max = max_element(a, a+n);

    cout << "min element: " << *min << "\n";
    cout << "max element: " << *max << "\n";

    return 0;
}
