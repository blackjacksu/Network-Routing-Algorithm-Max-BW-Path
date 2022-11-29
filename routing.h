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

#define findmin(a, b) (a > b ? b : a)

// The type of vertex:
enum v_type {
    unseen = 0, // Init state of vertex
    intree, // The vertex we use to begin with and explore its neighbor 
    fringer, // The vertex that is neighbored to intree vertex
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
    bool w_heap;
    MaxHeap * Heap;

    // Without heap
    int * H;
    int * D;

    int Dijkstra_wHeap(int src, int dest, int * path);

    int Dijkstra(int src, int dest, int * path);

    int getLargestFringer();

public:
    // Constructors
    MaxBwDijkstra();

    MaxBwDijkstra(Graph * g, bool w_heap);

    // Destructor
    ~MaxBwDijkstra();

    // Find the max bandwidth path from src to dest
    int findMaxBWPath(int src, int dest, int * maxPath);
};

class MaxBwKruskal
{
private:
    Graph * G;
    int vertex_num;
    int edge_num;

    int * dad;
    int * rank;

    // Disjoint set operation:
    // Create a set whose only member is x
    void makeSet(int x);

    // Unites the two set that contain x and y
    // Say S = Sx U Sy
	void unionSet(int x, int y);

    // Find the root of x
	int find(int x);

    // Kruskal Maximum Spanning Tree 
    void KruskalMST();
public:
    // Constructors
    MaxBwKruskal();

    MaxBwKruskal(Graph * g);

    ~MaxBwKruskal();

    // Find the max bandwidth path from src to dest
    int findMaxBWPath(int src, int dest, int * maxPath);
};



#endif