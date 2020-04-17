#include <limits.h> 
#include <stdio.h> 
#define VERTICES 9 

int minDis(int dist[], bool sptSet[]) 
{ 
	int min = INT_MAX, min_index; 

	for (int v = 0; v < VERTICES; v++) 
		if (sptSet[v] == false && dist[v] <= min) 
			min = dist[v], min_index = v; 

	return min_index; 
} 

int printSolution(int dist[], int n, int src) 
{ 
	for (int i = 0; i < VERTICES; i++) 
		printf("%c -> %c ==> %d\n", char(src+65), char(i+65), dist[i]); 
} 

void shortestPath(int graph[VERTICES][VERTICES], int src) 
{ 
	int dist[VERTICES]; 
	bool sptSet[VERTICES];  
	for (int i = 0; i < VERTICES; i++) 
		dist[i] = INT_MAX, sptSet[i] = false; 
	dist[src] = 0; 
	for (int count = 0; count < VERTICES - 1; count++) { 
		int u = minDis(dist, sptSet); 
		sptSet[u] = true;  
		for (int v = 0; v < VERTICES; v++) 
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
				&& dist[u] + graph[u][v] < dist[v]) 
				dist[v] = dist[u] + graph[u][v]; 
	} 
	printSolution(dist, VERTICES, src); 
} 
 
int main() 
{ 
	int graph[VERTICES][VERTICES] = { 
	                    { 0, 1, 3, 4, 7, 2, 4, 1, 0 }, 
						{ 4, 0, 7, 0, 9, 14, 0, 0, 0 }, 
						{ 2, 0, 0, 9, 0, 10, 0, 0, 0 }, 
						{ 1, 0, 4, 14, 10, 0, 2, 0, 0 }, 
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 }, 
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 }, 
			            { 0, 0, 0, 0, 0, 2, 0, 1, 6 }, 
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 }, 
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } 
	}; 
    
    printf("Matrix format representaion of Distances:\n");
    for(int i=0; i<VERTICES; i++) {
        if(i==0) {
            printf("\t");
            for(int z=0; z<VERTICES; z++) {
                printf("%c\t",char(z+65));
            }
            printf("\n\n");
        }
        for(int j=0; j<VERTICES; j++) {
            if(j==0) {
                printf("%c\t",char(j+65));
            }
            printf("%d\t",graph[i][j]);
        }
        printf("\n\n");
    }
    printf("\nMinimum Distances:\n");
    for(int i=0; i<VERTICES; i++) {
	    shortestPath(graph, i);
    }
	return 0; 
} 
