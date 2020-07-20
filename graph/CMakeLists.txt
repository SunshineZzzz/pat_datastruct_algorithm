add_executable(GraphAdjacencyMatrix GraphAdjacencyMatrix.cc)
add_test(NAME GraphAdjacencyMatrix COMMAND GraphAdjacencyMatrix)

add_executable(GraphAdjacencyList GraphAdjacencyList.cc)
add_test(NAME GraphAdjacencyList COMMAND GraphAdjacencyList)

add_executable(DFS DFS.cc)
add_test(NAME DFS COMMAND DFS)

add_executable(BFS BFS.cc)
add_test(NAME BFS COMMAND BFS)