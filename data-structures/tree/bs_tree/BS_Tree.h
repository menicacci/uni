#ifndef _BS_TREE_H
#define _BS_TREE_H

typedef struct BS_Tree {
	struct BS_Tree* p;
	struct BS_Tree* l;
	struct BS_Tree* r;
	int key;
} BST;

BST* new_tree_elem(int);
int BST_insert(BST*,int);
int tree_insert(BST**,int);

BST* tree_minimum(BST*);
BST* tree_maximum(BST*);
int height_BST(BST*);

BST* itr_tree_serch(BST*,int);
BST* ric_tree_serch(BST*,int);

void delete_tree(BST*);
void tree_bypass(BST**,BST*);
void tree_delete(BST**,BST*);

void tree_sort(int*,int);

#endif