#include <stdio.h>
#include <stdlib.h>
#include "B_Tree.h"


/* INSERT */

void allocate_node(BT* node) {
	BT new_node = (BT)malloc(sizeof(BN));

	new_node->l = new_node->r = new_node->p = NULL;

	*node = new_node;
}

void add_root(BT* root, int val) {
	if(*root != NULL) return;

	allocate_node(root);

	(*root)->info = val;
}

void add_child(BT node_p, BT node_c, int val) {
	node_c->info = val;

	node_c->p = node_p;
}

BT add_l(BT node, int val) {
	if(node->l != NULL) return NULL;

	BT new_node;
	allocate_node(&new_node);
	add_child(node,new_node,val);

	node->l = new_node;
}

BT add_r(BT node, int val) {
	if(node->r != NULL) return NULL;

	BT new_node;
	allocate_node(&new_node);
	add_child(node,new_node,val);

	node->r = new_node;
}


/* SEARCH */

BT search_node_pre(BT node, int val) {
	if(node == NULL) return NULL;

	if(node->info == val) return node;

	BT l = search_node_pre(node->l,val);
	if(l != NULL) return l;
	
	return search_node_pre(node->r,val);
}

BT search_node_aft(BT node, int val) {
	if(node == NULL) return NULL;

	BT l = search_node_pre(node->l,val);
	if(l != NULL) return l;

	BT r = search_node_pre(node->r,val);
	if(r != NULL) return r;

	if(node->info == val) return node;

	return NULL;
}

BT search_node_sim(BT node, int val) {
	if(node == NULL) return NULL;

	BT l = search_node_pre(node->l,val);
	if(l != NULL) return l;

	if(node->info == val) return node;
	
	return search_node_pre(node->r,val);
}

int search_node(BT node, int val) {
	if(node == NULL) return 0;

	return (node->info == val) || search_node(node->l) || search_node(node->r);
}

int search_depth_ric(BT node, int val, int lev) {
	if(node == NULL) return -1;

	if(node->info == val) return lev;

	int l = search_depth_ric(node->l,val,lev+1);
	if(l != -1) return l;

	int r = search_depth_ric(node->r,val,lev+1);
	if(r != -1) return r;

	return -1;
}

int search_depth(BT node, int val) {
	return search_depth_ric(node,val,0);
}


/* STUFF */

int height(BT node) {
	if(node == NULL) return -1;

	int l = height(node->l);
	int r = height(node->r);

	if(l > r) return l + 1;
	return r + 1;
}

int count_nodes(BT node) {
	if(node == NULL) return 0;

	return 1 + count_nodes(node->l) + count_nodes(node->r);
}

int count_leafs(BT node) {
	if(node == NULL) return 0;

	return (node->l == NULL && node->r == NULL) + count_leafs(node->l) + count_leafs(node->r);
}

int node_per_level(BT node, int lev) {
	if(node == NULL) return 0;

	if(lev == 0) return 1;

	return node_per_level(node->l,lev-1) + node_per_level(node->r,lev-1);
}

int full(BT node) {
	if(node == NULL) return 0;

	if(node->l == NULL && node->r == NULL) return 1;

	return full(node->l) && full(node->r);
}


/* DELETE */

void cut_tree(BT node) {
	if(node == NULL) return;

	cut_tree(node->l);
	cut_tree(node->r);

	free(node);
}

void cut_branch(BT node) {
	if(node == NULL) return;

	if(node->p != NULL) {
		if(node->p->l == node) node->p->l = NULL;
		else node->p->r = NULL;
	}

	delete_tree(node);
}


/* PRINT */

void print_tab(BT node, int tab) {
	for(int i = 0; i < tab; i++) printf("\t");

	printf("%d\n", node->info);
}

void print_tree_ric(BT node, int h) {
	if(node == NULL) return;

	print_tree_ric(node->l,h-1);

	print_tab(node,h);

	print_tree_ric(node->r,h-1);
}

void print_tree(BT node) {
	printf("Binary tree:\n\n");
	print_tree_ric(node,height(node));

	printf("\n\n\n");
}


/* COPY */

BT copy_tree_ric(BT node) {
	if(node == NULL) return NULL;

	BT new_node;
	allocate_node(&new_node);
	new_node->info = node->info;

	new_node->l = copy_tree_ric(node->l);
	if(new_node->l != NULL) new_node->l->p = new_node;

	new_node->r = copy_tree_ric(node->r);
	if(new_node->r != NULL) new_node->r->p = new_node;

	return new_node;
}

BT copy_tree(BT root) {
	if(root == NULL) return NULL;

	BT new_tree = copy_tree_ric(root);
	new_tree->p = NULL;

	return new_tree;
}


/* TREE & LIST */

pSL path(BT root, BT node) {
	if(root == NULL || node == NULL) return NULL;

	pSL list = NULL;

	while(node != NULL) {
		add_head(&list,node->info);

		node = node->p;
	}

	return list;
}

pSL find_path(BT root, int val) {
	if(root == NULL) return NULL;

	BT find_val = search_node_pre(root,val);
	if(find_val == NULL) return NULL;

	return path(root,find_val);
}

int degree_of_kinship(BT root, BT n1, BT n2) {
	if(root == NULL || n1 == NULL || n2 == NULL) return -1;
	if(n1 == n2) return 0;

	pSL l1 = path(root,n1);
	pSL l2 = path(root,n2);

	pSL i1 = l1;
	pSL i2 = l2;

	while(i1->info == i2->info) {
		i1 = i1->next;
		i2 = i2->next;
		if(i1 == NULL || i2 == NULL) break;
	}

	int output = length(i1) + lenght(i2);

	delete_list(l1);
	delete_list(l2);

	return output;
}