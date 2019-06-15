#include "pch.h"
#include <stdio.h>
#include <malloc.h>

struct nod_stiva {
	int inf;
	nod_stiva *next;
};

nod_stiva *creare_nod(int inf, nod_stiva *next) {
	nod_stiva *nou = (nod_stiva*)malloc(sizeof(nod_stiva));

	nou->inf = inf;
	nou->next = next;

	return nou;
}

void push(nod_stiva **varf, int inf) {
	nod_stiva *nou = creare_nod(inf, NULL);

	if ((*varf) == NULL) {
		(*varf) = nou;
	}
	else {
		nou->next = (*varf);
		(*varf) = nou;
	}
}

void traversare(nod_stiva *varf) {
	nod_stiva *aux = varf;

	while (aux) {
		printf("\nInformatia: %d", aux->inf);
		aux = aux->next;
	}
}

int pop(nod_stiva **varf, int *extras) {
	if ((*varf) == NULL)
		return -1;
	else {
		nod_stiva *aux = (*varf);
		(*extras) = (*varf)->inf;
		(*varf) = (*varf)->next;

		free(aux);
		return 0;
	}
}

void main() {
	nod_stiva *varf = NULL;

	push(&varf, 1);
	push(&varf, 2);
	push(&varf, 3);
	push(&varf, 4);
	push(&varf, 5);

	traversare(varf);

	printf("\n");
	int extras;
	while (pop(&varf, &extras) == 0) {
		printf("\nSe extrag elementele -> %d", extras);
	}
}