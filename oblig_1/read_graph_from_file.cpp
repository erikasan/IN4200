
#include <fstream>

using namespace std;

void bubble_sort(int **col_idx, 
                 double **val, 
                 int start, 
                 int stop){
    /*
    Shameless copy from https://www.programiz.com/dsa/bubble-sort
    Bubble sort is a standard algorithm and I do not claim to have invented it.
    */
    int size = stop - start;
    for (int i = 0; i < size - 1; i++){
        
        int swapped = 0;
        
        for (int j = start; j < stop - i - 1; j++){

            if ((*col_idx)[j] > (*col_idx)[j+1]){

                int temp_idx = (*col_idx)[j];
                int temp_val = (*val)[j];
            
                (*col_idx)[j] = (*col_idx)[j+1];
                (*val)[j] = (*val)[j+1];

                (*col_idx)[j+1] = temp_idx;
                (*val)[j+1] = temp_val;

                swapped = 1;
            }
        }

        if (swapped == 0){
            break;
        }
    }
    return;
}

void read_graph_from_file(char *filename, 
                          int *N, 
                          int **row_ptr, 
                          int **col_idx, 
                          double **val){

    // Open file
    ifstream infile;
    infile.open(filename);

    // Skip the first two lines
    infile.ignore(500, '\n');
    infile.ignore(500, '\n');

    // Dummy variable for reading "#", "Nodes:" and "Edges:"
    char dummy[6];

    // Store the number of webpages in N.
    // N+1 will be the number of elements in row_ptr
    infile >> dummy >> dummy >> *N;

    // Skip the rest of the 3rd line and the 4th line
    infile.ignore(500, '\n');
    infile.ignore(500, '\n');

    // Allocate row_ptr and fill with zeros
    *row_ptr = new int[*N+1]{};

    int FromNodeId, ToNodeId;

    int countersFrom[*N]{};
    int countersTo[*N]{};

    // Read in pairs of integers
    while (infile >> FromNodeId >> ToNodeId){

        // Exclude self-links
        if (FromNodeId != ToNodeId){
            (*row_ptr)[ToNodeId+1]   += 1;
            countersFrom[FromNodeId] += 1;
        }
    }
    
    infile.close();

    for (int i = 2; i < *N+1; i++){
        (*row_ptr)[i] += (*row_ptr)[i-1];
    }

    *col_idx = new int[(*row_ptr)[*N]];
    *val = new double[(*row_ptr)[*N]];

    infile.open(filename);

    infile.ignore(500, '\n');
    infile.ignore(500, '\n');
    infile.ignore(500, '\n');
    infile.ignore(500, '\n');

    while (infile >> FromNodeId >> ToNodeId){
        if (FromNodeId != ToNodeId){
            (*col_idx)[(*row_ptr)[ToNodeId] + countersTo[ToNodeId]] = FromNodeId;
            (*val)[(*row_ptr)[ToNodeId] + countersTo[ToNodeId]] = countersFrom[FromNodeId];
            countersTo[ToNodeId]++;
        }   
    }

    for (int i = 0; i < *N; i++){
        bubble_sort(col_idx, val, (*row_ptr)[i], (*row_ptr)[i+1]);
    }

    infile.close();

    return;
}