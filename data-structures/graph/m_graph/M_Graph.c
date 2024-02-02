 #include <stdio.h>
#include <stdlib.h>
#include "M_Graph.h"

MG* new_graph(int dim) {
	MG* g = (MG*)malloc(sizeof(MG));

	g->size = dim;
	g->matrix = (int**)calloc(g->size,sizeof(int*));

	for(int i = 0; i < g->size; i++)
		g->matrix[i] = (int*)calloc(g->size,sizeof(int));

	return g;
}

void print_graph(MG* g) {
	for(int i = 0; i < g->size; i++) {
		for(int j = 0; j < g->size; j++)
			printf("%d ", g->matrix[i][j]);
		printf("\n");
	}
	printf("\n");
}

void add_arc(MG* g, int i, int j) {
	g->matrix[i][j] = 1;
	g->matrix[j][i] = 1;
}



void bfs(MG* g, int v) {
	int* color = (int*)calloc(g->size,sizeof(int));
	color[v] = 1;
	
	pSLL q = NULL;
	add_tail(&q,v);

	while(q != NULL) {
		int u = delete_head(&q);
		printf("[%d]\n", u);

		for(int i = 0; i < g->size; i++) {
			if(g->matrix[u][i]) {
				if(!color[i]) {
					add_tail(&q,i);
					color[i] = 1;
				}
			}
		}
	}
	printf("\n\n");
}

void bfs_color(MG* g, int* color, int v) {
	pSLL q = NULL;
	add_tail(&q,v);

	while(q != NULL) {
		int u = delete_head(&q);

		for(int i = 0; i < g->size; i++)
			if(g->matrix[u][i])
				if(!color[i]) {
					add_tail(&q,i);
					color[i] = 1;
				}
	}
}

void dfs_color(MG* g, int* color, int v) {
	color[v] = 1;

	for(int i = 0; i < g->size; i++)
		if(g->matrix[i][v])
			if(!color[i])
				dfs_color(g,color,i);
}

void dfs_color_mark(MG* g, int* color, int v, int mark) {
	color[v] = mark;

	for(int i = 0; i < g->sise; i++)
		if(g->matrix[i][v])
			if(!color[i]) dfs_color_mark(g,color,i,mark);
}

int dfs_color_size(MG* , int* color, int v) {
	int sz = 1;
	color[v] = 1;

	for(int i = 0; i < g->size; i++)
		if(g->matrix[i][v])
			if(!color[i]) size += dfs_color_size(g,color,i);

	return sz;
}

int dfs_color_arch(MG* g, int* color, int v) {
	int arch = 0;
	color[v] = 1;

	for(int i = 0; i < g->size; i++) 
		if(g->matrix[i][v]) {
			arch++;
			if(!color[i]) arch += dfs_color_arch(g,color,i);
		}
	return arch;
}

int is_connected(MG* g) {
	int* color = (int*)calloc(g->size,sizeof(int));
	bfs_color(g,color,0);

	for(int i = 0; i < g->size; i++) 
		if(!color[i]) return 0;
	return 1;
}

int comp_connected(MG* g) {
	int* color = (int*)calloc(g->size,sizeof(int));
	int comp = 0;

	for(int i = 0; i < g->size; i++) 
		if(!color[i]) {
			comp++;
			bfs_color(g,color,i);
		}

	free(color);
	return comp;
}

void mark_distance(MG* g, int* dist, int v) {
	dist[v] = 1;
	
	pSLL q = NULL;
	add_head(&q,v);

	while(q != NULL) {
		int u = delete_head(&q);

		for(int i = 0; i < g->size; i++)
			if(g->matrix[u][i])
				if(!dist[i] || dist[i] > dist[u] + 1) {
					insert_last(&q,i);
					dist[i] = dist[u] + 1;
				}
	}
}

int* distance(MG* g, int v) {
	int* dist = (int*)calloc(g->size,sizeof(int));
	
	mark_distance(g,dist,v);
	
	for(int i = 0; i < g->size; i++) 
		dist[i]--;
	
	return dist;
}

