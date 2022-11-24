#include "graph.h"

Graph::Graph()
{
    int i = 0;
    N = 5;
    M = 5;
    edges = new Edge[M];

    edges[i++] = {0, 1, 6};
    edges[i++] = {1, 2, 7};
    edges[i++] = {2, 0, 5};
    edges[i++] = {3, 2, 10};
    edges[i++] = {4, 5, 1};
}

Graph::Graph(int N)
{
    int i = 0;
    M = 5;
    edges = new Edge[M];
    head = new Vertex*[N]();
    this->N = N;

    edges[i++] = {0, 1, 6};
    edges[i++] = {1, 2, 7};
    edges[i++] = {2, 0, 5};
    edges[i++] = {3, 2, 10};
    edges[i++] = {4, 5, 1};

    // initialize head pointer for all vertices
    for (int i = 0; i < N; i++) 
    {
        head[i] = nullptr;
    }

    // add edges to the directed graph
    for (unsigned i = 0; i < this->M; i++)
    {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;

        // insert at the beginning
        Vertex* newVertex = getAdjListVertex(dest, weight, head[src]);

        // point head pointer to the new node
        head[src] = newVertex;

        // uncomment the following code for undirected graph
        newVertex = getAdjListVertex(src, weight, head[dest]);
        // change head pointer to point to the new node
        head[dest] = newVertex;
    }
}

Graph::Graph(int N, enum type t)
{
    head = new Vertex*[N]();
    this->N = N;
    int M_cycle = 0;
    int src_prev = 0;
    int i = 0;
    // // Providing a seed value
	// srand((unsigned) time(NULL));
    seed = rand();

    switch (t)
    {
        case type_1:
            // Allocate memory according to total number of edges 
            M = GRAPH_VERTEX_AVG_DEG * N / 2;
            edges = new Edge[M];


            M_cycle = M * HUNDRED_PERCENT / GRAPH_VERTEX_CYCLE_PERCENTAGE;
            // Ensure the connectivity form a cycle of 100 vertex
            i = 0;
            src_prev = rand() % N;
            while (i < M_cycle)
            {
                edges[i].src = src_prev;
                edges[i].dest = rand() % N;
                edges[i].weight = rand() % GRAPH_EDGE_WEIGHT_MAX + 1;

                if (edges[i].src == edges[i].dest)
                {
                    // Invalid edge
                    continue;
                }
                
                i++;

                // Last dest become next src
                src_prev = edges[i].dest;
            }

            // initialize head pointer for all vertices
            for (int i = 0; i < N; i++) 
            {
                head[i] = nullptr;
            }

            // add edges to the directed graph
            for (unsigned i = 0; i < this->M; i++)
            {
                int src = edges[i].src;
                int dest = edges[i].dest;
                int weight = edges[i].weight;

                // insert at the beginning
                Vertex* newVertex = getAdjListVertex(dest, weight, head[src]);

                // point head pointer to the new node
                head[src] = newVertex;

                // uncomment the following code for undirected graph
                newVertex = getAdjListVertex(src, weight, head[dest]);
                // change head pointer to point to the new node
                head[dest] = newVertex;
            }

            break;
        case type_2:

            break;
        default: 
            break;
    }
}

Graph::~Graph() 
{
    for (int i = 0; i < N; i++) 
    {
        delete[] head[i];
    }

    delete[] head;
}

Vertex* Graph::getAdjListVertex(int value, int weight, Vertex* head)
{
    Vertex* newVertex = new Vertex;
    newVertex->val = value;
    newVertex->cost = weight;

    // point new node to the current head
    newVertex->next = head;

    return newVertex;
}

void Graph::printList(int i)
{
    Vertex *ptr = head[i];
    while (ptr != nullptr)
    {
        cout << "(" << i << ", " << ptr->val << ", " << ptr->cost << ") ";
        ptr = ptr->next;
    }
    cout << endl;
}