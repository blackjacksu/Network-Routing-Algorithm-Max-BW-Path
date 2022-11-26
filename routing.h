// Author: TING-WEI SU
// Institute: Texas A&M University
// Date: 11/19/2022
// Project: Maximum Bandwidth Routing Algorithm

#ifndef SRC_CPP_ROUTING_H
#define SRC_CPP_ROUTING_H

#include <iostream>
#include "graph.h"
#include "datastruct.h"

using namespace std;

#define DEBUG_MAX_BW_PATH 0

class MaxBwDijkstra
{
private:
    Graph * G;

    // With heap
    MaxHeap * Heap;

    // Without heap
    int * H;
    int * D;

public:
    // Constructors
    MaxBwDijkstra();

    MaxBwDijkstra(bool w_heap);

    // Destructor
    ~MaxBwDijkstra();

    int MaxBwDijkstra::findMaxBWPath(Graph * g, int src, int dest, int * maxPath);

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