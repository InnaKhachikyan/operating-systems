#include <stdio.h>
#include <stdlib.h>
#include "min_heap.h"

#define PARENT(i) ((int)(((i) - 1) / 2))
#define LEFT(i)   ((int)((i) * 2 + 1))
#define RIGHT(i)  ((int)((i) * 2 + 2))

static int cmp_proc_by_burst(const proc *a, const proc *b) {
    if (a->burst_time != b->burst_time) return (a->burst_time < b->burst_time) ? -1 : 1;
    if (a->arrival_time != b->arrival_time) return (a->arrival_time < b->arrival_time) ? -1 : 1;
    if (a->pid != b->pid) return (a->pid < b->pid) ? -1 : 1;
    return 0;
}

static void swap(proc **a, proc **b) {
    proc *t = *a; *a = *b; *b = t;
}

static void upheap(MinHeap *heap, int i) {
    while (i > 0) {
        int p = PARENT(i);
        if (cmp_proc_by_burst(heap->data[i], heap->data[p]) < 0) {
            swap(&heap->data[i], &heap->data[p]);
            i = p;
        } else {
            break;
        }
    }
}

static void downheap(MinHeap *heap, int i) {
    while (1) {
        int l = LEFT(i), r = RIGHT(i), smallest = i;
        if (l < heap->size && cmp_proc_by_burst(heap->data[l], heap->data[smallest]) < 0) smallest = l;
        if (r < heap->size && cmp_proc_by_burst(heap->data[r], heap->data[smallest]) < 0) smallest = r;
        if (smallest != i) {
            swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
}

MinHeap *create_heap(int capacity) {
    if (capacity < 1) capacity = 1;
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (!heap) { fprintf(stderr, "malloc failed\n"); exit(EXIT_FAILURE); }
    heap->data = (proc **)malloc((size_t)capacity * sizeof(proc *));
    if (!heap->data) { fprintf(stderr, "malloc failed\n"); exit(EXIT_FAILURE); }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void free_heap(MinHeap *heap) {
    if (!heap) return;
    free(heap->data);
    heap->data = NULL;
    free(heap);
    heap = NULL;
}

void heap_insert(MinHeap *heap, proc *p) {
    if (heap->size == heap->capacity) {
        fprintf(stderr, "insert on full heap (capacity=%d)\n", heap->capacity);
        exit(EXIT_FAILURE);
    }
    heap->data[heap->size] = p;
    upheap(heap, heap->size);
    heap->size++;
}

int is_empty(const MinHeap *heap) {
    return heap->size == 0;
}

proc *extract_min(MinHeap *heap) {
    if (is_empty(heap)) {
        fprintf(stderr, "extract on empty heap\n");
        exit(EXIT_FAILURE);
    }
    proc *root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    if (heap->size > 0) downheap(heap, 0);
    return root;
}

