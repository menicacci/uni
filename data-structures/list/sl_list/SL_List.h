#ifndef _SL_LIST_H
#define _SL_LIST_H

typedef struct SL_List {
	struct SL_List* next;
	int info;
} SLL;

typedef SLL* pSLL;

void add_head(pSLL*,int);
void add_tail(pSLL*,int);

pSLL search(pSLL,int);

int delete_head(pSLL*);
int delete_tail(pSLL*);
void delete_val(pSLL*,pSLL);

void print_list(pSLL);

int lenght(pSLL);

#endif