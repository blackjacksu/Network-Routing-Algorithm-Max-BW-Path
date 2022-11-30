#include "datastruct.h"

MaxHeap::MaxHeap()
{
    size = 0;
    heap = new struct node[HEAP_SIZE_MAX];
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

void MaxHeap::swap(struct node &a, struct node &b)
{
    struct node temp = a;
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

    if (heap[p].bw < heap[i].bw)
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

    if (l < (size - 1) && heap[l].bw > heap[largest].bw)
    {
        largest = l;
    }

    if (r < (size - 1) && heap[r].bw > heap[largest].bw)
    {
        largest = r;
    }

    if (largest != i)
    {
        swap(heap[largest], heap[i]);
        max_heapify_down(i);
    }
}

void MaxHeap::insertNode(int idx, int bw)
{
    int i = size;
    if (size < HEAP_SIZE_MAX)
    {
        // insert at last of heap
        heap[i].idx = idx;
        heap[i].bw = bw;
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

int MaxHeap::getMax()
{
    return heap[0].idx;
}

bool MaxHeap::isEmpty()
{
    return size == 0;
}

void MaxHeap::removeNode(int x)
{
    if (size > 0)
    {
        swap(heap[x], heap[size - 1]);
        size--;
        max_heapify_down(x);
    }
    else
    {
        cout << "No element in heap" << endl;
    }
}

//pushes element on to the stack
bool Stack::push(int x)
{
    bool ret = false;

    if (top >= (STACK_SIZE_MAX - 1)) 
    {
        cout << "Stack Overflow!";
        ret = false;
    }
    else 
    {
        stack[++top] = x;
        // cout << x << endl;
        ret = true;
    }
    return ret;
}

Stack::Stack() 
{ 
    top = -1; 
}
  
//removes or pops elements out of the stack
int Stack::pop()
{
    if (top < 0) {
        cout << "Stack Underflow!";
        return 0;
    }
    else {
        int x = stack[top--];
        return x;
    }
}
  
//check if stack is empty
bool Stack::isEmpty()
{
    return (top < 0);
}
