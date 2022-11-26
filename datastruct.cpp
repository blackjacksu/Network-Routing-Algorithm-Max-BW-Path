#include "datastruct.h"

MaxHeap::MaxHeap()
{
    size = 0;
    heap = new int[HEAP_SIZE_MAX];
}

// MaxHeap::MaxHeap(unsigned int n)
// {
//     assert(n < HEAP_SIZE_MAX);

//     size = n;
//     heap = new int[HEAP_SIZE_MAX];
// }

MaxHeap::~MaxHeap()
{
    delete [] heap;
}

void MaxHeap::swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void MaxHeap::max_heapify_up(int i)
{
    int p = parent(i);

    // i is root: done
    if (i == 0)
    {
        return;
    }

    if (heap[p] < heap[i])
    {
        swap(heap[p], heap[i]);
        max_heapify_up(p);
    }
}

void MaxHeap::max_heapify_down(int i)
{
    int l = left(i);
    int r = right(i);
    int largest = i;

    // Check if node is leaf?? Already check when l < size - 1

    if (l < (size - 1) && heap[l] > heap[largest])
    {
        largest = l;
    }

    if (r < (size - 1) && heap[r] > heap[largest])
    {
        largest = r;
    }

    if (largest != i)
    {
        swap(heap[largest], heap[i]);
        max_heapify_down(i);
    }
}

void MaxHeap::insert(int x)
{
    int i = size;
    if (size < HEAP_SIZE_MAX)
    {
        // insert at last of heap
        heap[i] = x;
        size++;
        max_heapify_up(i);
    }
    else
    {
        cout << "Exceed max size of heap" << endl;
    }
}

void MaxHeap::removeMax()
{
    if (size > 0)
    {
        swap(heap[0], heap[size - 1]);
        size--;
        max_heapify_down(0);
    }
    else
    {
        cout << "No element in heap" << endl;
    }
}

int MaxHeap::max()
{
    return heap[0];
}