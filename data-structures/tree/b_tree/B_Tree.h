#ifndef _B_TREE_H
#define _B_TREE_H

typedef struct B_Node {
	struct B_Node* l;
	struct B_Node* r;
	struct B_Node* p;
	int info;
} BN;

typedef struct BN* BT;

void add_root(BT*,int);
BT add_l(BT,int);
BT add_r(BT,int);

BT search_node_pre(BT,int);
BT search_node_aft(BT,int);
BT search_node_sim(BT,int);
int search_node(BT,int);
int search_depth(BT,int);

int height(BT);
int count_nodes(BT);
int count_leafs(BT);
int node_per_level(BT,int);
int full(BT);

void cut_tree(BT);
void cut_branch(BT);

void print_tree(BT);

BT copy_tree(BT);

#include "SL_List.h"

pSL path(BT,BT);
pSL find_path(BT,int);
int degree_of_kinship(BT,BT,BT);

#endif