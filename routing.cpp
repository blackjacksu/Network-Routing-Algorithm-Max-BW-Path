#include "routing.h"

MaxBwDijkstra::MaxBwDijkstra()
{

}

MaxBwDijkstra::MaxBwDijkstra(Graph * g, bool w_heap)
{
    G = g;
    vertex_num = G->getEdgeNum();
    edge_num = G->getEdgeNum();

    status = new v_type[vertex_num] {unseen};
    dad = new int[vertex_num];
    fill_n(dad, sizeof(int) * vertex_num, -1);
    bwidth = new int[vertex_num];
    fill_n(bwidth, sizeof(int) * vertex_num, INT32_MAX);

    if (w_heap == true)
    {
        Heap = new MaxHeap();
    }
    else
    {
        H = new int[vertex_num];
        D = new int[vertex_num];
    }
}

MaxBwDijkstra::~MaxBwDijkstra()
{
    delete Heap;
    
    delete [] H;
    delete [] D;
    delete [] status;
    delete [] dad;
    delete [] bwidth;
}

int MaxBwDijkstra::findMaxBWPath(int src, int dest, int * maxPath)
{
    int maxbw = 0;



    while (!Heap->isEmpty())
    {

    }
    return maxbw;
}