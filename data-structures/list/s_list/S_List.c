#include <stdio.h>
#include <stdlib.h>
#include "S_List.h"


void initialize(pSL* pl) {
	pSL sentinel = (pSL)malloc(sizeof(SL));

	sentinel->next = sentinel->next = sentinel;

	*pl = sentinel;
}


/* INSERT */

void allocate_node(pSL* n, int val) {
	pSL new_node = (pSL)malloc(sizeof(SL));
	new_node->info = val;

	*n = new_node;
}

void add_head(pSL s, int val) {
	pSL new_node;
	allocate_node(&new_node,val);

	new_node->next = s->next;
	new_node->prev = s;

	s->next->prev = new_node;
	s->next = new_node;
}

void add_tail(pSL s, int val) {
	pSL new_node;
	allocate_node(&new_node,val);

	new_node->next = s;
	new_node->prev = s->prev;

	s->prev->next = new_node;
	s->prev = new_node;
}

void add_aftr(pSL n, int val) {
	if(n == NULL) return;

	pSL new_node;
	allocate_node(&new_node,val);

	new_node->next = n->next;
	new_node->prev = n;

	n->next->prev = new_node;
	n->next = new_node;
}

void add_befr(pSL n, int val) {
	if(n == NULL) return;

	pSL new_node;
	allocate_node(&new_node,val);

	new_node->next = n;
	new_node->prev = n->prev;

	n->prev->next = n;
	n->prev = n;
}

void add_ordr(pSL s, int val) {
	if(s->next = s) {
		add_head(s,val);
		return;
	}

	pSL t_n = s->next;

	if(t_n->info > val) {
		add_head(s,val);
		return;
	}

	while(t_n->next != s) {
		if(t_n->info > val) {
			add_before(t_n,val);
			return;
		}
		
		t_n = t_n->next;
	}

	add_tail(s,val);
}


/* SEARCH */

pSL search(pSL s, int x) {
	pSL t_n = s->next;

	while(t_n != s) {
		if(t_n->info == x) return t_n;
	
		t_n = t_n->next;
	}

	return NULL;
}


/* DELETE */

void delete_node(pSL n) {
	n->next->prev = n->prev;
	n->prev->next = n->next;
} 

void delete_head(pSL s) {
	if(s->next == s) return;

	pSL t_n = s->next;

	delete_node(t_n);
	free(t_n);
}

void delete_tail(pSL s) {
	if(s->prev == s) return;

	pSL t_n = s->prev;

	delete_node(t_n);
	free(t_n);
}

void delete_value(pSL s, int val) {
	pSL t_n = search(s,val);

	if(t_n != NULL) {
		delete_node(t_n);
		free(t_n);
	}
}

void delete_list(pSL s) {
	while(s->next != s) delete_head(s);

	free(s);
}


/* SORT */

void change_infos(pSL a, pSL b) {
	int c = a->info;
	a->info = b->info;
	b->info = c;
}

void sort_list(pSL s) {
	if(s->next == s) return;

	pSL f = s->next;
	pSL m, t;

	while(f->next != s) {
		m = f;

		for(t = f->next; t != s; t = t->next) 
			if(t->info < m->info) m = t;

		change_infos(f,m);

		f = f->next;
	}
}


/* STUFF */

int count_nodes(pSL s) {
	int output = 0;
	pSL t_n = s->next;

	while(t_n != s) {
		output++;
		t_n = t_n->next;
	} 

	return output;
}


/* PRINT */

void print_list(pSL s) {
	pSL t_n = s->next;

	printf("List: ");

	while(t_n != s) {
		printf("%d ", t_n->info);
		t_n = t_n->next;
	}

	printf("\n\n");
}