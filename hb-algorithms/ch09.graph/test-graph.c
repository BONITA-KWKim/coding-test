#include "graph.h"

int main(void) {
    /* Create graph */
    Graph *graph = create_graph();

    /* Create vertices */
    Vertex *v1 = create_vertex('1');
    Vertex *v2 = create_vertex('2');
    Vertex *v3 = create_vertex('3');
    Vertex *v4 = create_vertex('4');
    Vertex *v5 = create_vertex('5');

    /* Add vertices on graph */
    add_vertex(graph, v1);
    add_vertex(graph, v2);
    add_vertex(graph, v3);
    add_vertex(graph, v4);
    add_vertex(graph, v5);

    /* draw edges */
    add_edge(v1, create_edge(v1, v2, 0));
    add_edge(v1, create_edge(v1, v3, 0));
    add_edge(v1, create_edge(v1, v4, 0));
    add_edge(v1, create_edge(v1, v5, 0));

    add_edge(v2, create_edge(v2, v1, 0));
    add_edge(v2, create_edge(v2, v3, 0));
    add_edge(v2, create_edge(v2, v5, 0));

    add_edge(v3, create_edge(v3, v1, 0));
    add_edge(v3, create_edge(v3, v2, 0));

    add_edge(v4, create_edge(v4, v1, 0));
    add_edge(v4, create_edge(v4, v5, 0));
    
    add_edge(v5, create_edge(v5, v1, 0));
    add_edge(v5, create_edge(v5, v2, 0));
    add_edge(v5, create_edge(v5, v4, 0));

    /* print graph */
    print_graph(graph);

    /* destroy graph */
    destroy_graph(graph);

    return 0;
}