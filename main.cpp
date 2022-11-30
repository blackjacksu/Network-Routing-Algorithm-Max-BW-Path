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

#define VERTEX_NUM  5000


// Graph implementation in C++ without using STL
int main()
{
    // Total number of nodes in the graph (labelled from 0 to 5)
    int N = 10;
    // int N = VERTEX_NUM;
    int src, dest;
 
    // Construct graphs
    Graph * graph = new Graph(N, type_1);
    Graph * graph2 = new Graph(N, type_2);

    // Randomly pick a source vertex and destination vertex
    src = random() % N;
    dest = random() % N;

    cout << "s: " << src << "-> t: " << dest << endl;

    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    MaxBwDijkstra * heap_dijkstra = new MaxBwDijkstra(graph, true);
    heap_dijkstra->findMaxBWPath(src, dest);

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "Time: " << elapsed.count() * 1e-3 << "us." << endl;


    // Start measuring time
    begin = std::chrono::high_resolution_clock::now();

    MaxBwDijkstra * array_dijkstra = new MaxBwDijkstra(graph, false);
    array_dijkstra->findMaxBWPath(src, dest);

    // Stop measuring time and calculate the elapsed time
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "Time: " << elapsed.count() * 1e-3 << "us." << endl;

    // Start measuring time
    begin = std::chrono::high_resolution_clock::now();

    MaxBwDijkstra * heap_dijkstra_2 = new MaxBwDijkstra(graph2, true);
    heap_dijkstra_2->findMaxBWPath(src, dest);
        
    // Stop measuring time and calculate the elapsed time
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "Time: " << elapsed.count() * 1e-3 << "us." << endl;


    // Start measuring time
    begin = std::chrono::high_resolution_clock::now();
    MaxBwKruskal * kruskal = new MaxBwKruskal(graph);
    kruskal->findMaxBWPath(src, dest);

    // Stop measuring time and calculate the elapsed time
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    cout << "Time: " << elapsed.count() * 1e-3 << "us." << endl;


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