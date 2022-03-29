#include <random>
#include <iostream>


using namespace std;

void swap(double *a, 
          double *b){

    double tmp = *b;
    *b = *a;
    *a = tmp;
    return;
}

int partition(double *array, 
              int start, 
              int stop, 
              int pivotIndex){

    double pivotValue = array[pivotIndex];

    int storeIndex = start;

    swap(&array[pivotIndex], &array[stop]);


    for (int i = start; i < stop; i++){
    
        if (array[i] > pivotValue){
            swap(&array[storeIndex], &array[i]);
            storeIndex++;
        }
    }

    swap(&array[stop], &array[storeIndex]);

    return storeIndex;
}

double quickselect(double *array, 
                   int start, 
                   int stop, 
                   int n){
    /*
    Shameless copy from https://en.wikipedia.org/wiki/Quickselect.
    Finding the k-th largest element of an array is a common procedure in which many standard algorithms already exist.
    No need to reinvent the wheel.
    */
    if (start == stop){
        return array[start];
    }

    

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(start, stop);

    int pivotIndex = uni(rng);

    pivotIndex = partition(array, 
                           start, 
                           stop, 
                           pivotIndex);

    if (n == pivotIndex){
        return array[n];
    }

    else if (n < pivotIndex){
        return quickselect(array, 
                           start, 
                           pivotIndex - 1, 
                           n);
    }

    else{
        return quickselect(array, 
                           pivotIndex + 1, 
                           stop, 
                           n);
    }
}


void top_n_webpages(int N, 
                    double *scores, 
                    int n){


    double temp_scores[N]; // Because quickselect also sorts the array which is not what I wanted

    for (int i = 0; i < N; i++){
        temp_scores[i] = scores[i];
    }

    double nth_largest = quickselect(temp_scores, 
                                     0, 
                                     N, 
                                     n-1);

    #pragma omp parallel for
    for (int i = 0; i < N; i++){
        if (scores[i] >= nth_largest){
            printf("%d %f\n", i, scores[i]);
        }
    }

    // No idea why this gives me an error
    //delete[] temp_scores;

    return;
}
