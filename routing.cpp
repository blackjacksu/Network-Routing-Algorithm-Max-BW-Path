#include "routing.h"

MaxBwDijkstra::MaxBwDijkstra()
{
    // Default
}

MaxBwDijkstra::MaxBwDijkstra(Graph * g, bool w_heap)
{
    int i;
    G = g;
    vertex_num = G->getEdgeNum();
    edge_num = G->getEdgeNum();
    this->w_heap = w_heap;

    status = new v_type[vertex_num] {unseen};
    dad = new int[vertex_num];
    // fill_n(dad, sizeof(int) * vertex_num, -1);
    bwidth = new int[vertex_num];
    // fill_n(bwidth, sizeof(int) * vertex_num, INT32_MAX);
    for (i = 0; i < vertex_num; i++)
    {
        dad[i] = -1;
        bwidth[i] = INT32_MAX;
    }

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
    int i = 0;
    int v = 0;

    status[src] = intray;

    // Get neighbor vertex of src
    Vertex * ptr = G->getAdjList(src);
    
    // Init the neighbor of src as fringer
    while (ptr != NULL)
    {
        status[ptr->val] = fringer;
        dad[ptr->val] = src;
        bwidth[ptr->val] = ptr->cost;

        ptr = ptr->next;
    }

    // Add fringer vertex to heap
    for (i = 0; i < vertex_num; i++)
    {
        if (status[i] == fringer)
        {
            if (w_heap == true)
            {
                Heap->insert(i);
            }
            else
            {
                // 
            }
        }
    }

    // Extract the largest bwidth vertex from Heap until it is empty
    while (!Heap->isEmpty())
    {
        v = Heap->max();
        Heap->removeMax();
        status[v] = intray;
        ptr = G->getAdjList(v);

        while (ptr != NULL)
        {
            if (status[ptr->val] == unseen)
            {
                status[ptr->val] = fringer;
                dad[ptr->val] = v;
                bwidth[ptr->val] = findmin(bwidth[v], ptr->cost);
            }
            else if (status[ptr->val] == fringer 
                    && bwidth[ptr->val] < findmin(bwidth[v], ptr->cost))
            {
                dad[ptr->val] = v;
                bwidth[ptr->val] = findmin(bwidth[v], ptr->cost);
            }

            ptr = ptr->next;
        }
    }
    return maxbw;
}