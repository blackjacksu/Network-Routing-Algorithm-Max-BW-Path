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

#define DATA_SIZE_MAX    5000000
#define HEAP_SIZE_MAX   DATA_SIZE_MAX
#define STACK_SIZE_MAX  DATA_SIZE_MAX

#define left(i)     ((i << 1) + 1) // (2 * i + 1)
#define right(i)    ((i << 1) + 2) // (2 * i + 2)
#define parent(j)   ((j - 1) >> 1) // ((j - 1) / 2)

struct node {
    int idx;
    int bw;
};

class MaxHeap
{
private: 
    unsigned int size;
    struct node * heap;
    int height;

    void swap(struct node &a, struct node &b);

    void max_heapify_up(int i);

    void max_heapify_down(int i);

public:
    MaxHeap();

    ~MaxHeap();

    // Insert new element to heap
    void insertNode(int idx, int bw);

    // Remove an element from heap
    void removeMax();

    // Remove certain element from heap
    void removeNode(int bw);

    // Return the root of the heap
    int getMax();
    
    // Emptiness of heap 
    bool isEmpty();
};


class Stack
{
private:
    int top;
public:
    // Array method implemented stack
    int stack[STACK_SIZE_MAX];
     
    // Constructor
    Stack();

    // Push to stack
    bool push(int x);

    // Pop from stack
    int pop();

    // Check the emptiness of stack
    bool isEmpty();
};

#endif