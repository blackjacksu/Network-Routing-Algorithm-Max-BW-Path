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

    delete(G);
}

int MaxBwDijkstra::findMaxBWPath(int src, int dest)
{
    int ret = 0;

    if (w_heap == true)
    {
        ret = Dijkstra_wHeap(src, dest);
    }
    else
    {
        ret = Dijkstra(src, dest);
    }

    return ret;
}

int MaxBwDijkstra::Dijkstra_wHeap(int src, int dest)
{
    int maxbw = 0;
    int i = 0;
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
    printPath(src, dest);

    return maxbw;
}

int MaxBwDijkstra::Dijkstra(int src, int dest)
{
    int maxbw = 0;
    // int i = 0;
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
    printPath(src, dest);

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

void MaxBwDijkstra::printPath(int src, int dest)
{
    // Print the path
    int j = dest;
    int pop = 0;
    Stack stk;

    while (dad[j] != src)
    {
        j = dad[j];
        stk.push(j);
    }
    cout << src;
    while (!stk.isEmpty())
    {
        pop = stk.pop();
        cout << "->";
        cout << pop;
    }
    cout << endl;
}

// Kruskal Maximum Bandwidth Path
MaxBwKruskal::MaxBwKruskal()
{

}

MaxBwKruskal::MaxBwKruskal(Graph * g)
{
    int i;
    G = g;
    vertex_num = G->getEdgeNum();
    edge_num = G->getEdgeNum();
    MST = new Graph(vertex_num, type_1, edge_num);

    dad = new int [vertex_num];
    rank = new int [vertex_num];

    mst_status = new v_type[vertex_num] {unseen};
    mst_dad = new int[vertex_num];
    // fill_n(mst_dad, sizeof(int) * vertex_num, -1);
    mst_bwidth = new int[vertex_num];
    // fill_n(mst_bwidth, sizeof(int) * vertex_num, -1);

    for (i = 0; i < vertex_num; i++)
    {
        dad[i] = INT32_MIN;
        rank[i] = INT32_MIN;
        
        mst_dad[i] = INT32_MIN;
        mst_bwidth[i] = 0;
    }
    Heap = new MaxHeap[edge_num];
}

int MaxBwKruskal::findMaxBWPath(int src, int dest)
{
    int maxbw = INT32_MAX;
    int i = dest;
    KruskalMST();

    DFS(src);

    // Extract the max bw
    while (mst_dad[i] != src)
    {
        maxbw = findmin(maxbw, mst_bwidth[i]);
        i = mst_dad[i];
    }

    // Print the max bw path
    printPath(src, dest, mst_dad);

    return maxbw;
}

void MaxBwKruskal::DFS(int s)
{
    mst_status[s] = fringer;

    // Get neighbor vertex of src
    Vertex * ptr = G->getAdjList(s);
    
    // Init the neighbor of src as fringer
    while (ptr != NULL)
    {
        if (mst_status[ptr->val] == unseen)
        {
            mst_dad[ptr->val] = s;
            mst_bwidth[ptr->val] = ptr->cost;
            DFS(ptr->val);
        }

        ptr = ptr->next;
    }

    mst_status[s] = intree;
}

MaxBwKruskal::~MaxBwKruskal()
{
    delete []Heap;
    delete []rank;
    delete []dad;

    delete(G);
    delete(MST);
}

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
    else 
    {
        return find(dad[x]);
    }
}

void MaxBwKruskal::KruskalMST()
{
    int i = 0;
    int size;
    int j = 0;
    int u, v;
    Vertex ** V = new Vertex * [vertex_num]();
    // Add edges in non decresing order
    Edge * edges = G->getEdgeList(size);
    
    for (i = 0; i < vertex_num; i++)
    {
        makeSet(i);
    }

    for (i = 0; i < vertex_num; i++)
    {
        V[i] = G->getAdjList(i);
    }

    if (size != edge_num)
    {
        // Examine the case
        // Should not happen
        cout << "Error: The size should be the same." << endl;
    }

    for (i = 0; i < size; i++)
    {
        Heap->insertNode(i, edges[i].weight);
    }
    
    while (!Heap->isEmpty())
    {
        j = Heap->getMax();
        Heap->removeMax();

        u = edges[j].src;
        v = edges[j].dest;

        if (find(u) != find(v))
        {
            // Add the edge to MST 
            unionSet(u, v);
            MST->addEdge(u, v, edges[j].weight);
        }
    }
}

void MaxBwKruskal::printPath(int src, int dest, int * d)
{
    // Print the path
    int j = dest;
    int pop = 0;
    Stack stk;
    int * parent = d;

    while (parent[j] != src)
    {
        j = parent[j];
        stk.push(j);
    }

    cout << src;
    while (!stk.isEmpty())
    {
        pop = stk.pop();
        cout << "->";
        cout << pop;
    }
}