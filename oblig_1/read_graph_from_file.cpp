
#include <fstream>

using namespace std;

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
    *val = new double[(*row_ptr)[*N]]{};

    infile.open(filename);

    infile.ignore(500, '\n');
    infile.ignore(500, '\n');
    infile.ignore(500, '\n');
    infile.ignore(500, '\n');

    int countersTo[*N]{};

    while (infile >> FromNodeId >> ToNodeId){
        if (FromNodeId != ToNodeId){
            (*col_idx)[(*row_ptr)[ToNodeId] + countersTo[ToNodeId]] = FromNodeId;
            (*val)[(*row_ptr)[ToNodeId] + countersTo[ToNodeId]] += countersFrom[FromNodeId];
            countersTo[ToNodeId]++;
        }   
    }

    infile.close();
    return;
}