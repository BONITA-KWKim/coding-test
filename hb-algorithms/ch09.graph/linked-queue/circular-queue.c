#include "circular-queue.h"

void CQ_create_queue(CircularQueue **q, int capacity) {
    (*q) = (CircularQueue *)malloc(sizeof(CircularQueue));

    (*q)->capacity = capacity;
    (*q)->front = 0;
    (*q)->rear = 0;
    (*q)->nodes = (Node *)malloc(sizeof(Node) * (capacity + 1));
}

void CQ_destroy_queue(CircularQueue * q) {
    free(q->nodes);
    free(q);
}

void CQ_enqueue(CircularQueue *q, ElementType data) {
    if(q->rear == q->capacity+1) {
        q->rear = 0;
    }

    q->nodes[q->rear++].data = data;
}

ElementType CQ_dequeue(CircularQueue *q) {
    if(q->front == q->capacity + 1) {
        q->front = 0;
    }
    return q->nodes[q->front++].data;
}

int CQ_get_size(CircularQueue *q) {
    if(q->front <= q->rear) {
        return q->rear - q->front;
    } else {
        return q->rear + (q->capacity - q->front) + 1;
    }
}

int CQ_is_empty(CircularQueue *q) {
    return q->front == q->rear;
}

int CQ_is_full(CircularQueue *q) {
    if(q->front < q->rear)
        return (q->rear - q->front) == q->capacity;
    else
        return (q->rear + 1) == q->front;
}
