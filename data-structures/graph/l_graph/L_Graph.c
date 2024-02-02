#include <stdio.h>
#include <stdlib.h>

#include "L_Graph.h"

LG* new_graph(int dim) {
	LG* g = (LG*)malloc(sizeof(LG));
	g->size = dim;

	g->array = (AE**)calloc(g->size,sizeof(AE*));

	return g;
}

void print_graph(LG* g) {
	for(int i = 0; i < g->size; i++) {
		printf("[%d] -> ", i);

		AE* x = g->array[i];
		while(x != NULL) {
			printf("%d ", x->info);
			x = x->next;
		}
		printf("\n");
	}
	printf("\n");
}

void add_arc(LG* g, int i, int j) {
	AE* ij_arc = (AE*)malloc(sizeof(AE));
	ij_arc->prev = NULL;
	ij_arc->next = g->array[i];
	ij_arc->info = j;
	if(g->array[i] != NULL) g->array[i]->prev = ij_arc;
	g->array[i] = ij_arc;

	if(i != j) {
		AE* ji_arc = (AE*)malloc(sizeof(AE));
		ji_arc->prev = NULL;
		ji_arc->next = g->array[j];
		ji_arc->info = i;
		if(g->array[j] != NULL) g->array[j]->prev = ji_arc;
		g->array[j] = ji_arc;
	}
}

void bfs(LG* g, int v) {
	int* color = (int*)calloc(g->size,sizeof(int));
	pSLL q = NULL;
	add_head(&q,v);
	color[v] = 1;

	while(q != NULL) {
		int u = delete_first(&q);
		printf("[%d]\n", u);

		AE* x = g->array[u];
		while(x != NULL) {
			if(!color[x->info]) {
				add_tail(&q,x->info);
				color[x->info] = 1;
			}
			x = x->next;
		}
	}
	printf("\n");
}

void bfs_color(LG* g, int* color, int v) {
	pSLL q = NULL;
	add_head(&q,v);
	color[v] = 1;

	while(q != NULL) {
		int u = delete_first(&q);
		AE* x = g->array[u];
		while(x != NULL) {
			if(!color[x->info]) {
				add_tail(&q,x->info);
				color[x->info] = 1;
			}
			x = x->next;
		}
	}
}

void dfs_color(LG* g, int* color, int v) {
	color[v] = 1;

	AE* x = g->array[v];

	while(x != NULL) {
		if(!color[x->info]) dfs_color(g,color,x->info);

		x = x->next;
	}
}

void dfs_color_mark(LG* g, int* color, int v, int mark) {
	color[v] = mark;

	AE* x = g->array[v];

	while(x != NULL) {
		if(!color[x->info]) dfs_color_mark(g,color,v,mark);

		x = x->next;
	}
}

int dfs_color_size(LG* g, int* color, int v) {
	int sz = 1;
	color[v] = 1;

	AE* x = g->array[v];

	while(x != NULL) {
		if(!color[x->info])
			sz += dfs_color_size(g,color,x->info);

		x = x->next;
	}
	return sz;
} 

int dfs_color_arch(LG* g, int* color, int v) {
	int arch = 0;
	color[v] = 1;

	AE* x = g->array[v];

	while(x != NULL) {
		arch++;
		if(!color[x->info]) arch += dfs_color_arch(g,color,x->info);
		
		x = x->next;
	}
	return arch;
}

int is_connected(LG* g) {
	int* color = (int*)calloc(g->size,sizeof(int));
	bfs_color(g,color,0);

	for(int i = 0; i < g->size; i++)
		if(!color[i]) return 0;
	return 1;
}

int comp_connected(LG* g) {
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

void mark_distance(AG* g, int* color, int v) {
	color[v] = 1;
	
	pSLL q = NULL;
	add_head(&q,v);
	while(q != NULL) {
		int u = delete_head(&q);

		AE* x = g->array[u];
		while(x != NULL) {
			if(!color[x->info] || color[x->info] > color[u] + 1) {
				add_tail(&q,x->info);
				color[x->info] = color[u] + 1;
			}
			x = x->next;
		}
	}
}

int* distance(AG* g, int v) {
	int* color = (int*)calloc(g->size,sizeof(int));

	mark_distance(g,color,v);

	for(int i = 0; i < g->size; i++)
		color[i]--;

	return color;
}

