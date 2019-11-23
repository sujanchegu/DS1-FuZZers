#include <stdio.h>
#include <limits.h>
#include<stdlib.h>

int N;
int e;
int matrix[100][100];
int source;
int visited[100];

void createGraph()
{	
    printf("Enter number of Vertices: ");
    scanf("%d", &N);
    printf("Enter number of edges: ");
    scanf("%d",&e);
    while(e>(N*(N-1))) {
	printf("\ninvalid please enter again : ");
	scanf("%d",&e);
    }
	
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            matrix[i][j] = INT_MAX;
        }
    }
    int i, j, w;
    while (1)
    {
        printf("Enter source, destination, weight:");
        scanf("%d %d %d", &i, &j, &w);
        if ((i == -1) && (j == -1))
            break;
        matrix[i][j] = w;
    }
}

int pop(int *dist)
{
    int min = INT_MAX, k;
    for (int i = 1; i <= N; i++)
        if (visited[i] == 0 && dist[i] < min)
        {
            visited[i] = 1;
            min = dist[i];
            k = i;
        }
    return k;
}


void display_shortest(int *dist) {
	for (int i = 1; i <= N; i++)
	    {
		if (dist[i] != INT_MAX)
		    printf("%d - %d\n", i, dist[i]);
		else
		    printf("%d - NotAccesible\n", i);
	    }
}

void print_path(int *parent,int d) {
	if(d<=0)
		return;
	print_path(parent,parent[d]);
	printf("%d->",d);
}

void bellman() {
	int dist[N+1];
	int parent[N+1];
	for(int i=1;i<=N;i++){
		dist[i]=INT_MAX;
		parent[i]=-1;
		}
	dist[source]=0;
	for(int i=1;i<=N-1;i++) {
		for( int j=1;j<=e;j++) {
			if(matrix[i][j]!=INT_MAX) {
				if((dist[i]!=INT_MAX) && (dist[i]+matrix[i][j]<dist[j])) {
					dist[j]=dist[i]+matrix[i][j];
					parent[j]=i;
					}
			}
		}
	}
	display_shortest(dist);
	while(1) {
	    int d;
	    printf("\n enter destination vertex [enter -1 to stop].. : ");
	    scanf("%d",&d);
	    while(d>N) {
		  printf("\ninvalid please enter again : ");
		  scanf("%d",&d);
   	    }
	    if(d<0) break;
	    print_path(parent,d);
	}
}

void dijkstra()
{
    int parent[N+1];
    int dist[N+1];
    for (int i = 1; i <= N; i++)
        dist[i] = INT_MAX;
    dist[source] = 0;
    for (int i = 1; i <= N; i++)
    {
        int u = pop(dist);
        for (int v = 1; v <= N; v++)
            if (visited[v] == 0 && matrix[u][v] != INT_MAX)
                if (dist[u] + matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + matrix[u][v];
                    parent[v]=u;
                    }
    }
    display_shortest(dist);
    while(1) {
	    int d;
	    printf("\n enter destination vertex [enter -1 to stop].. : ");
	    scanf("%d",&d);
	    while(d>N) {
		  printf("\ninvalid please enter again : ");
		  scanf("%d",&d);
   	    }
	    if(d<0) break;
	    print_path(parent,d);
	}
}

int main() {
	printf("\t\t\t SHORTEST PATH FINDER \t\t -BY the FuZZers");
	printf("\n");
	createGraph();
	printf("\n created graph..");
	while(1) {
		printf("\n ALGORITHM SELECTION: \n 1.DIJKSTRA \n 2.BELLMAN_FORD \n 3.exit");
		printf("\n enter your choice : ");
		int ch;
		scanf("%d",&ch);
		switch(ch) {
			case 1:
				printf("\nenter source vertex for traversal.. ");
				scanf("%d",&source); 
				dijkstra();
				break;
			case 2:
				printf("\nenter source vertex for traversal.. ");
				scanf("%d",&source); 
				bellman();
				break;
			default:
				exit(1);
				break;
		}
	}
}
