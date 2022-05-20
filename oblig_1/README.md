For the serial implementation, compile with

`g++ main.cpp`

and run using

`./a.out [filename] [d] [epsilon] [n]`.

For example `./a.out example_web_graph.txt 1 0.00001 3` should result in the ouput

```
5 0.2025
6 0.18
7 0.295
```

For the parallelised implementation, compile with

`g++ main.cpp -fopenmp`

and run using the same command as above. Set the number of threads as usual by setting the global `OMP_NUM_THREADS` variable in the command line.
