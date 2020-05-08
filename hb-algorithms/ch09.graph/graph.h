#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include <stdlib.h>

enum VISIT_MODE {Visited, NotVisited};

typedef int ElementType;
typedef struct tagVertex {
    ElementType data;
    int visited;
    int index;

    struct tagVertex *next;
    struct tagEdge *adjacent_list;
} Vertex;

typedef struct tagEdge {
    int weight;
    Vertex *from;
    Vertex *target;

    struct tagEdge *next;
} Edge;

typedef struct tagGraph {
    Vertex *vertices;
    int vertex_count;
} Graph;

Graph *create_graph(void);
void destroy_graph(Graph *);

Vertex *create_vertex(ElementType);
void destroy_vertex(Vertex *);

Edge *create_edge(Vertex *, Vertex *, int);
void destroy_edge(Edge *);

void add_vertex(Graph *, Vertex *);
void add_edge(Vertex *, Edge *);
void print_graph(Graph *);

#endif //__GRAPH_H__