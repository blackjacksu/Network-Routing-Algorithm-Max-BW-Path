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
    // Total number of nodes in the graph (labelled from 0 to 5)
    int N = 10;
 
    // Construct graphs
    Graph * graph = new Graph(N, type_1);
    Graph * graph2 = new Graph(N, type_2);

    MaxBwDijkstra * heap_dijkstra = new MaxBwDijkstra(graph, true);
    MaxBwDijkstra * array_dijkstra = new MaxBwDijkstra(graph, false);
    MaxBwDijkstra * heap_dijkstra_2 = new MaxBwDijkstra(graph2, true);

    // Randomly pick a source vertex and destination vertex


#if DEBUG_MAIN
    // print adjacency list representation of a graph
    cout << "Graph type 1" << endl;
    for (int i = 0; i < N; i++)
    {
        // print given vertex
        cout << i;
 
        // print all its neighboring vertices
        graph->printList(i);
    }

    cout << "Graph type 2" << endl;
    for (int i = 0; i < N; i++)
    {
        // print given vertex
        cout << i;
 
        // print all its neighboring vertices
        graph2->printList(i);
    }
#endif

    return 0;
}