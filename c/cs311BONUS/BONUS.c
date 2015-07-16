#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
 
 int nodes;
 
void push(int** flow, int** df, int** capacity, int* edges, int u, int v) {
  df[u][v] = MIN(edges[u], capacity[u][v]);
  flow[u][v] = flow[u][v] + df[u][v];
  flow[v][u] = -flow[u][v];
  edges[u] = edges[u] - df[u][v];
  edges[v] = edges[u] + df[u][v];
}
 
void relabel(int** capacity, int** flow, int*height, int u) {
  int v;
  int min = 9999999;
  for (v = 0; v < nodes; v++) {
    if (capacity[u][v] - flow[u][v] > 0) {
      min = MIN(min, height[v]);
      height[u] = min + 1;
    }
  }
}
 
void matrix(int** oo) {
  int i,j;
  for (i = 0; i < nodes; i++) {
    for (j = 0; j < nodes; j++)
      printf("%d\t",oo[i][j]);
    printf("\n");
  }
}
 
int maxFlow(){
//	if(u.isoverflowing() &&
//		capacity[u][v]>0 &&
//		height[u] == height[v]+1)
//			push(u,v);
	
	return 0;
}
	
int main(void) {
//------------------------------------------------	
	char buffer[20];
	char* last;
	FILE* input = fopen("input.txt", "r");
	fgets(buffer, 20, input);
	last = strtok(buffer," \n");
	nodes = atoi(last);
	printf("last = %s, nodes = %i",last, nodes);
 //-----------------------------------------------
	int df[nodes][nodes];
	int edges[nodes];
	int height[nodes];
	int flow[nodes][nodes];
	int capacity[nodes][nodes];
	int ls[nodes];
	int numedges, i, u, v, p, temp, n;
//------------------------------------------------
	while(fgets(buffer, 20, input) != NULL){
		numedges++;
		last = strtok(buffer," \n");
			u=atoi(last);
			printf("%s ", last);
		last = strtok(NULL," \n");
			v=atoi(last);
			printf("%s ", last);
		last = strtok(NULL," \n");
			capacity[u][v] = atoi(last);
			printf("%s ", last);
		printf("\n");
	}
//--------------------------------------------------
	  for (i = 0, p = 0; i < nodes; i++){
		if((i != 0) && (i != nodes-1)) {
		  ls[p] = i;
		  p++;
		}
	  }
//-------------------------------------------------- 
	  height[0] = nodes;
	  edges[0] = 999999999;
	  for (i = 0; i < nodes; i++)
		push(flow, df, capacity, edges, 0, i);
	  p = 0;
	  while (p < nodes - 2) {
		int u = ls[p];
		int old = height[u];
		//discharge(C, F, excess, height, seen, u);
		if (height[u] > old) {
			temp = ls[p];
			for (n = i; n > 0; n--){
				ls[n] = ls[n-1];
			}
			ls[0] = temp;
			p=0;
		}
		else
		  p += 1;
	  }
	  int maxflow = 0;
	  for (i = 0; i < nodes; i++)
		maxflow += flow[0][i];
	 
	  free(ls);
	  free(height);
	  free(edges);
  printf("Capacity:\n");
  //matrix(capacity);
  printf("Max Flow:\n%d\n", maxFlow());
  printf("Flows:\n");
  //matrix(flow);
 
  return 0;
}


