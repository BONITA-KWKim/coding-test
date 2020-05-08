#include "circular-queue.h"

int main(void) {
    int i = 0;
    CircularQueue *q;

    CQ_create_queue(&q, 10);

    CQ_enqueue(q, 1);
    CQ_enqueue(q, 2);
    CQ_enqueue(q, 3);
    CQ_enqueue(q, 4);
    CQ_enqueue(q, 5);

    for(i = 0; 3 > i; ++i) {
        printf("Dequeue: %d, ", CQ_dequeue(q));
        printf("Front: %d, Rear: %d\n", q->front, q->rear);
    }

    i = 100;
    while(0 == CQ_is_full(q)) {
        CQ_enqueue(q, i++);
    }

    while(0 == CQ_is_empty(q)) {
        printf("Dequeue: %d, ", CQ_dequeue(q));
        printf("Front: %d, Rear: %d\n", q->front, q->rear);
    }

    CQ_dequeue(q);

    return 0;
}