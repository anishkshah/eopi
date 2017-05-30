#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <error.h>
#include <limits.h>

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

	if(!new_dest)
	{
		perror("Failed to add_edge\n");
	}

	new_dest->next = g->array[src].head;
	g->array[src].head = new_dest;

	return;
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
			printf(" ---- (%d) ----> %d", vertex_node->weight, vertex_node->vertex);
			vertex_node = vertex_node->next;
		}
		printf("\n");
	}
	return;
}

void dump_dijkstra(struct graph *g, int *dist_to, int *edge_to)
{
	int i = 0;

	printf("dist_to    edge_to\n");
	for (i = 0; i < g->V; ++i)
	{
		printf("  %d   %d\n", dist_to[i], edge_to[i]);	
	}
	return;
}

void dijkstra_util(struct graph *g, int src, int *dist_to, int *edge_to)
{
	struct aj_node *vertex_node = NULL;
	dist_to[src] = 0;
	int completed = 0;
	struct aj_node *closest = NULL;

	while(completed != g->V)
	{
		vertex_node = g->array[src].head;

		closest = get_closed(vertex_node);

		dist_to[];
		vertex_node = closest->vertex;

		completed++;
	}
    

}

void dijkstra(struct graph *g, int src)
{
	int V = 0;
	int *dist_to = NULL;
	int *edge_to = NULL;
	int i = 0;

	if(g == NULL) return NULL;

	V = g->V;

	dist_to = calloc(V, sizeof(int));
	edge_to = calloc(V, sizeof(int));

	for(i= 0; i < V; ++i)
	{
		dist_to[i] = INT_MAX;
	}

	dijkstra_util(g, src, dist_to, edge_to);
	dump_dijkstra(dist_to, edge_to);
}


int main()
{
    int V = 10;
    struct graph *g = NULL;

    g = create_graph(V);
    if(g == NULL)
    {
        return -1;
    }

    add_edge(g, 0 ,1, 5);
	add_edge(g, 0 ,4, 9);
    add_edge(g, 0, 7, 8);
    add_edge(g, 1, 2, 12);
    add_edge(g, 1, 3, 15);
    add_edge(g, 1, 7, 4);
    add_edge(g, 2, 3, 3);
    add_edge(g, 2, 6, 11);
    add_edge(g, 3, 6, 9);
    add_edge(g, 4, 5, 4);
    add_edge(g, 4, 6, 20);
    add_edge(g, 4, 7, 5);
    add_edge(g, 5, 2, 1);
    add_edge(g, 5, 6, 13);
    add_edge(g, 7, 5, 6);
    add_edge(g, 7, 2, 7);

    print_graph(g, V);

    return 0;
}