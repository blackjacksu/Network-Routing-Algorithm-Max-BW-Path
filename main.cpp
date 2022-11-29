// Author: TING-WEI SU
// Institute: Texas A&M University
// Date: 11/19/2022
// Project: Maximum Bandwidth Routing Algorithm

#include <iostream>
#include <chrono>
#include "graph.h"
#include "routing.h"

using namespace std;

#define DEBUG_MAIN  1


void printPath(int src, int dest, int * path)
{
    int i = dest;
    while (path[i] != src)
    {
        i = path[dest];
        // print the path in reverse order
        cout << i << endl;
    }
}

// Graph implementation in C++ without using STL
int main()
{
    // Total number of nodes in the graph (labelled from 0 to 5)
    int N = 10;
    int src, dest;
    int path[10];
 
    // Construct graphs
    Graph * graph = new Graph(N, type_1);
    Graph * graph2 = new Graph(N, type_2);

    // Randomly pick a source vertex and destination vertex
    src = random() % N;
    dest = random() % N;

    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();
    MaxBwDijkstra * heap_dijkstra = new MaxBwDijkstra(graph, true);
    heap_dijkstra->findMaxBWPath(src, dest, path);
    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);

    MaxBwDijkstra * array_dijkstra = new MaxBwDijkstra(graph, false);
    array_dijkstra->findMaxBWPath(src, dest, path);
    printPath(src, dest, path);

    MaxBwDijkstra * heap_dijkstra_2 = new MaxBwDijkstra(graph2, true);
    heap_dijkstra_2->findMaxBWPath(src, dest, path);

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