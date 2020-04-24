#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

typedef int PriorityType;

typedef struct tagPQNode {
    PriorityType priority;
    void *data;
} PQNode;

typedef struct tagPriorityQueue {
    PQNode *Nodes;
    int capacity;
    int used_size;
} PriorityQueue;

PriorityQueue *PQ_create(int);
void PQ_destory(PriorityQueue *);
void PQ_enqueue(PriorityQueue *, PQNode);
void PQ_dequeue(PriorityQueue *, PQNode *);
int PQ_get_parent(int);
int PQ_get_left_child(int);
void PQ_swap_node(PriorityQueue *, int, int);
int PQ_is_empty(PriorityQueue *);

#endif //__PRIORITY_QUEUE_H__
