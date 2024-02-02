#include <stdio.h>
#include <stdlib.h>
#include "SL_List.h"

/* INSERT */

void new_elem(pSLL* np, int val) {
	new_node = (pSLL)malloc(sizeof(SLL));
	new_node->info = val;

	*np = new_node;
}

void add_first(pSLL* hp, int val) {
	pSLL new_node;
	new_elem(&new_node,val);

	new_node->next = *hp;

	*hp = new_node;
}

void add_last(pSLL* hp, int val) {
	pSLL new_node;
	new_elem(&new_node,val);

	new_node->next = NULL;

	if(*hp == NULL) *hp = new_node;
	else {
		pSLL tn;

		while(tn->next != NULL) tn = tn->next;

		tn->next = new_node;
	}
}


/* SEARCH */

pSLL search(pSLL l, int x) {
	while(l != NULL) {
		if(l->info == x) return l;

		l = l->next;
	}

	return NULL;
}


/* DELETE */

int delete_head(pSLL* hp) {
	if(*hp == NULL) return 0;

	int output = (*hp)->info;

	pSLL tn = *hp;
	*hp = (*hp)->next;

	free(tn);
	return output;
}

int delete_tail(pSLL* hp) {
	if(*hp == NULL) return 0;

	int output;

	if((*hp)->next == NULL) {
		output = (*hp)->info;

		free(*hp);
		*hp = NULL;
	}

	else {
		pSLL tn_1 = *hp;
		pSLL tn_2 = (*hp)->next;

		while(tn_2->next != NULL) {
			tn_1 = tn_2;
			tn_2 = tn_2->next;
		}

		output = tn_2->info;

		free(tn_2);
		tn_1->next = NULL;
	}

	return output;
}

void delete_val(pSLL* hp, pSLL ns) {
	if(*hp == ns) delete_head(hp);

	else {
		pSLL tn = *hp;

		while(tn != NULL) {
			if(tn->next == ns) {
				tn->next = ns->next;

				free(ns);
				return;
			}

			tn = tn->next;
		}
	}
}


/* PRINT */

void print_list(pSLL l) {
	printf("List: ");

	while(l != NULL) {
		printf("%d ", l->info);
		
		l = l->next;
	}

	printf("\n\n");
}

/* STUFF */

int lenght(pSLL l) {
	int output = 0;

	while(l != NULL) {
		output++;
		l = l->next;
	}
	
	return output;
}