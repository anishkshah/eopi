#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Uni directed graph goes from Node to Node in single direction A---->B
// Bi directed graph goes from Node to Node in both directions   A<--->B
/*
      0---------1
	 / \		 \
	5	2---------6
	 \ /		 /
	  3---------4
*/

#define N 7
				    	  //0  1  2  3  4  5  6
int graph_bidir[N][N] = { { 0, 1, 1, 0, 0, 1, 0 }, //0
						  { 1, 0, 0, 0, 0, 0, 1 }, //1
						  { 1, 0, 0, 1, 0, 0, 1 }, //2
						  { 0, 0, 1, 0, 1, 1, 0 }, //3
						  { 0, 0, 0, 1, 0, 0, 1 }, //4
						  { 1, 0, 0, 1, 0, 0, 0 }, //5
						  { 0, 1, 0, 0, 1, 0, 0 }, //6
						};

int q[N+N];
int tail = 0;
int head = 0;

void BFS(int graph[N][N], int V, int *visited)
{
	int traveler = 0;
	int i =0;
	
	memset(q, 0, sizeof(q));

	visited[V] = 1;
	q[tail] = V;
	tail++;
	
	printf("BFS for %d : ", V);
	
	while(tail != head)
	{
		traveler = q[head];
		head++;

		printf("%d --", traveler);

		for(i = 0; i < N; i++)
		{
			if(visited[i] != 1 && graph[traveler][i])
			{
				q[tail] = i;
				tail++;
				visited[i] = 1;
			}
		}
	}
	printf("\n");
}

void DFS_util(int graph[N][N], int V, int *visited, int V_count)
{
	int vertices = 0;
	visited[V] = 1;
	printf("%d -- ", V);
	for(vertices = 0; vertices < V_count; vertices++)
	{
		if(visited[vertices] != 1 && graph[V][vertices])
		{
			DFS_util(graph, vertices, visited, V_count);
		}
	}
}

void DFS(int graph[N][N], int V, int V_count)
{
	int vertices = 0;
	int *visited = calloc(V_count, sizeof(visited));
	printf("DFS for vertice %d: ", V);
	
	DFS_util(graph, V, visited, V_count);
	printf("\n");
}


int main(int argc, char const *argv[])
{
	int visited[N];

	memset(visited, 0, sizeof(visited));
	BFS(graph_bidir, 0, visited);

	memset(visited, 0, sizeof(visited));
	BFS(graph_bidir, 5, visited);

	memset(visited, 0, sizeof(visited));
	BFS(graph_bidir, 3, visited);

	DFS(graph_bidir, 0, N);

	DFS(graph_bidir, 5, N);

	DFS(graph_bidir, 3, N);

	return 0;
}