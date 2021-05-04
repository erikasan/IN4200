Compile with

```
mpicxx MPI_main.cpp -o main
```

Run with

```
mpirun -np [number of processes] main M N K1 K2
```

where `M, N` are the dimensions of the input matrix, `K1` is the dimension of the first kernel and `K2` is the dimension of the second kernel.
