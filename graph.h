// Author: TING-WEI SU
// Institute: Texas A&M University
// Date: 11/19/2022
// Project: Maximum Bandwidth Routing Algorithm

#ifndef SRC_CPP_GRAPH_H
#define SRC_CPP_GRAPH_H

#include <iostream>
#include <cstdlib>

using namespace std;

#define DEBUG_GRAPH     0
#define ENABLE_RANDOMESS    0

#define HUNDRED_PERCENT 100 // (%)


#define GRAPH_TYPE_1_VERTEX_AVG_DEG    6
#define GRAPH_TYPE_2_VERTEX_ADJACENCY_PERCENTAGE    20 / HUNDRED_PERCENT
#define GRAPH_VERTEX_MAX    5000
#define GRAPH_VERTEX_MIN    10
#define GRAPH_VERTEX_CYCLE_PERCENTAGE   50 / HUNDRED_PERCENT


#define GRAPH_EDGE_WEIGHT_MAX   100
#define GRAPH_EDGE_WEIGHT_MIN   10 


// Data structure to store adjacency list nodes
struct Vertex
{
    int val;    // val: connected vertex
    int cost;   // cost: cost to pay to neighbor vertex
    Vertex* next;
};
 
// Data structure to store a graph edge
struct Edge {
    int src, dest, weight;
};

// The type of graph: 1, 2
enum type {
    type_1, // Avg vertex degree = 6
    type_2, // Vertex is adjacent to 20% of the total vertices
};


class Graph
{
private:
    // An array of pointers to Vertex to represent the
    // adjacency list
    Vertex **head;

    // an array of graph edges
    Edge *edges;

    // Total number of vertices
    int N;   
    // Total number of edges 
    int M;
    // Random seed 
    int seed;

    // Function to allocate a new vertex for the adjacency list
    // To-Do: Temperarily work around, but why??
    Vertex * insertNewVertexAtHead(int value, int weight, Vertex* head);

    // Function to check if the new random generated edge is valid
    bool isEdgeValid(Edge edge, int idx);

    // Function to connect two vertices by new edges
    void connectVertices(Edge edge);

    // Function to search for alone vertex
    // By alone, I mean those vertex that has not been connected
    int searchAlonedVertex();

    // Function to search for connected vertex
    int searchConnectedVertex();
 
public:
    // Constructor default
    Graph();

    // Constructor by vertex number
    Graph(int N);

    // Constructor by graph type
    Graph(int N, enum type t);
 
    // Destructor
    ~Graph();

    // Function to print all neighboring vertices of a given vertex
    void printList(int i);

    // Function to get the vertex number
    int getVertexNum();

    // Function to get the edge number
    int getEdgeNum();

    // Function to get adjacency list
    Vertex * getAdjList(int v);

    // To-Do: check graph bipartiteness
    bool isBipartite();

    // To-Do: check graph connectivity
    bool isConnected();
};

#endif