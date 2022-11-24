// Author: TING-WEI SU
// Institute: Texas A&M University
// Date: 11/19/2022
// Project: Maximum Bandwidth Routing Algorithm

#include <iostream>
#include "graph.h"
#include "routing.h"
using namespace std;

#define DEBUG_MAIN  1

// Graph implementation in C++ without using STL
int main()
{
    // total number of nodes in the graph (labelled from 0 to 5)
    int N = 10;
 
    // construct graph
    Graph * graph = new Graph(N, type_1);
    MaxBwDijkstra * dijkstra = new MaxBwDijkstra(N, graph);

#if DEBUG_MAIN
    // print adjacency list representation of a graph
    for (int i = 0; i < N; i++)
    {
        // print given vertex
        cout << i;
 
        // print all its neighboring vertices
        graph->printList(i);
    }
#endif

    return 0;
}