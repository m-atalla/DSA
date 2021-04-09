#include <stdio.h>
#include <stdlib.h>

// Adjacent list nodes struct
typedef struct node
{
    int vertex;
    struct node *next;
} vertex_t;

typedef struct 
{
    vertex_t *head;
} adjlist_t;

// Graph struct (adjacency list)
typedef struct
{
    int vertexes_number;
    adjlist_t *list;
} graph_t;

/**
 * Initialize an empty graph
 * @param VN vertexes_number
 * @return graph_t * pointer to a graph_t struct
 */
graph_t *create_graph(int VN)
{
    graph_t *graph = (graph_t *)malloc(sizeof(graph_t));

    graph->vertexes_number = VN;

    // Allocates a list equal to the size of a single vertex
    // times the total of vertexes in the graph.
    graph->list = malloc(VN * sizeof(vertex_t));

    // Initializes an empty list
    for (int i = 0; i < VN; i++)
    {
        graph->list[i].head = NULL;
    }

    return graph;
}

/**
 * prints contents of a graph
 * 
 */
void print_graph(graph_t *graph)
{
    for (int i = 0; i < graph->vertexes_number; i++)
    {
        printf("adjacents of vertex[%d]: ", i);

        // vertexes with no edges.
        if (graph->list[i].head == NULL)
        {
            printf("NULL");
        }
        
        // temp traversal pointer
        vertex_t *current = graph->list[i].head;

        while (current != NULL)
        {
            printf(" -> %d", current->vertex);

            current = current->next;
        }

        printf("\n");
    }
}

vertex_t * create_vertex(int dest) {
    vertex_t *new_vertex = (vertex_t *)malloc(sizeof(vertex_t));
    new_vertex->vertex = dest;
    new_vertex->next = NULL;

    return new_vertex;
}
/**
 * Creates following edges in an undirected graph
 * src => dest, dest => src
 */
void add_edge(graph_t * graph, int src, int dest) {
    vertex_t *new_vertex = create_vertex(dest);

    // Create an edge from src to dest
    // while perserving existing list
    new_vertex->next = graph->list[src].head;
    graph->list[src].head = new_vertex;

    // Undirected graph. Therefore,
    // the same operation needs to be preformed in the inverse.
    // from dest to src
    new_vertex = create_vertex(src); // resuse new_vertex declaration with a new value
    new_vertex->next = graph->list[dest].head;
    graph->list[dest].head = new_vertex;
}

int main(int argc, char const *argv[])
{
    graph_t *graph = create_graph(5);

    add_edge(graph, 0, 1); 
    add_edge(graph, 0, 4); 
    add_edge(graph, 1, 2); 
    add_edge(graph, 1, 3); 
    add_edge(graph, 1, 4); 
    add_edge(graph, 2, 3); 
    add_edge(graph, 3, 4); 

    print_graph(graph);
    return 0;
}
