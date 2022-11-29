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
        dad[i] = 0;
        bwidth[i] = 0;
    }

    if (this->w_heap == true)
    {
        Heap = new MaxHeap();
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
    int ret = 0;

    if (w_heap == true)
    {
        ret = Dijkstra_wHeap(src, dest, maxPath);
    }
    else
    {
        ret = Dijkstra(src, dest, maxPath);
    }

    return ret;
}

int MaxBwDijkstra::Dijkstra_wHeap(int src, int dest, int * path)
{
    int maxbw = 0;
    int i = 0;
    int j = 0;
    int v = 0;

    status[src] = intree;
    dad[src] = -1;
    bwidth[src] = INT32_MAX;

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
            Heap->insertNode(i, bwidth[i]);
        }
    }

    // Extract the largest bwidth vertex from Heap until it is empty
    while (!Heap->isEmpty())
    {
        // Get max (root) from heap
        v = Heap->getMax();
        Heap->removeMax();

        // Mark the largest fringer vertex as intree
        status[v] = intree;
        ptr = G->getAdjList(v);

        while (ptr != NULL)
        {
            if (status[ptr->val] == unseen)
            {
                status[ptr->val] = fringer;
                dad[ptr->val] = v;
                bwidth[ptr->val] = findmin(bwidth[v], ptr->cost);
                Heap->insertNode(ptr->val, bwidth[ptr->val]);
            }
            else if (status[ptr->val] == fringer 
                    && bwidth[ptr->val] < findmin(bwidth[v], ptr->cost))
            {
                Heap->removeNode(ptr->val);
                dad[ptr->val] = v;
                bwidth[ptr->val] = findmin(bwidth[v], ptr->cost);
                Heap->insertNode(ptr->val, bwidth[ptr->val]);
            }

            ptr = ptr->next;
        }
    }

    maxbw = bwidth[dest];

    // Print the path
    j = dest;
    while (dad[j] != src)
    {
        j = dad[j];
        // print the path in reverse order
        cout << j << "<-" << endl;
    }
    cout << src << endl;

    return maxbw;
}

int MaxBwDijkstra::Dijkstra(int src, int dest, int * path)
{
    int maxbw = 0;
    // int i = 0;
    int j = 0;
    int v = 0;
    int count = 0; // fringer count

    status[src] = intree;
    dad[src] = -1;
    bwidth[src] = INT32_MAX;

    // Get neighbor vertex of src
    Vertex * ptr = G->getAdjList(src);
    
    // Init the neighbor of src as fringer
    while (ptr != NULL)
    {
        status[ptr->val] = fringer;
        count++;
        dad[ptr->val] = src;
        bwidth[ptr->val] = ptr->cost;

        ptr = ptr->next;
    }

    // // Add fringer vertex to heap
    // for (i = 0; i < vertex_num; i++)
    // {
    //     if (status[i] == fringer)
    //     {
    //         count++;
    //     }
    // }

    // Extract the largest bwidth vertex from Heap until it is empty
    while (count > 0)
    {
        // Get largest bwidth fringer
        v = getLargestFringer();
        if (v < 0)
        {
            break;
        }
        // Mark the largest fringer vertex as intree
        status[v] = intree;
        count--;
        ptr = G->getAdjList(v);

        while (ptr != NULL)
        {
            if (status[ptr->val] == unseen)
            {
                status[ptr->val] = fringer;
                count++;
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

    maxbw = bwidth[dest];

    // Print the path
    j = dest;
    while (dad[j] != src)
    {
        j = dad[j];
        // print the path in reverse order
        cout << j << "<-" << endl;
    }
    cout << src << endl;

    return maxbw;
}

int MaxBwDijkstra::getLargestFringer()
{
    // Linearly search the largest fringer
    int maxfringerid = -1; // return -1 when no more fringer is found
    int maxbw = 0;
    int i = 0;

    for (i = 0; i < vertex_num; i++)
    {
        if (bwidth[i] >= maxbw && status[i] == fringer)
        {
            maxbw = bwidth[i];
            maxfringerid = i;
        }
    }
    return maxfringerid;
}

// Kruskal Maximum Bandwidth Path

void MaxBwKruskal::makeSet(int x)
{
    // Create a set of its own
    rank[x] = 0;
    dad[x] = x;
}

void MaxBwKruskal::unionSet(int x, int y)
{
    // Union by rank
    int x_root = find(x);
    int y_root = find(y);

    if (x_root == y_root)
    {
        // Already in the same set
        return;
    }

    int x_rank = rank[x];
    int y_rank = rank[y];

    if (x_rank > y_rank)
    {
        // Make x the dad of y
        dad[y] = x;
    }
    else if (x_rank < y_rank)
    {
        // Make y the dad of x
        dad[x] = y;
    }
    else
    {
        // Where x_rank = y_rank
        dad[y] = x;
        rank[x]++;
    }
    
}

int MaxBwKruskal::find(int x)
{
    // If x is the root of itself
    if (dad[x] == x) {
        return x;
    }
    else {
        return find(dad[x]);
    }
}

MaxBwKruskal::MaxBwKruskal()
{

}

MaxBwKruskal::MaxBwKruskal(Graph * g)
{
    int i;
    G = g;
    vertex_num = G->getEdgeNum();
    edge_num = G->getEdgeNum();

    dad = new int [vertex_num];
    rank = new int [vertex_num];

    for (i = 0; i < vertex_num; i++)
    {
        dad[i] = INT32_MIN;
        rank[i] = INT32_MIN;
    }

}

MaxBwKruskal::~MaxBwKruskal()
{

}