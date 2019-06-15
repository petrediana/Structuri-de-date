#include "pch.h"
#include <stdio.h>
#include <malloc.h>

struct nod_lista_secundara {
	int inf;
	nod_lista_secundara *next;
};

struct nod_lista_principala {
	nod_lista_secundara *inf;
	nod_lista_principala *next;
};

void adauga_nod_lista_secundara(nod_lista_secundara **prim, int inf) {
	nod_lista_secundara *nou = (nod_lista_secundara*)malloc(sizeof(nod_lista_secundara));
	nou->inf = inf;
	nou->next = NULL;

	if ((*prim) == NULL) {
		(*prim) = nou;
	}
	else {
		nou->next = (*prim);
		(*prim) = nou;
	}
}

void traversare_lista_secundara(nod_lista_secundara *prim) {
	nod_lista_secundara *aux = prim;

	while (aux) {
		printf("\nInformatie lista secundara: %d", aux->inf);
		aux = aux->next;
	}
}

void dezalocare_lista_secundara(nod_lista_secundara **prim) {
	nod_lista_secundara *aux = (*prim);
	
	while (aux) {
		nod_lista_secundara *temp = aux;
		aux = aux->next;

		free(temp);
	}
}

void adauga_lista_principala(nod_lista_principala **prim, nod_lista_secundara *inf) {
	nod_lista_principala *nou = (nod_lista_principala*)malloc(sizeof(nod_lista_principala));
	nou->inf = inf;
	nou->next = NULL;

	if ((*prim) == NULL) {
		(*prim) = nou;
	}
	else {
		nou->next = (*prim);
		(*prim) = nou;
	}
}

void traversare_lista_principala(nod_lista_principala *prim) {
	nod_lista_principala *aux = prim;

	while (aux) {
		printf("\nInformatia listei principale -> ");
		traversare_lista_secundara(aux->inf);
		aux = aux->next;
	}
}

void dezalocare_lista_principala(nod_lista_principala **prim) {
	nod_lista_principala *aux = (*prim);

	while (aux) {
		nod_lista_principala *temp = aux;
		aux = aux->next;

		dezalocare_lista_secundara(&temp->inf);
		free(temp);
	}
	(*prim) = NULL;
}

void main() {
	nod_lista_secundara *prim_numere_pare = NULL;
	nod_lista_secundara *prim_numere_impare = NULL;

	adauga_nod_lista_secundara(&prim_numere_pare, 2);
	adauga_nod_lista_secundara(&prim_numere_pare, 4);
	adauga_nod_lista_secundara(&prim_numere_pare, 6);
	adauga_nod_lista_secundara(&prim_numere_pare, 8);

	adauga_nod_lista_secundara(&prim_numere_impare, 1);
	adauga_nod_lista_secundara(&prim_numere_impare, 3);
	adauga_nod_lista_secundara(&prim_numere_impare, 5);
	adauga_nod_lista_secundara(&prim_numere_impare, 7);

	traversare_lista_secundara(prim_numere_pare);
	traversare_lista_secundara(prim_numere_impare);

	printf("\n\n");

	nod_lista_principala *prim_lp = NULL;
	adauga_lista_principala(&prim_lp, prim_numere_impare);
	adauga_lista_principala(&prim_lp, prim_numere_pare);

	traversare_lista_principala(prim_lp);

	dezalocare_lista_principala(&prim_lp);
}