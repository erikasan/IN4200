#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    
    int max_iterations = 1000;
    int batch_size = 100;

    for (int k = 1; k <= max_iterations; k++){
        if (!(k%batch_size)){
            cout << k << "\n";
        }
    }

    return 0;
}
