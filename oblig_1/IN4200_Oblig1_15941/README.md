### IMPORTANT

This is the second time I'm taking this course. I also had IN4200 in the spring 2021 semester with candidate number 15815. This assignment is similar to the first home exam of last year. The way graphs are represented in text files is identical, and in both the home exam and this assignment we're asked to write a function read_graph_from_file that reads the text files and represents the graphs as matrices in CRS format. For this function I have taken my previous work and made the neccessary changes to fit this assignment. Apparently, not informing you of this counts as cheating, which is why I felt it necessary to write this.


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

`g++ main_omp.cpp -fopenmp`

and run using the same command as above. Set the number of threads as usual by setting the global `OMP_NUM_THREADS` variable in the command line.