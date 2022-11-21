#include "graph.h"

Graph::Graph(int N)
{
    // allocate memory
    head = new Vertex*[N]();
    this->N = N;

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