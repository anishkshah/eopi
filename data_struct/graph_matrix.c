#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Uni directed graph goes from Node to Node in single direction A---->B
// Bi directed graph goes from Node to Node in both directions   A<--->B
/*
      0---------1
     / \         \
    5   2---------6
     \ /         /
      3---------4
*/

#define N 9
#define D 8
                        // 0  1  2  3  4  5  6  7  8
int graph_bidir[N][N] = {
                          {0, 4, 0, 0, 0, 0, 0, 8, 0},
                          {4, 0, 8, 0, 0, 0, 0,11, 0},
                          {0, 8, 0, 7, 0, 4, 0, 0, 2},
                          {0, 0, 7, 0, 9,14, 0, 0, 0},
                          {0, 0, 0, 9, 0,10, 0, 0, 0},
                          {0, 0, 4,14,10, 0, 2, 0, 0},
                          {0, 0, 0, 0, 0, 2, 0, 1, 6},
                          {8,19, 0, 0, 0, 0, 1, 0, 7},
                          {0, 0, 2, 0, 0, 0, 6, 7, 0}
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


/*
        1---------------  15  ----------3
      / |                             / |
     /  |                           /   |
    5   |                         /     |
   /    |                       /       |
  0     7 ------ 7 -----------2         |
  | \   | \                 /   \       |
  |  8  |   \             /      \      |
  |   \ |     6         1         \     |
  |     7       \     /            11   |
  |   /            \ /              \   |
  |  5              5                \  |
  |/                                  \ |
  4----------------- 20 ----------------6



  graph       - input graph
  distance_to - the minimum distance from source vertex
  edge_to     - the closest edge to reach the source vertex.

*/


int get_min_index(int *input, int size, int *value)
{
    int i = 0;
    int min_index = 0;
    int min_value = INT_MAX;

    for (i = 0; i < size; ++i)
    {
        if(input[i] < min_value)
        {
            min_index = i;
            min_value = input[i];
        }
    }
    return min_index;
}

void Dijikstra(int graph[N][N], int *distance_to, int *edge_to, int source_v)
{ 
    memset(distance_to, 0, sizeof(int)* N);
    memset(edge_to, 0, sizeof(int)* N);

}


void display_djikstras(int *distance_to, int *edge_to)
{
    int i = 0;
    printf("Vertex :  distance_to  edge_to\n");
    for(i = 0; i < N; i++)
    {
        printf("  %d         %d          %d\n", i, distance_to[i], edge_to[i]);
    }
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


    int dist_to[N];
    int edge_to[N];

    Dijikstra(graph_bidir, dist_to, edge_to, 0);
    display_djikstras(dist_to, edge_to);

    return 0;
}
