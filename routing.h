// Author: TING-WEI SU
// Institute: Texas A&M University
// Date: 11/19/2022
// Project: Maximum Bandwidth Routing Algorithm

#ifndef SRC_CPP_ROUTING_H
#define SRC_CPP_ROUTING_H

#include <iostream>
#include "graph.h"

using namespace std;

#define DEBUG_MAX_BW_PATH 0

class MaxBwDijkstra
{
private:
    Graph * G;
public:
    // Constructors
    MaxBwDijkstra();

    MaxBwDijkstra(int N);

    MaxBwDijkstra(int N, Graph * g);

    ~MaxBwDijkstra();

};

#endif