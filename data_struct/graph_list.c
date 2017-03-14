#include <stdio.h>
#include <string.h>

struct aj_node
{
    int des;
    struct aj_node *next;
}

struct aj_list
{
    struct aj_node *head;
}

struct graph
{
    int V;
    struct aj_list *array;
}

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

struct aj_node * new_node(int value)
{
    struct aj_node *new = NULL;
    new = malloc(sizeof(struct aj_node));
    if(new) {
        new->value = value;
        new->next = NULL;
    }
    return new;
}

struct graph* create_graph(int V)
{
    struct graph *graph = NULL;
    int vertices = 0;
    struct aj_node vertex_node= NULL;

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

    new_node_des->next = graph->array[src].head;
    graph->array[src].head = new_node_des;

    //for uni directed graph
    new_node_src->next = graph->array[des].head;
    graph->array[des].head = new_node_src;  
}

void dfs_util(struct graph *g, int V, boolean *visited)
{
    struct aj_node = NULL;
    int new_V = 0;

    // Visiting the Node V
    
    visited[V] = TRUE;
    aj_node = g->array[V];
        
    while(aj_node != NULL)
    {
        new_V = aj_node->des;
        if(visited[new_V] != TRUE)
        {
            dfs_util(g, new_V, visited);
        }
        aj_node = aj_node->next;
    }
}

/* traversal of all the vertices reachable form V */
void dfs(int V)
{
    int i = 0;
    boolean *visited = calloc(V, sizeof(boolean));

    for(i = 0; i < V; i++)
    {
        if(visited[i] == FALSE)
        {
            DFS_util(i, visited);
        }
    }
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


void bfs(int V)
{
    list queue;
    boolean *visited = calloc(V, sizeof(boolean));

    visited[V] = true;
    queue.push(V);
}

int main()
{
    struct graph G = NULL;

    G = create_graph(6);
    if(G == NULL) {
        return -1;
    }



}
