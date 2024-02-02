#include <stdio.h>
#include <stdlib.h>
#include "O_Graph.h"

OG* new_graph() {
	OG* g = (OG*)malloc(sizeof(OG));

	g->node_num = 0;
	g->arch_num = 0;

	g->nodes = NULL;
	g->arches = NULL;

	return g;
}

