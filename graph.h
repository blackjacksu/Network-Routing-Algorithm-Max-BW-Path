#include <iostream>

using namespace std;

#define DEBUG_GRAPH 0

// Data structure to store adjacency list nodes
struct Vertex
{
    int val, cost;
    Vertex* next;
};
 
// Data structure to store a graph edge
struct Edge {
    int src, dest, weight;
};


class Graph
{
private:
    // An array of pointers to Vertex to represent the
    // adjacency list
    Vertex **head;

    // total number of vertices in the graph
    int N;    

    int M = 5; 

    // an array of graph edges
    Edge edges[5] =
    {
        // (x, y, w) —> edge from `x` to `y` having weight `w`
        {0, 1, 6}, {1, 2, 7}, {2, 0, 5}, 
        {3, 2, 10}, {4, 5, 1},
    };

    // Function to allocate a new vertex for the adjacency list
    Vertex* getAdjListVertex(int value, int weight, Vertex* head);
 
public:

    // Constructor
    Graph(int N);
 
    // Destructor
    ~Graph();

    // Function to print all neighboring vertices of a given vertex
    void printList(int i);
};