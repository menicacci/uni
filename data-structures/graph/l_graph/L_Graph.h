#ifndef _L_GRAPH_H
#define _L_GRAPH_H

#include "SL_List.h"

typedef struct array_elem {
	struct array_elem* prev;
	struct array_elem* next;
	int info;
} AE;

typedef struct list_graph {
	AE** array;
	int size;
} LG;

LG* new_graph(int);

void print_graph(LG*);

void add_arc(LG*,int,int);

void bfs(LG*,int);
void bfs_color(LG*,int*,int);
void dfs_color(LG*,int*,int);
void dfs_color_mark(LG*,int*,int,int);
int  dfs_color_size(LG*,int*,int);
int  dfs_color_arch(LG*,int*,int);

int is_connected(LG*);
int comp_connected(LG*);

int* distance(AG*,int);

#endif