// Author: TING-WEI SU
// Institute: Texas A&M University
// Date: 11/19/2022
// Project: Maximum Bandwidth Routing Algorithm

#include <iostream>
#include <chrono>
#include <iomanip>

#include "graph.h"
#include "routing.h"

using namespace std;

#define DEBUG_MAIN  0
#define TEST_GRAPH_NUM  5
#define TEST_SRC_DEST_NUM   5
#define ALGORITHM_NUM   3
#define DATA_SET_NUM    (TEST_GRAPH_NUM * TEST_SRC_DEST_NUM)

#define CONSOLE_DISPLAY_COLUMN_WIDTH   20

// Be cautious!! changing this to larger than 1500 might take 
// a long time to generate the graph because I enable the 
// randomness throughout all the vertex!!
#define VERTEX_NUM  1200


// Graph implementation in C++ without using STL
int main()
{
    // Total number of nodes in the graph (labelled from 0 to 5)
#if DEBUG_MAIN
    int N = 10;
#else
    int N = VERTEX_NUM;
    srand(time(NULL));
#endif
    int i = 0;
    int j;
    int src[TEST_SRC_DEST_NUM];
    int dest[TEST_SRC_DEST_NUM];


    // Randomly pick 5 pairs of source vertex and destination vertex
    while (i < TEST_SRC_DEST_NUM)
    {
        src[i] = rand() % N;
        dest[i] = rand() % N;

        if (src[i] == dest[i])
        {
            continue;
        }
        else
        {
            i++;
        }
    }

    Graph * graph1[TEST_GRAPH_NUM];
    Graph * graph2[TEST_GRAPH_NUM];

    for (i = 0; i < TEST_GRAPH_NUM; i++)
    {
        graph1[i] = new Graph(N, type_1);
        cout << "Graph " << i + 1 << ", type 1, generated." << endl;
        graph2[i] = new Graph(N, type_2);
        cout << "Graph " << i + 1 << ", type 2, generated." << endl;
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

    auto begin = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    double sum[6] = { 0.0 };
    double type_1_sum[TEST_GRAPH_NUM][ALGORITHM_NUM] = { 0.0 };
    double type_2_sum[TEST_GRAPH_NUM][ALGORITHM_NUM] = { 0.0 };

    int maxbw = 0;

    for (i = 0; i < TEST_GRAPH_NUM; i++)
    {
        for (j = 0; j < TEST_SRC_DEST_NUM; j++)
        {
            // Test - 1: Use Dijkstra without heap on type 1 Graph -------------
            cout << "[ Graph-" << i + 1 << " ] ";
            cout << "Dijkstra w/o heap on type 1 graph (s, t) = (" << src[j] << ", " << dest[j] << ") " << endl;
            begin = std::chrono::high_resolution_clock::now();

            array_dijkstra = new MaxBwDijkstra(graph1[i], false);
            maxbw = array_dijkstra->findMaxBWPath(src[j], dest[j]);

            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Bandwidth: " << maxbw << endl;
            cout << "Time: " << elapsed.count() * 1e-3 << " us." << endl;
            cout << endl;

            sum[0] += elapsed.count() * 1e-3;
            type_1_sum[i][0] += elapsed.count() * 1e-3;

            delete(array_dijkstra);
            // Test - 1: End ------------------------------------------------

            // Test - 2: Use Dijkstra with heap on type 1 Graph -------------
            cout << "[ Graph-" << i + 1 << " ] ";
            cout << "Dijkstra w/ heap on type 1 graph (s, t) = (" << src[j] << ", " << dest[j] << ") " << endl;
            begin = std::chrono::high_resolution_clock::now();

            heap_dijkstra = new MaxBwDijkstra(graph1[i], true);
            maxbw = heap_dijkstra->findMaxBWPath(src[j], dest[j]);

            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Bandwidth: " << maxbw << endl;
            cout << "Time: " << elapsed.count() * 1e-3 << " us." << endl;
            cout << endl;

            sum[1] += elapsed.count() * 1e-3;
            type_1_sum[i][1] += elapsed.count() * 1e-3;

            delete(heap_dijkstra);
            // Test - 2: End ---------------------------------------------------

            // Test - 3: Use Kruskal with heap on type 1 Graph -----------------
            cout << "[ Graph-" << i + 1 << " ] ";
            cout << "Kruskal on type 1 graph (s, t) = (" << src[j] << ", " << dest[j] << ") " << endl;
            begin = std::chrono::high_resolution_clock::now();

            kruskal = new MaxBwKruskal(graph1[i]);
            maxbw = kruskal->findMaxBWPath(src[j], dest[j]);

            // Stop measuring time and calculate the elapsed time
            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Bandwidth: " << maxbw << endl;
            cout << "Time: " << elapsed.count() * 1e-3 << " us." << endl;
            cout << endl;

            sum[2] += elapsed.count() * 1e-3;
            type_1_sum[i][2] += elapsed.count() * 1e-3;

            delete(kruskal);
            // Test - 3: End ---------------------------------------------------
            
            // Test - 4: Use Dijkstra without heap on type 2 Graph -------------
            cout << "[ Graph-" << i + 1 << " ] ";
            cout << "Dijkstra w/o heap on type 2 graph (s, t) = (" << src[j] << ", " << dest[j] << ") " << endl;
            begin = std::chrono::high_resolution_clock::now();

            array_dijkstra = new MaxBwDijkstra(graph2[i], true);
            maxbw = array_dijkstra->findMaxBWPath(src[j], dest[j]);

            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Bandwidth: " << maxbw << endl;
            cout << "Time: " << elapsed.count() * 1e-3 << " us." << endl;
            cout << endl;

            sum[3] += elapsed.count() * 1e-3;
            type_2_sum[i][0] += elapsed.count() * 1e-3;

            delete(array_dijkstra);
            // Test - 4: End ---------------------------------------------------

            // Test - 5: Use Dijkstra with heap on type 2 Graph ----------------
            cout << "[ Graph-" << i + 1 << " ] ";
            cout << "Dijkstra w/ heap on type 2 graph (s, t) = (" << src[j] << ", " << dest[j] << ") " << endl;
            begin = std::chrono::high_resolution_clock::now();

            heap_dijkstra = new MaxBwDijkstra(graph2[i], true);
            maxbw = heap_dijkstra->findMaxBWPath(src[j], dest[j]);

            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Bandwidth: " << maxbw << endl;
            cout << "Time: " << elapsed.count() * 1e-3 << " us." << endl;
            cout << endl;

            sum[4] += elapsed.count() * 1e-3;
            type_2_sum[i][1] += elapsed.count() * 1e-3;

            delete(heap_dijkstra);
            // Test - 5: End ---------------------------------------------------
            
            // Test - 6: Use Kruskal on type 2 Graph ---------------------------
            cout << "[ Graph-" << i + 1 << " ] ";
            cout << "Kruskal on type 2 graph (s, t) = (" << src[j] << ", " << dest[j] << ") " << endl;
            begin = std::chrono::high_resolution_clock::now();
            
            kruskal = new MaxBwKruskal(graph2[i]);
            maxbw = kruskal->findMaxBWPath(src[j], dest[j]);

            end = std::chrono::high_resolution_clock::now();
            elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            cout << "Bandwidth: " << maxbw << endl;
            cout << "Time: " << elapsed.count() * 1e-3 << " us." << endl;
            cout << endl;

            sum[5] += elapsed.count() * 1e-3;
            type_2_sum[i][2] += elapsed.count() * 1e-3;

            delete(kruskal);
            // Test - 6: End ---------------------------------------------------
        }
    }

    // Print the result table for two type of graph
    // Versue three algorthm 
    cout << "Result Summary" << endl;
    cout << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Type \\ Algorithm"
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Dijkstra"
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Dijkstra heap" 
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Kruskal" 
         << endl;
    
    cout << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Graph type 1"
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << sum[0] / DATA_SET_NUM
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << sum[1] / DATA_SET_NUM
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << sum[2] / DATA_SET_NUM
         << endl;

    cout << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Graph type 2"
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << sum[3] / DATA_SET_NUM
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << sum[4] / DATA_SET_NUM
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << sum[5] / DATA_SET_NUM
         << endl;
    
    cout << "Type 1 Graph Summary" << endl;
    cout << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Graph \\ Algorithm"
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Dijkstra"
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Dijkstra heap" 
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Kruskal" 
         << endl;
    for (i = 0; i < TEST_GRAPH_NUM; i++)
    {
        cout << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Graph" << i
             << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << type_1_sum[i][0] / TEST_SRC_DEST_NUM
             << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << type_1_sum[i][1] / TEST_SRC_DEST_NUM
             << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << type_1_sum[i][2] / TEST_SRC_DEST_NUM
             << endl;
    }

    cout << "Type 2 Graph Summary" << endl;
    cout << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Graph \\ Algorithm"
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Dijkstra"
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Dijkstra heap" 
         << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Kruskal" 
         << endl;
    
    for (i = 0; i < TEST_GRAPH_NUM; i++)
    {
        cout << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << "Graph" << i + 1
             << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << type_2_sum[i][0] / TEST_SRC_DEST_NUM
             << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << type_2_sum[i][1] / TEST_SRC_DEST_NUM
             << setw(CONSOLE_DISPLAY_COLUMN_WIDTH) << type_2_sum[i][2] / TEST_SRC_DEST_NUM
             << endl;
    }
    return 0;
}