#ifndef _O_GRAPH_H
#define _O_GRAPH_H

typedef struct Elem_L_Node EN;
typedef struct Elem_L_Arch EA;

typedef struct Node_Struct {
	EN* pos; // posizione nodo nella lista del grafo
	EA* arch; // lista archi incidenti
	int color;
} NS;

typedef struct Arch_Struct {
	EA* pos;
	NS* from;
	NS* to;
	EA* frompos;
	EA* topos;
} AS;

typedef struct Elem_L_Node {
	struct Elem_L_Node* prev;
	struct Elem_L_Node* next;
	NS* info;
} EN;

typedef struct Elem_L_Arch {
	struct Elem_L_Arch* prev;
	struct Elem_L_Arch* next;
	AS* info;
} EA;

typedef struct Object_Graph {
	int node_num;
	int arch_num;
	EA* arches;
	EN* nodes;
} OG;


OG* new_graph();

NS* add_node(OG*);
AS* add_arch(OG*);




#endif