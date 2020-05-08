#include "graph.h"

Graph *create_graph(void) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));

    graph->vertices = NULL;
    graph->vertex_count = 0;

    return graph;
}

void destroy_graph(Graph *graph) {
    while(NULL != graph->vertices) {
        Vertex *vertices = graph->vertices->next;
        destroy_vertex(graph->vertices);
        graph->vertices = vertices;
    }

    free(graph);
}

Vertex *create_vertex(ElementType data) {
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));

    vertex->data = data;
    vertex->next = NULL;
    vertex->adjacent_list = NULL;
    vertex->visited = NotVisited;
    vertex->index = -1;

    return vertex;
}

void destroy_vertex(Vertex *vertex){
    while(NULL != vertex->adjacent_list) {
        Edge *edge = vertex->adjacent_list->next;
        destroy_edge(vertex->adjacent_list);
        vertex->adjacent_list = edge;
    }

    free(vertex);
}

Edge *create_edge(Vertex *from, Vertex *to, int weight) {
    Edge *edge = (Edge *)malloc(sizeof(Edge));

    edge->from = from;
    edge->target = to;
    edge->next = NULL;
    edge->weight = weight;

    return edge;
}

void destroy_edge(Edge *edge) {
    free(edge);
}

void add_vertex(Graph *graph, Vertex *vertex) {
    Vertex *vertex_list = graph->vertices;

    if(NULL == vertex_list) {
        graph->vertices = vertex;
    } else {
        while(NULL != vertex_list->next) {
            vertex_list = vertex_list->next;
        }

        vertex_list->next = vertex;
    }

    vertex->index = graph->vertex_count++;
}

void add_edge(Vertex *vertex, Edge *edge) {
    if(NULL == vertex->adjacent_list) {
        vertex->adjacent_list = edge;
    } else {
        Edge *adjacent_list = vertex->adjacent_list;

        while(NULL != adjacent_list->next) {
            adjacent_list = adjacent_list->next;
        }

        adjacent_list->next = edge;
    }
}

void print_graph(Graph *graph) {
    Vertex * vertex = NULL;
    Edge *edge = NULL;

    if(NULL == (vertex = graph->vertices)) {
        return;
    }

    while(NULL != vertex) {
        printf("%c: ", vertex->data);

        if(NULL == (edge = vertex->adjacent_list)) {
            vertex = vertex->next;
            printf("\n");
            continue;
        }

        while(NULL != edge) {
            printf("%c[%d] ", edge->target->data, edge->weight);
            edge = edge->next;
        }

        printf("\n");

        vertex = vertex->next;
    }

    printf("\n");
}
