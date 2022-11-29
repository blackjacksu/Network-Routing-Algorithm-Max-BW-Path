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

        // Insert at the beginning for src vertex
        Vertex * newVertex = insertNewVertexAtHead(dest, weight, head[src]);

        // To-Do: point head pointer to the new node
        head[src] = newVertex;

        // Insert at the beginning for dest vertex
        newVertex = insertNewVertexAtHead(src, weight, head[dest]);

        // To-Do: change head pointer to point to the new node
        head[dest] = newVertex;
    }
}

Graph::Graph(int N, enum type t)
{
    head = new Vertex*[N]();
    this->N = N;
    int M_cycle = 0;
    int src_prev = 0;
    int src_begin = 0;
    int i = 0;
    int aloned = 0;
    int connected = 0;
    bool isvalid = false;
    bool isallconnected = false;
    // Providing a seed value
#if ENABLE_RANDOMESS
	srand((unsigned) time(NULL));
#endif

    // initialize head pointer for all vertices
    for (int i = 0; i < N; i++) 
    {
        head[i] = nullptr;
    }

    switch (t)
    {
        case type_1:
            // Allocate memory according to total number of edges 
            M = N * GRAPH_TYPE_1_VERTEX_AVG_DEG / 2;
            edges = new Edge[M];

            M_cycle = M * GRAPH_VERTEX_CYCLE_PERCENTAGE;
            // Ensure the connectivity form a cycle of 100 vertex
            i = 0;
            src_prev = rand() % N;
            src_begin = src_prev;

            // Form the graph with at lease one cycle
            while (i < M_cycle)
            {
                if (i == M_cycle - 1)
                {
                    // The last edge is to connect back to the beginning vertex
                    edges[i].src = src_prev;
                    edges[i].dest = src_begin;
                    edges[i].weight = rand() % GRAPH_EDGE_WEIGHT_MAX + 1;
                }
                else
                {
                    edges[i].src = src_prev;
                    edges[i].dest = rand() % N;
                    edges[i].weight = rand() % GRAPH_EDGE_WEIGHT_MAX + 1;
                }

                isvalid = isEdgeValid(edges[i], i);

                if (isvalid == true)
                {
                    // This is the stage where we are still constructing cycle
                    // Last dest become next src
                    src_prev = edges[i].dest;

                    connectVertices(edges[i]);
                    
                    i++;
                }
            }

            // Second stage of forming the graph
            // Connect the vertex in the cycle list with new vertex
            while (i < M)
            {
                // Search for vertex that is not connected
                if (isallconnected == false)
                {
                    aloned = searchAlonedVertex();
                    connected = searchConnectedVertex();
                    if (aloned < 0)
                    {
                        isallconnected = true;
                    }
                    else
                    {
                        edges[i].src = connected;
                        edges[i].dest = aloned;
                        edges[i].weight = rand() % GRAPH_EDGE_WEIGHT_MAX + 1;
                    }
                }
                else
                {
                    edges[i].src = rand() % N;
                    edges[i].dest = rand() % N;
                    edges[i].weight = rand() % GRAPH_EDGE_WEIGHT_MAX + 1;
                }

                isvalid = isEdgeValid(edges[i], i);

                if (isvalid == true)
                {
                    // This is the stage where we are still constructing cycle
                    // Last dest become next src
                    src_prev = edges[i].dest;

                    connectVertices(edges[i]);
                    
                    i++;
                }
            }
            break;
        case type_2:
            // 20% of vertex in neighbor 
            // Allocate memory according to total number of edges 
            M = N * N * GRAPH_TYPE_2_VERTEX_ADJACENCY_PERCENTAGE / 2;
            edges = new Edge[M];

            M_cycle = M * GRAPH_VERTEX_CYCLE_PERCENTAGE;
            // Ensure the connectivity form a cycle of 100 vertex
            i = 0;
            src_prev = rand() % N;
            src_begin = src_prev;

            // Form the graph with at lease one cycle
            while (i < M_cycle)
            {
                if (i == M_cycle - 1)
                {
                    // The last edge is to connect back to the beginning vertex
                    edges[i].src = src_prev;
                    edges[i].dest = src_begin;
                    edges[i].weight = rand() % GRAPH_EDGE_WEIGHT_MAX + 1;
                }
                else
                {
                    edges[i].src = src_prev;
                    edges[i].dest = rand() % N;
                    edges[i].weight = rand() % GRAPH_EDGE_WEIGHT_MAX + 1;
                }

                isvalid = isEdgeValid(edges[i], i);

                if (isvalid == true)
                {
                    // This is the stage where we are still constructing cycle
                    // Last dest become next src
                    src_prev = edges[i].dest;

                    connectVertices(edges[i]);
                    
                    i++;
                }
            }

            // Second stage of forming the graph
            // Connect the vertex in the cycle list with new vertex
            while (i < M)
            {
                // Search for vertex that is not connected
                if (isallconnected == false)
                {
                    aloned = searchAlonedVertex();
                    connected = searchConnectedVertex();
                    if (aloned < 0)
                    {
                        isallconnected = true;
                    }
                    else
                    {
                        edges[i].src = connected;
                        edges[i].dest = aloned;
                        edges[i].weight = rand() % GRAPH_EDGE_WEIGHT_MAX + 1;
                    }
                }
                else
                {
                    edges[i].src = rand() % N;
                    edges[i].dest = rand() % N;
                    edges[i].weight = rand() % GRAPH_EDGE_WEIGHT_MAX + 1;
                }

                isvalid = isEdgeValid(edges[i], i);

                if (isvalid == true)
                {
                    // This is the stage where we are still constructing cycle
                    // Last dest become next src
                    src_prev = edges[i].dest;

                    connectVertices(edges[i]);
                    
                    i++;
                }
            }
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
    delete[] edges;
}

void Graph::insertNewVertexAtHead(int value, int weight, Vertex* head)
{
    Vertex* newVertex = new Vertex;
    newVertex->val = value;
    newVertex->cost = weight;

    // point new node to the current head
    newVertex->next = head;
            
    // // point head pointer to the new node
    // head = newVertex;

    // To-Do: Workaround
    return newVertex;
}

bool Graph::isEdgeValid(Edge edge, int idx)
{
    bool isvalid = true;
    int j = 0;
    // Check invalid edge and regenerate again
    if (edges[idx].src == edges[idx].dest)
    {
        // Invalid undirected edge
        // self to self
        isvalid = false;
    }
    else
    {
        for (j = 0; j < idx; j++)
        {
            if ((edges[j].src == edges[idx].src 
                && edges[j].dest == edges[idx].dest) 
                || (edges[j].src == edges[idx].dest 
                && edges[j].dest == edges[idx].src))
            {
                // Check previous generated edges
                // Invalid edges: duplicate edges w/ different weight
                isvalid = false;
            }
        }
    }
    return isvalid;
}

void Graph::connectVertices(Edge edge)
{
    int src, dest, weight;
    
    // add edges to the directed graph
    src = edge.src;
    dest = edge.dest;
    weight = edge.weight;

    // Insert at the beginning for src vertex
    Vertex * newVertex = insertNewVertexAtHead(dest, weight, head[src]);
    
    // To-Do: point head pointer to the new node
    head[src] = newVertex;

    // Insert at the beginning for dest vertex
    newVertex = insertNewVertexAtHead(src, weight, head[dest]);
    
    // To-Do: change head pointer to point to the new node
    head[dest] = newVertex;
}

int Graph::searchAlonedVertex()
{
    int i = 0;
    while (head[i] != NULL)
    {
        if (i < N)
        {
            i++;
        }
        else
        {   
            // Couldn't find aloned vertex
            // All vertex is connected
            return -1;
        }
    }
    return i;
}

int Graph::searchConnectedVertex()
{
    // Randomly pick connected vertex
    int i = rand() % N;
    while (head[i] == NULL)
    {
        i = rand() % N;
    }
    return i;
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

int Graph::getVertexNum()
{
    return N;
}


int Graph::getEdgeNum()
{
    return M;
}

Vertex * Graph::getAdjList(int v)
{
    if (v < N)
    {
        return head[v];
    }
    // Bug: when v >= N, will not return
    return NULL;
}

bool Graph::isBipartite()
{
    bool ret = false;

    return ret;
}

bool Graph::isConnected()
{
    bool ret = false;

    return ret;
}