# IN4200 Home Exam 1

To compile the programs, make `compile.sh` executable (if it's not already) with

```
chmod a+x compile.sh
```

Compile with

```
./compile.sh
```

This will produce the five main executables

* read_graph_from_file1
* read_graph_from_file2
* create_SNN_graph1
* create_SNN_graph2
* check_node

The first four executables can be run with

```
./[executable] [filename] ([output])
```

where `executable` is the name of the executable, `filename` is the name of the text file containing the connectivity graph, and `output` is an optional argument which can be anything whatsoever (e.g. `1`). If `output` is given, the output is printed to the terminal (obviously not recommended for large connectivity graphs).

The executable `check_node` can be run with

```
./check_node [filename] [node_id] [tau]
```

where `node_id` is the id of the node to be checked if it belongs to a cluster and `tau` is the SNN threshold as described in the problem text. The output is always printed to the terminal as it shouldn't be too overwhelming.

The actual implementations of the functions can be found in the folder `header_files` while the executables correspond to the programs in the `programs` folder.

Test programs along with executables can be found in the `tests` folder. The implementations are tested against the same connectivity graph presented in the problem text. The test functions work in the stupidest way possible, by simply printing the desired and calculated outputs to the screen respectively and letting the user visually verify that they are the same (apparently this was ok with Xing :P).

The executables corresponding to the test functions are simply run with

```
./[executable]
```

i.e no arguments needed.
