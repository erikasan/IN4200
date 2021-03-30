g++ -o read_graph_from_file1 programs/read_graph_from_file1.cpp

g++ -o read_graph_from_file2 programs/read_graph_from_file2.cpp

g++ -o create_SNN_graph1 programs/create_SNN_graph1.cpp

g++ -o create_SNN_graph2 programs/create_SNN_graph2.cpp

g++ -o check_node programs/check_node.cpp


g++ -o test_read_graph_from_file1 tests/test_read_graph_from_file1.cpp

g++ -o test_read_graph_from_file2 tests/test_read_graph_from_file2.cpp

g++ -o test_create_SNN_graph1 tests/test_create_SNN_graph1.cpp

g++ -o test_create_SNN_graph2 tests/test_create_SNN_graph2.cpp

g++ -o test_check_node tests/test_check_node.cpp


mv test_read_graph_from_file1 tests
mv test_read_graph_from_file2 tests
mv test_create_SNN_graph1 tests
mv test_create_SNN_graph2 tests
mv test_check_node tests
