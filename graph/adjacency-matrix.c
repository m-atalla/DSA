#include <stdio.h>
#include <stdlib.h>

#define V 5


void display(int G[][V]) {
    for (int i = 0; i < V; i++)
    {
        printf("V[%d] -> ", i);
        for (int j = 0; j < V; j++)
        {
            printf("%d", G[i][j]);
        }

        printf("\n");
    }
    
}

/**
 * add undirected unweighted edge
 * 
 */
void add_edge(int G[][V], int src, int dest) {
    G[src][dest] = 1;

    G[dest][src] = 1;
}

int main(int argc, char const *argv[])
{
    int G[][V] = {
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0}        
    };

    add_edge(G, 0, 1); 
    add_edge(G, 0, 4); 
    add_edge(G, 1, 2); 
    add_edge(G, 1, 3); 

    display(G);

    return 0;
}
