#ifndef MINHEAP_H
#define MINHEAP_H

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int in_heap;
} proc;

typedef struct {
    proc **data;
    int size;
    int capacity;
} MinHeap;

MinHeap *create_heap(int capacity);
void free_heap(MinHeap *heap);
void heap_insert(MinHeap *heap, proc *p);
proc *extract_min(MinHeap *heap);
int is_empty(const MinHeap *heap);

#endif

