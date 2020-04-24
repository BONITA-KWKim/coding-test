#include "priority-queue.h"

PriorityQueue *PQ_create(int init_size) {
    PriorityQueue * new_PQ = (PriorityQueue *)malloc(sizeof(PriorityQueue));

    new_PQ -> capacity  =init_size;
    new_PQ -> used_size = 0;
    new_PQ -> Nodes = (PQNode *)malloc(sizeof(PQNode) * init_size);

    return new_PQ;
}

void PQ_destory(PriorityQueue * PQ) {
    free(PQ->Nodes);
    free(PQ);
}

void PQ_enqueue(PriorityQueue * PQ, PQNode new_node) {
    int current_pos = PQ -> used_size;
    int parent_pos = PQ_get_parent(current_pos);

    if(PQ->capacity == PQ->used_size) {
        if(0 == PQ->capacity) 
            PQ->capacity = 1;

        PQ -> capacity *= 2;
        PQ -> Nodes = (PQNode *)realloc(PQ -> Nodes, sizeof(PQNode) * PQ -> capacity);
    }

    PQ -> Nodes[current_pos] = new_node;

    /* after processing */
    while(0 < current_pos && 
        PQ -> Nodes[current_pos].priority < 
        PQ -> Nodes[parent_pos].priority) {
        PQ_swap_node(PQ, current_pos, parent_pos);

        current_pos = parent_pos;
        parent_pos = PQ_get_parent(current_pos);
    }

    ++PQ->used_size;
}

void PQ_dequeue(PriorityQueue *PQ, PQNode *root) {
    int parent_pos= 0;
    int left_pos  = 0;
    int right_pos = 0;

    memcpy(root, &PQ->Nodes[0], sizeof(PQNode));
    memcpy(&PQ->Nodes[0], 0, sizeof(PQNode));

    --PQ->used_size;
    PQ_swap_node(PQ, 0, PQ -> used_size);

    left_pos = PQ_get_left_child(0);
    right_pos = left_pos + 1;

    while(1) {
        int selected_child = 0;

        if(PQ->used_size <= left_pos) 
            break;

        if(PQ->used_size <= right_pos) {
            selected_child = left_pos;
        } else {
            if(PQ->Nodes[left_pos].priority > PQ->Nodes[right_pos].priority) {
                selected_child = right_pos;
            } else {
                selected_child = left_pos;
            }
        }

        if(PQ->Nodes[selected_child].priority > PQ->Nodes[parent_pos].priority) {
            PQ_swap_node(PQ, parent_pos, selected_child);
            parent_pos = selected_child;
        } else {
            break;
        }

        left_pos = PQ_get_left_child(parent_pos);
        right_pos = left_pos + 1;
    }

    if(PQ->used_size < (PQ->capacity/2)) {
        PQ->capacity /= 2;
        PQ->Nodes = (PQNode *)realloc(PQ->Nodes, sizeof(PQNode) * PQ->capacity);
    }
}

void PQ_swap_node(PriorityQueue * PQ, int idx1, int idx2) {
    int copy_size = sizeof(PQNode);
    PQNode *tmp = (PQNode *)malloc(copy_size);

    memcpy(tmp,              &PQ->Nodes[idx1], copy_size);
    memcpy(&PQ->Nodes[idx1], &PQ->Nodes[idx2], copy_size);
    memcpy(&PQ->Nodes[idx2], tmp,              copy_size);

    free(tmp);
}

int PQ_get_parent(int idx) {
    return (int)((idx - 1) / 2);
}

int PQ_get_left_child(int idx) {
    return (2 * idx) + 1;
}

int PQ_is_empty(PriorityQueue *PQ) {
    return (PQ->used_size == 0);
}
