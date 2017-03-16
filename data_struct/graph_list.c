#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct aj_node
{
    int des;
    struct aj_node *next;
};

struct aj_list
{
    struct aj_node *head;
};

struct graph
{
    int V;
    struct aj_list *array;
};

/* Unidirected GRAPH with Adjacency list.

    0---1\
    |  /| \
    | / |  2
    |/  | /
    4---3/

    0[]-->1-->4
    1[]-->1-->4-->2-->3
    2[]-->1-->3
    3[]-->1-->4-->2
    4[]-->3-->0-->1

    V - Vertices's
    E - Edges 
*/

struct aj_node * new_node(int dest)
{
    struct aj_node *new = NULL;
    new = malloc(sizeof(struct aj_node));
    if(new) {
        new->des = dest;
        new->next = NULL;
    }
    return new;
}

struct graph* create_graph(int V)
{
    struct graph *graph = NULL;

    graph = malloc(sizeof(struct graph));

    graph->V = V;
    graph->array = calloc(V, sizeof(struct aj_list));

    return graph;
}

/* add edge to the uni-directed graph */

void add_edge(struct graph *g, int src, int des)
{
    struct aj_node *new_node_des = new_node(des);
    struct aj_node *new_node_src = new_node(src);

    new_node_des->next = g->array[src].head;
    g->array[src].head = new_node_des;

    //for uni directed graph
    new_node_src->next = g->array[des].head;
    g->array[des].head = new_node_src;  
}

void dfs_util(struct graph *g, int vertex, int *visited)
{
    struct aj_node *node= NULL;
    int new_V = 0;

    // Visiting the Node at - vertex
    
    visited[vertex] = 1;

    printf("%d -- ", vertex);

    node = g->array[vertex].head;
        
    while(node != NULL)
    {
        new_V = node->des;
        if(visited[new_V] != 1)
        {
            dfs_util(g, new_V, visited);
        }
        node = node->next;
    }
}

/* traversal of all the vertices reachable form V */
void dfs(struct graph *g, int vertex)
{
    int i = 0;
    int *visited = calloc(g->V, sizeof(int));

    printf("DFS : ");
    dfs_util(g, vertex, visited);
    printf("\n");
}


/* Breath First Search - computes the shortest path(fewest no of edges)
 *
 *
 *  0-------2-----4        1    4
 *  |\     /|    /        / | / |
 *  | \   / |   /        /  |/  |
 *  |  \ /  |  /       0 ---2   |
 *  |   1   | /          \   \  |
 *  5-------3             \   \ |
 *                          5---3
 *                  d = 0   1   2  
 */

/*
void bfs(int V)
{
    list queue;
    boolean *visited = calloc(V, sizeof(boolean));

    visited[V] = true;
    queue.push(V);
}
*/

int main()
{
    int V = 7;
    struct graph *g = NULL;

    g = create_graph(V);
    if(g == NULL) {
        return -1;
    }

    add_edge(g, 1, 4);
    add_edge(g, 1, 3);
    add_edge(g, 1, 2);
    add_edge(g, 1, 0);
    add_edge(g, 2, 3);
    add_edge(g, 4, 0);
    add_edge(g, 3, 4);
    add_edge(g, 0 ,1);

    add_edge(g, 6 ,5);
   
    dfs(g, 0);
    dfs(g, 1);
    dfs(g, 2);
    dfs(g, 3);
    dfs(g, 4);
    dfs(g, 5);
    return 0;
}
