#include "pch.h"
#include <stdio.h>
#include <malloc.h>

struct nod_lista_dubla_circulara {
	int inf;
	nod_lista_dubla_circulara *next;
	nod_lista_dubla_circulara *prev;
};

nod_lista_dubla_circulara *creare_nod(int inf, nod_lista_dubla_circulara *next, nod_lista_dubla_circulara *prev) {
	nod_lista_dubla_circulara *nou = (nod_lista_dubla_circulara*)malloc(sizeof(nod_lista_dubla_circulara));

	nou->inf = inf;
	nou->next = next;
	nou->prev = prev;

	return nou;
}

void adauga_element(nod_lista_dubla_circulara **prim, nod_lista_dubla_circulara **ultim, int inf) {
	nod_lista_dubla_circulara *nou = creare_nod(inf, NULL, NULL);

	if ((*prim) == NULL && (*ultim) == NULL) {
		(*prim) = nou;
		(*prim)->next = (*prim);
		(*prim)->prev = (*prim);
		(*ultim) = (*prim);
	}
	else {
		(*ultim)->next = nou;
		nou->next = (*prim);
		nou->prev = (*ultim);
		(*ultim) = nou;
	}
}

void traversare_normala(nod_lista_dubla_circulara *prim) {
	nod_lista_dubla_circulara *aux = prim;

	while (aux->next != prim) {
		printf("\nInformatia: %d", aux->inf);
		aux = aux->next;
	}
	printf("\nInformatia: %d", aux->inf);
}

void traversare_inversa(nod_lista_dubla_circulara *prim, nod_lista_dubla_circulara *ultim) {
	nod_lista_dubla_circulara *aux = ultim;

	while (aux != prim) {
		printf("\nInformatia: %d", aux->inf);
		aux = aux->prev;
	}
	printf("\nInformatia: %d", aux->inf);
}

void dezalocare(nod_lista_dubla_circulara **prim, nod_lista_dubla_circulara **ultim) {
	nod_lista_dubla_circulara *aux = (*prim);

	while (aux != (*ultim)) {
		nod_lista_dubla_circulara *temp = aux;
		aux = aux->next;

		free(temp);
	}

	free(aux);
	(*prim) = NULL;
	(*ultim) = NULL;
}

void sterge_element(nod_lista_dubla_circulara **prim, nod_lista_dubla_circulara **ultim, int element) {
	if ((*prim) != NULL && (*ultim) != NULL) {

		//cazul 1: elementul este la inceput
		if ((*prim)->inf == element) {
			printf("\nSe sterge -> %d", (*prim)->inf);
			nod_lista_dubla_circulara *sterge = (*prim);
			(*prim) = (*prim)->next;
			(*ultim)->next = (*prim);
			(*prim)->prev = (*ultim);

			free(sterge);
			return;
		}

		//cazul 2: elementul este ultimul
		if ((*ultim)->inf == element) {
			printf("\nSe sterge -> %d", (*ultim)->inf);

			nod_lista_dubla_circulara *sterge = (*ultim);
			(*ultim) = (*ultim)->prev;
			(*ultim)->next = (*prim);
			(*prim)->prev = (*ultim);

			free(sterge);
			return;
		}

		//elementul este la mijloc
		nod_lista_dubla_circulara *aux = (*prim)->next;
		while (aux != (*ultim)) {
			if (aux->inf == element) {
				printf("\nSe sterge -> %d", (aux)->inf);
				
				nod_lista_dubla_circulara *sterge = aux;
				aux->prev->next = aux->next;
				aux->next->prev = aux->prev;

				free(sterge);
				return;

			}
			aux = aux->next;
		}
	}
	else {
		printf("\nLista vida!!");
	}
}

void main() {
	nod_lista_dubla_circulara *prim = NULL;
	nod_lista_dubla_circulara *ultim = NULL;

	adauga_element(&prim, &ultim, 1);
	adauga_element(&prim, &ultim, 2);
	adauga_element(&prim, &ultim, 3);
	adauga_element(&prim, &ultim, 4);
	adauga_element(&prim, &ultim, 5);

	printf("\nTraversare Normala");
	traversare_normala(prim);

	printf("\n\nTraversare inversa");
	traversare_inversa(prim, ultim);

	printf("\n\nSterg primul element");
	sterge_element(&prim, &ultim, 1);
	traversare_normala(prim);

	printf("\n\nSterg primul element");
	sterge_element(&prim, &ultim, 5);
	traversare_normala(prim);

	printf("\n\nSterg un element");
	sterge_element(&prim, &ultim, 3);
	traversare_normala(prim);

	dezalocare(&prim, &ultim);
}
