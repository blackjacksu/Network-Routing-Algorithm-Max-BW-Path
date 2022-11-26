#include "routing.h"

MaxBwDijkstra::MaxBwDijkstra()
{

}

MaxBwDijkstra::MaxBwDijkstra(bool w_heap)
{
    if (w_heap == true)
    {
        Heap = new MaxHeap();
    }
    else
    {
        H = new int[SIZE_MAX];
        D = new int[SIZE_MAX];
    }
}

MaxBwDijkstra::~MaxBwDijkstra()
{
    delete Heap;
    
    delete [] H;
    delete [] D;
}

int MaxBwDijkstra::findMaxBWPath(Graph * g, int src, int dest, int * maxPath)
{
    int maxbw = 0;
    G = g;

    return maxbw;
}