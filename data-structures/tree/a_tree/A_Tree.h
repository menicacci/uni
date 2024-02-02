#ifndef _A_TREE_H
#define _A_TREE_H

typedef struct A_Node {
	struct A_Node* l;
	struct A_Node* r;
	struct A_Node* p;
	int info;
} AN;

typedef AN* AT;

void add_root(AT*,int);
AT add_sibling(AT,int);
AT add_child(AT,int);

AT search_node_1(AT,int);
AT search_node_2(AT,int);

int height_1(AT);
int height_2(AT);
int node_per_level(AT,int);
int max_grade(AT);

void print_tree(AT);
void print_sons(AT);

void delete_tree(AT);
void delete_node(AT,AT);

void generate_tree(AT,int,int);

#endif