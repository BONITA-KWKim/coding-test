#ifndef __CIRCULAR_QUEUE_H__
#define __CIRCULAR_QUEUE_H__

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode {
    ElementType data;
} Node;

typedef struct tagCircularQueue {
    int capacity;
    int front;
    int rear;

    Node *nodes;
} CircularQueue;

void CQ_create_queue(CircularQueue **, int);
void CQ_destroy_queue(CircularQueue *);
void CQ_enqueue(CircularQueue *, ElementType);
ElementType CQ_dequeue(CircularQueue *);
int CQ_get_size(CircularQueue *);
int CQ_is_empty(CircularQueue *);
int CQ_is_full(CircularQueue *);

#endif //__CIRCULAR_QUEUE_H__