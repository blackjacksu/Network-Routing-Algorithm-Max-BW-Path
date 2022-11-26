// Author: TING-WEI SU
// Institute: Texas A&M University
// Date: 11/25/2022
// Project: Maximum Bandwidth Routing Algorithm

#ifndef SRC_CPP_ROUTING_H
#define SRC_CPP_ROUTING_H

#include <iostream>
// #include <algorithm>
#include "graph.h"
#include "datastruct.h"

using namespace std;

#define DEBUG_MAX_BW_PATH 0

// The type of vertex:
enum v_type {
    unseen = 0, // Init state of vertex
    intray, // The vertex we use to begin with and explore its neighbor 
    fringer, // The vertex that is neighbored to intray vertex
};

class MaxBwDijkstra
{
private:
    Graph * G;
    int vertex_num;
    int edge_num;

    v_type * status;
    int * bwidth;
    int * dad;

    // With heap
    MaxHeap * Heap;

    // Without heap
    int * H;
    int * D;

public:
    // Constructors
    MaxBwDijkstra();

    MaxBwDijkstra(Graph * g, bool w_heap);

    // Destructor
    ~MaxBwDijkstra();

    int findMaxBWPath(int src, int dest, int * maxPath);

};

class MaxBwKruskal
{
private:
    Graph * G;
public:
    // Constructors
    MaxBwKruskal();

    MaxBwKruskal(int N);

    MaxBwKruskal(int N, Graph * g);

    ~MaxBwKruskal();

};



#endif