#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>

struct aj_node
{
    int vertex;
    int weight;
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

struct graph * create_graph(int vertices)
{
	struct graph *g = NULL;

	g = calloc(1, sizeof(struct aj_node));
	g->V = vertices;
	g->array = calloc(vertices, sizeof(struct aj_list));

	return g;
}

struct aj_node * create_node(int dest, int weight)
{
	struct aj_node *temp = NULL;

	temp = calloc(1, sizeof(struct aj_node));
	temp->weight = weight;
	temp->vertex = dest;

	return temp;
}

void add_edge(struct graph *g, int src, int dest, int weight)
{
	struct aj_node * new_dest = NULL;

	new_dest = create_node(dest, weight);
	new_dest->next = g->array[src]->next;
	g->array[src].head = new_dest;

	return;
}




int main()
{
    int V = 7;
    struct graph *g = NULL;

    g = create_graph(V);
    if(g == NULL)
    {
        return -1;
    }

    add_edge(g, 0 ,1);
	add_edge(g, 0 ,6);
    add_edge(g, 1, 4);
    add_edge(g, 1, 3);
    add_edge(g, 1, 2);
    add_edge(g, 1, 0);
    add_edge(g, 2, 3);
    add_edge(g, 2, 4);
    add_edge(g, 2, 5);
    add_edge(g, 3, 4);
    add_edge(g, 4, 0);
    add_edge(g, 5, 4);
    add_edge(g, 6 ,1);
    add_edge(g, 6 ,2);
    add_edge(g, 6 ,5);
   
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