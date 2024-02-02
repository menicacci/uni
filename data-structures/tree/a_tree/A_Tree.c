#include <stdio.h>
#include <stdlib.h>
#include "A_Tree.h"

/* INSERT */

void allocate_node(AT* node, int val) {
	AT new_node = (AT)malloc(sizeof(AN));

	new_node->info = val;

	new_node->l = new_node->r = new_node->p = NULL;

	*node = new_node;
}

void add_root(AT* root, int val) {
	if(*root != NULL) return;

	AT new_node;
	allocate_node(&new_node,val);
}

AT add_sibling(AT node, int val) {
	AT new_node;
	allocate_node(&new_node,val);

	new_node->p = node->p;
	new_node->r = node;

	new_node->parent->left = new_node;

	return new_node;
}

AT add_child(AT node, int val) {
	AT new_node;
	allocate_node(&new_node,val);

	new_node->p = node;
	new_node->r = node->l;

	node->l = new_node;

	return new_node;
}


/* SEARCH */

AT search_node_1(AT node, int val) {
	if(node == NULL) return NULL;

	if(node->info == val) return node;

	AT l = search_node_1(node->l,val);
	if(l != NULL) return l;

	return search_node_1(node->r,val);
}

AT search_node_2(AT node, int val) {
	if(node == NULL) return NULL;

	if(node->info == val) return node;

	AT child = node->l;
	AT output;

	while(child != NULL) {
		output = search_node_2(child,val);
		if(output != NULL) return output;

		child = child->r;
	}

	return NULL;
}

/* STUFF */

int height_1(AT node) {
	if(node == NULL) return -1;

	int l = 1 + height(node->l);
	int r = height(node->r);

	if(l > r) return l;
	return r;
}

int height_2(AT node) {
	if(node == NULL) return -1;

	int h_t = -1;
	int c_h;

	while(node != NULL) {
		c_h = height(node->l);
		if(c_h > h_t) h_t = c_h;

		node = node->r;
	}
	h_t++;

	return h_t;
}

int node_per_level(AT node, int lev) {
	if(node == NULL) return 0;

	if(lev == 0) {
		int output = 0;

		while(node != NULL) {
			output++;

			node = node->right;
		}

		return output;
	}

	return node_per_level(node->l,lev-1) + node_per_level(node->r,lev);
}

int max_grade(AT node) {
	if(node == NULL) return -1;

	int act_g, max_g, chd_g;
	act_g = max_g = 0;

	AT child = node->left;

	while(child != NULL) {
		chd_g = max_grade(child);
		act_g++;

		if(chd_g > max_g) max_g = chd_g;

		child = child->right;
	}	

	if(act_g > max_g) return act_g;
	return max_g;
}


/* PRINT */

void print_tab(AT node, int tab) {
	for(int i = 0; i < tab; i++) printf("\t");

	printf("%d\n", node->info);
}

void print_tree_ric(AT node, int lev) {
	if(node == NULL) return;

	print_tab(tab,lev);

	print_tree_ric(node->l,lev-1);
	print_tree_ric(node->r,lev);
}

void print_tree(AT node) {
	print_tree_ric(node,0);

	printf("\n\n\n");
}

void print_sons(AT node) {
	if(node == NULL) return;

	printf("%d's sons: ", node->info);

	node = node->l;
	while(node != NULL) {
		printf("%d ", node->info);
		node = node->right;
	}

	pintf("\n");
}


void delete_tree(AT node) {
	if(node == NULL) return;

	delete_tree(node->l);
	delete_tree(node->r);

	free(node);
}

void delete_node(AT node) {
	if(node == NULL) return;

	if(node->p == NULL) delete_tree(node);

	if(node->p->l == node) {
		node->p->l = node->r;
		node->r = NULL;

		delete_tree(node);
		return;
	}

	AT child = node->p->l;
	while(child->right != node) child = child->right;

	child->right = node->right;
	node->right = NULL;

	delete_tree(node);
}


/* UTILITY */

void generate_tree(AT node, int lev, int chd) {
	if(node == NULL) return;

	if(lev == 0) return;

	AT child;
	for(int i = 0; i < chd; i++) {
		child = add_child(node,rand()%100);
		generate_tree(child,lev-1,chd);
	}
}