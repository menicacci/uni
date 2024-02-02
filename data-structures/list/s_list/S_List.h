#ifndef _S_LIST_H
#define _S_LIST_H

typedef struct S_List {
	struct S_List* next;
	struct S_List* prev;
	int info;
} SL;

typedef SL* pSL;

void initialize(pSL*);

void add_head(pSL,int);
void add_tail(pSL,int);
void add_aftr(pSL,int);
void add_befr(pSL,int);
void add_ordr(pSL,int);

pSL search(pSL,int);

void delete_head(pSL);
void delete_tail(pSL);
void delete_value(pSL,int);

void delete_list(pSL);

void sort_list(pSL);

int count_nodes(pSL);

void print_list(pSL);

#endif