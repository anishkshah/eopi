#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "helper.c"

struct aj_node
{
    int vertex;
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

struct aj_node * new_fifo_node(int vertex)
{
    struct aj_node *new_fifo = NULL;
    new_fifo = malloc(sizeof(struct aj_node));
    if(new_fifo) {
        new_fifo->vertex = vertex;
        new_fifo->next = NULL;
    }
    return new_fifo;
}

struct graph* create_graph(int V)
{
    struct graph *graph = NULL;

    graph = malloc(sizeof(struct graph));

    graph->V = V;
    graph->array = calloc(V, sizeof(struct aj_list));

    return graph;
}

/* add edge to the directed graph */

void add_edge(struct graph *g, int src, int des)
{
    struct aj_node *new_fifo_node_vertex = new_fifo_node(des);

    new_fifo_node_vertex->next = g->array[src].head;
    g->array[src].head = new_fifo_node_vertex;

}

void dfs_util(struct graph *g, int vertex, int *visited)
{
    struct aj_node *node= NULL;
    int new_fifo_V = 0;

    // Visiting the Node at - vertex
    
    if(!visited[vertex])
    {
    	visited[vertex] = 1;
		printf("%d -- ", vertex);
	}

    node = g->array[vertex].head;
        
    while(node != NULL)
    {
        new_fifo_V = node->vertex;
        if(visited[new_fifo_V] != 1)
        {
            dfs_util(g, new_fifo_V, visited);
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


void topoloical_sort_util(struct graph *g, int vertex, int *visited, struct stack_node **stack)
{
    struct aj_node *node= NULL;
    int new_fifo_V = 0;

    // Visiting the Node at - vertex

    visited[vertex] = 1;
    node = g->array[vertex].head;
        
    while(node != NULL)
    {
        new_fifo_V = node->vertex;
        if(visited[new_fifo_V] != 1)
        {
            topoloical_sort_util(g, new_fifo_V, visited, stack);
        }
        node = node->next;
    }

    printf("%d -- ", vertex);
    push_stack(stack, vertex);
    return;
}

/* traversal of all the vertices reachable form V */
void topoloical_sort(struct graph *g)
{
    int i = 0;
    struct stack_node *stack = NULL;
    int *visited = calloc(g->V, sizeof(int));

    printf("topoloical_sort : ");
    for (i = 0; i < g->V; ++i)
    {
    	if(visited[i] == 0)
    	{
    		topoloical_sort_util(g, i, visited, &stack);
    	}
    }
    //printf("topoloical_sort_util: ");
    printf("\n");
    stack_print(&stack);
}


int is_cyclic_util(struct graph *g, int vertex, int *visited, int *rec_stack)
{
    struct aj_node *node= NULL;
    int new_fifo_V = 0;

    // Visiting the Node at - vertex
    if(!visited[vertex])
    {
        visited[vertex] = 1;
        rec_stack[vertex] = 1;
    
        node = g->array[vertex].head;
            
        while(node != NULL)
        {
            new_fifo_V = node->vertex;
            if(visited[new_fifo_V] != 1 && rec_stack[new_fifo_V] != 1)
            {
                return is_cyclic_util(g, new_fifo_V, visited, rec_stack);
            }
            else if(rec_stack[new_fifo_V] == 1)
            {
                return 1;
            }
            node = node->next;
        }
    }
    rec_stack[new_fifo_V] = 0;
    return 0;
}

/* traversal of all the vertices reachable form V */
void is_cycylic(struct graph *g, int vertex)
{
    int i = 0;
    int is_cycylic = 0;
    int *visited = calloc(g->V, sizeof(int));
    int *rec_stack = calloc(g->V, sizeof(int));

    is_cycylic = is_cyclic_util(g, vertex, visited, rec_stack);
    printf("vertex %d is is_cycylic %d\n", vertex, is_cycylic);
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

void bfs(struct graph *g, int V)
{
    struct fifo *queue = fifo_init();
    struct aj_node *vertex_node = NULL;
    int vertex = 0;
    int *visited = calloc(V, sizeof(int));

    put_fif0(queue, V);
    printf("BFS : ");
    while(!queue_empty(queue))
    {
        vertex =  get_fif0(queue);

        printf("%d -- ", vertex);
        visited[vertex] = 1;

        vertex_node = g->array[vertex].head;

        while(vertex_node !=NULL)
        {
            if(visited[vertex_node->vertex] != 1)
            {
                put_fif0(queue, vertex_node->vertex);
                visited[vertex_node->vertex] = 1;
            }
            vertex_node = vertex_node->next;
        }

    }
    printf("\n");
}



void print_graph(struct graph *g, int max_vertex)
{
	struct aj_node *vertex_node = NULL;
	int  i = 0;

	for (i = 0; i < max_vertex; ++i)
	{
		printf("%d", i);
		vertex_node = g->array[i].head;

		while(vertex_node)
		{
			printf(" --> %d", vertex_node->vertex);
			vertex_node = vertex_node->next;
		}
		printf("\n");
	}
	return;
}

int main()
{
    int V = 7;
    struct graph *g = NULL;

    g = create_graph(V);
    if(g == NULL) {
        return -1;
    }

    add_edge(g, 0 ,1);
	add_edge(g, 0 ,2);
    add_edge(g, 1, 4);
    add_edge(g, 1, 3);
    add_edge(g, 1, 2);
    add_edge(g, 1, 0);
    add_edge(g, 3, 2);
    add_edge(g, 2, 4);
    add_edge(g, 2, 5);
    add_edge(g, 3, 4);
    add_edge(g, 4, 0);
    add_edge(g, 5, 4);
    add_edge(g, 6 ,1);
    add_edge(g, 6 ,2);
    add_edge(g, 6 ,5);
   
    for (int i = 0; i < V; ++i)
    {
        is_cycylic(g, i);
    }


    dfs(g, 0);
    dfs(g, 1);
    dfs(g, 2);
    dfs(g, 3);
    dfs(g, 4);
    dfs(g, 5);

    print_graph(g, V);
    bfs(g, 0);
    topoloical_sort(g);
    return 0;
}
