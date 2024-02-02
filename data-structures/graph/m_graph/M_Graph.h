#ifndef _M_GRAPH_H
#define _M_GRAPH_H

#include "SL_List.h"

typedef struct matrix_graph {
	int size;
	int** matrix;
} MG;

MG* new_graph(int);

void print_graph(MG*);

void add_arc(MG*,int,int);

void bfs(MG*,int);
void bfs_color(MG*,int*,int);
void dfs_color(MG*,int*,int);
void dfs_color_mark(MG*,int*,int,int);
int  dfs_color_size(MG*,int*,int);
int  dfs_color_arch(MG*,int*,int);

int is_connected(MG*);
int comp_connected(MG*);

int* distance(MG*,int);



#endif