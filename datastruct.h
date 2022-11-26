// Author: TING-WEI SU
// Institute: Texas A&M University
// Date: 11/19/2022
// Project: Maximum Bandwidth Routing Algorithm

#ifndef SRC_CPP_DATASTRUCT_H
#define SRC_CPP_DATASTRUCT_H

#include <iostream>
#include <assert.h>

using namespace std;

#define DEBUG_DATA_STRUCT   0

#define SIZE_MAX    10000
#define HEAP_SIZE_MAX   SIZE_MAX

#define left(i)     ((i << 1) + 1) // (2 * i + 1)
#define right(i)    ((i << 1) + 2) // (2 * i + 2)
#define parent(j)   ((j - 1) >> 1) // ((j - 1) / 2)

class MaxHeap
{
private: 
    unsigned int size;
    int * heap;
    int height;

    void swap(int &a, int &b);

    void max_heapify_up(int i);

    void max_heapify_down(int i);

public:
    MaxHeap();

    ~MaxHeap();

    // Insert new element to heap
    void insert(int x);

    // Remove an element from heap
    void removeMax();

    // Return the root of the heap
    int max();
};

#endif