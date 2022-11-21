// Author: TING-WEI SU
// Institute: Texas A&M University
// Date: 11/19/2022
// Project: Maximum Bandwidth Routing Algorithm

#include <iostream>
#include "graph.h"
using namespace std;

 


// Graph implementation in C++ without using STL
int main()
{
    // total number of nodes in the graph (labelled from 0 to 5)
    int N = 6;
 
    // construct graph
    Graph graph(N);
 
    // print adjacency list representation of a graph
    for (int i = 0; i < N; i++)
    {
        // print given vertex
        cout << i;
 
        // print all its neighboring vertices
        graph.printList(i);
    }
 
    return 0;
}