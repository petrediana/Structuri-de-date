#include "pch.h"
#include <stdio.h>
#include <malloc.h>

struct nod_coada {
	int inf;
	nod_coada *next;
};

nod_coada *creare_nod(int inf, nod_coada *next) {
	nod_coada *nou = (nod_coada*)malloc(sizeof(nod_coada));

	nou->inf = inf;
	nou->next = next;

	return nou;
}

void put(nod_coada **prim, nod_coada **ultim, int inf) {
	nod_coada *nou = creare_nod(inf, NULL);

	if ((*prim) == NULL && (*ultim) == NULL) {
		(*prim) = nou;
		(*ultim) = (*prim);
	}
	else {
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

void traversare(nod_coada *prim) {
	nod_coada *aux = prim;

	while (aux) {
		printf("\nInformatia: %d", aux->inf);
		aux = aux->next;
	}
}

int get(nod_coada **prim, nod_coada **ultim, int *extras) {
	if ((*prim) == NULL && (*ultim) == NULL) {
		return -1;
	}
	else {
		nod_coada *aux = (*prim);
		(*extras) = (*prim)->inf;
		(*prim) = (*prim)->next;

		free(aux);
		if ((*prim) == (*ultim))
			(*ultim) = NULL;
		
		return 0;
	}
}

void main() {
	nod_coada *prim = NULL;
	nod_coada *ultim = NULL;

	put(&prim, &ultim, 1);
	put(&prim, &ultim, 2);
	put(&prim, &ultim, 3);
	put(&prim, &ultim, 4);
	put(&prim, &ultim, 5);

	traversare(prim);

	int extras;
	while (get(&prim, &ultim, &extras) == 0) {
		printf("\nElement extras -> %d", extras);
	}
}
