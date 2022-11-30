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
#define TEST_GRAPH_NUM  5
#define TEST_SRC_DEST_NUM   5

#define VERTEX_NUM  5000


// Graph implementation in C++ without using STL
int main()
{
    // Total number of nodes in the graph (labelled from 0 to 5)
#if DEBUG_MAIN
    int N = 10;
#else
    int N = VERTEX_NUM;
#endif
    int i;
    int j;
    int src[TEST_SRC_DEST_NUM];
    int dest[TEST_SRC_DEST_NUM];

    // Randomly pick 5 pairs of source vertex and destination vertex
    for (i = 0; i < TEST_SRC_DEST_NUM; i++)
    {
        src[i] = random() % N;
        dest[i] = random() % N;
    }

    Graph * graph1[TEST_GRAPH_NUM];
    Graph * graph2[TEST_GRAPH_NUM];

    for (i = 0; i < TEST_GRAPH_NUM; i++)
    {
        graph1[i] = new Graph(N, type_1);
        graph2[i] = new Graph(N, type_2);
    }

#if DEBUG_MAIN
    // print adjacency list representation of a graph
    cout << "Graph type 1" << endl;
    for (i = 0; i < N; i++)
    {
        // print given vertex
        cout << i;
 
        // print all its neighboring vertices
        graph1[0]->printList(i);
    }
    
    for (i = 0; i < N; i++)
    {
        // print given vertex
        cout << i;
 
        // print all its neighboring vertices
        graph1[1]->printList(i);
    }

    cout << "First Graph type 2" << endl;
    for (i = 0; i < N; i++)
    {
        // print given vertex
        cout << i;
 
        // print all its neighboring vertices
        graph2[0]->printList(i);
    }
    cout << "Second Graph type 2" << endl;
    for (i = 0; i < N; i++)
    {
        // print given vertex
        cout << i;
 
        // print all its neighboring vertices
        graph2[1]->printList(i);
    }
#endif
    MaxBwDijkstra * array_dijkstra;
    MaxBwDijkstra * heap_dijkstra;
    MaxBwKruskal * kruskal;

    for (i = 0; i < TEST_GRAPH_NUM; i++)
    {
        for (j = 0; j < TEST_SRC_DEST_NUM; j++)
        {
            // Test - 1: Use Dijkstra without heap on type 1 Graph -------------
            auto begin = std::chrono::high_resolution_clock::now();

            array_dijkstra = new MaxBwDijkstra(graph1[i], false);
            array_dijkstra->findMaxBWPath(src[j], dest[j]);

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Time: " << elapsed.count() * 1e-3 << "us." << endl;

            delete(array_dijkstra);
            // Test - 1: End ---------------------------------------------------

            // Test - 2: Use Dijkstra with heap on type 1 Graph -------------
            begin = std::chrono::high_resolution_clock::now();

            heap_dijkstra = new MaxBwDijkstra(graph1[i], true);
            heap_dijkstra->findMaxBWPath(src[j], dest[j]);

            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Time: " << elapsed.count() * 1e-3 << "us." << endl;

            delete(heap_dijkstra);
            // Test - 2: End ---------------------------------------------------

            // Test - 3: Use Kruskal with heap on type 1 Graph -----------------
            begin = std::chrono::high_resolution_clock::now();

            kruskal = new MaxBwKruskal(graph1[i]);
            kruskal->findMaxBWPath(src[j], dest[j]);

            // Stop measuring time and calculate the elapsed time
            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Time: " << elapsed.count() * 1e-3 << "us." << endl;

            delete(kruskal);
            // Test - 3: End ---------------------------------------------------
            
            // Test - 4: Use Dijkstra without heap on type 2 Graph ----------------
            begin = std::chrono::high_resolution_clock::now();

            array_dijkstra = new MaxBwDijkstra(graph2[i], true);
            array_dijkstra->findMaxBWPath(src[j], dest[j]);

            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Time: " << elapsed.count() * 1e-3 << "us." << endl;

            delete(array_dijkstra);
            // Test - 4: End ---------------------------------------------------

            // Test - 5: Use Dijkstra with heap on type 2 Graph ----------------
            begin = std::chrono::high_resolution_clock::now();

            heap_dijkstra = new MaxBwDijkstra(graph2[i], true);
            heap_dijkstra->findMaxBWPath(src[j], dest[j]);

            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Time: " << elapsed.count() * 1e-3 << "us." << endl;

            delete(heap_dijkstra);
            // Test - 5: End ---------------------------------------------------
            
            // Test - 3: Use Kruskal with heap on type 2 Graph -----------------
            begin = std::chrono::high_resolution_clock::now();
            
            kruskal = new MaxBwKruskal(graph2[i]);
            kruskal->findMaxBWPath(src[j], dest[j]);

            // Stop measuring time and calculate the elapsed time
            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Time: " << elapsed.count() * 1e-3 << "us." << endl;

            delete(kruskal);
            // Test - 3: End ---------------------------------------------------
        }
    }

    return 0;
}