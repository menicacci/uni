#include <stdio.h>
#include <stdlib.h>
#include "BS_Tree.h"

/* INSERT */

BST* new_tree_elem(int k) {
	BST* new_node = (BST*)malloc(sizeof(BST));

	new_node->p = new_node->l = new_node->r = NULL;
	new_node->key = k;

	return new_node;
}

int BST_insert(BST* node, int k) {
	if(k < node->key) {
		if(node->l == NULL) {
			node->l = new_tree_elem(k);
			node->l->p = node;
			
			return 1;
		}
		return BST_insert(node->l,k);
	}
	else if(k > node->key) {
		if(node->r == NULL) {
			node->r = new_tree_elem(k);
			node->r->p = node;

			return 1;
		}
		return BST_insert(node->r,k); 
	}

	return 0;
}

int tree_insert(BST** root, int k) {
	if(*root == NULL) {
		*root = new_tree_elem(k);
		return 1;
	}
	return BST_insert(*root,k);
}


/* STUFF */


BST* tree_minimum(BST* root) {
	while(root->l != NULL) root = root->l;

	return root;
}

BST* tree_maximum(BST* root) {
	while(root->r != NULL) root = root->r;

	return root;
}

int height_BST(BST* root) {
	if(root == NULL) return -1;

	int l = height_BST(root->l);
	int r = height_BST(root->r);

	if(l > r) return l + 1;
	return r + 1;
}

int count_nodes(BST* root) {
	if(root == NULL) return 0;

	return 1 + count_nodes(root->l) + count_nodes(root->r);
}


/* SEARCH */

BST* itr_tree_serch(BST* root, int k) {
	while(root != NULL) {
		if(root->key == k) return root;

		if(root->key > k) root = root->l;
		else root = root->r;
	}

	return NULL;
}

BST* ric_tree_serch(BST* root, int k) {
	if(root == NULL) return NULL;

	if(root->key == k) return root;

	if(root->key > k) return ric_tree_serch(root->l,k);
	return ric_tree_serch(root->r,k);
}


/* DELETE */

void delete_tree(BST* root) {
	if(root == NULL) return;

	delete_tree(root->l);
	delete_tree(root->r);

	free(root);
}

void tree_bypass(BST** root, BST* node) {
	BST* child;

	if(node->left != NULL) child = node->l;
	else child = node->r;

	if(child != NULL) child->parent = node->parent;

	if(node->p != NULL)
		if(node == node->p->l) node->p->l = child;
		node->p->r = child;
	else *root = child;

	free(node);
}

void tree_delete(BST** root, BST* node) {
	BST* temp;

	if(node->l != NULL && node->r != NULL) {
		temp = tree_minimum(node->r);
		node->key = temp->key;
	}
	else temp = node;

	tree_bypass(root,temp);
}


/* VISIT */

int is_sorted(int* A, int size) {
	for(int i = 0; i < size - 1; i++)
		if(A[i] > A[i + 1]) return 0;

	return 1;
}

int tree_to_array(int* A, BST* root, int i) {
	if(root == NULL) return i;

	i = tree_to_array(A,root->l;i);

	A[i] = root->key;

	i = tree_to_array(A,root->r,i+1);

	return i;
}

int BST_sym(BST* root) {
	int n = count_nodes(root);

	int* A = (int*)calloc(n,sizeof(int));
	tree_to_array(A,root,0);

	int output = is_sorted(A,n);

	free(A);
	return output;
}


/* SORT */

void tree_sort(int* A, int size) {
	BST* root = NULL;
	for(int i = 0; i < size; i++) tree_insert(&root,A[i]);

	tree_to_array(A,root,0);
	
	delete_tree(root);	
}