#include "pch.h"
#include <stdio.h>
#include <malloc.h>

struct nod_lista_simpla_circulara {
	int inf;
	nod_lista_simpla_circulara *next;
};

nod_lista_simpla_circulara *creare_nod(int inf, nod_lista_simpla_circulara *next) {
	nod_lista_simpla_circulara *nou = (nod_lista_simpla_circulara*)malloc(sizeof(nod_lista_simpla_circulara));

	nou->inf = inf;
	nou->next = next;

	return nou;
}

void inserare_nod_lsc(nod_lista_simpla_circulara **prim, nod_lista_simpla_circulara **ultim, int inf) {
	nod_lista_simpla_circulara *nou = creare_nod(inf, NULL);

	if ((*prim) == NULL && (*ultim) == NULL) {
		(*prim) = nou;
		(*prim)->next = (*prim);
		(*ultim) = (*prim);
	}
	else {
		(*ultim)->next = nou;
		nou->next = (*prim);
		(*ultim) = nou;
	}
}

void traversare(nod_lista_simpla_circulara *prim) {
	nod_lista_simpla_circulara *aux = prim;

	while (aux->next != prim) {
		printf("\nInformatia: %d", aux->inf);
		aux = aux->next;
	}
	printf("\nInformatia: %d", aux->inf);
}

void dezalocare(nod_lista_simpla_circulara **prim, nod_lista_simpla_circulara **ultim) {
	nod_lista_simpla_circulara *aux = (*prim);

	while (aux != (*ultim)) {
		nod_lista_simpla_circulara *temp = aux;
		aux = aux->next;

		free(temp);
	}

	free(aux);
	(*prim) = NULL;
	(*ultim) = NULL;
}

void sterge_element_lsc(nod_lista_simpla_circulara **prim, nod_lista_simpla_circulara **ultim, int element) {
	if ((*prim) != NULL && (*ultim) != NULL) {

		//cazul 1: elementul este primul
		if ((*prim)->inf == element) {
			printf("\nSterg acest element: %d", (*prim)->inf);
			
			nod_lista_simpla_circulara *aux = (*prim);
			(*prim) = (*prim)->next;
			(*ultim)->next = (*prim);

			free(aux);
			return;
		}

		//cazul 2: elementul este ultimul
		if ((*ultim)->inf == element) {
			printf("\nSterg acest element: %d", (*ultim)->inf);

			nod_lista_simpla_circulara *aux = (*prim), *sters = (*ultim);
			while (aux->next != (*ultim))
				aux = aux->next;
					   
			aux->next = (*prim);
			(*ultim) = aux;

			free(sters);
			return;
		}

		//cazul 3: elementul sters e pe la mijloc
		nod_lista_simpla_circulara *aux = (*prim);
		while (aux->next->inf != element)
			aux = aux->next;

		printf("\nSterg acest element: %d", aux->next->inf);

		nod_lista_simpla_circulara *sters = aux->next;
		aux->next= aux->next->next;
		
		free(sters);
		return;
	}
	else {
		printf("\nLista vida!!");
	}
}

void main() {
	nod_lista_simpla_circulara *prim = NULL;
	nod_lista_simpla_circulara *ultim = NULL;

	inserare_nod_lsc(&prim, &ultim, 1);
	inserare_nod_lsc(&prim, &ultim, 2);
	inserare_nod_lsc(&prim, &ultim, 3);
	inserare_nod_lsc(&prim, &ultim, 4);
	inserare_nod_lsc(&prim, &ultim, 5);

	traversare(prim);

	printf("\n\nSterg primul element");
	sterge_element_lsc(&prim, &ultim, 1);
	traversare(prim);

	printf("\n\nSterg ultimul element");
	sterge_element_lsc(&prim, &ultim, 5);
	traversare(prim);

	printf("\n\nSterg un element");
	sterge_element_lsc(&prim, &ultim, 3);
	traversare(prim);

	dezalocare(&prim, &ultim);
}

