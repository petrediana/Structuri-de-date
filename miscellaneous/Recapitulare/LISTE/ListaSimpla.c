#include "pch.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct nod_lista_simpla {
	int inf;
	struct nod_lista_simpla *next;
};

nod_lista_simpla *creare_nod(int inf, nod_lista_simpla *next) {
	nod_lista_simpla *nou = (nod_lista_simpla*)malloc(sizeof(nod_lista_simpla));

	nou->inf = inf;
	nou->next = next;

	return nou;
}

nod_lista_simpla *inserare_inceput(nod_lista_simpla *cap, int inf) {
	return creare_nod(inf, cap);
}

nod_lista_simpla *inserare_sfarsit(nod_lista_simpla *cap, int inf) {
	nod_lista_simpla *nou = creare_nod(inf, NULL);

	if (cap == NULL) {
		cap = nou;
	}
	else {
		nod_lista_simpla *aux = cap;
		while (aux->next) {
			aux = aux->next;
		}

		aux->next = nou;
	}

	return cap;
}

void afisare_lista(nod_lista_simpla *cap) {
	nod_lista_simpla *temp = cap;

	while (temp) {
		printf("\nInformatie: %d", temp->inf);
		temp = temp->next;
	}
}

void dezalocare_lista(nod_lista_simpla **cap) {
	while ((*cap)) {
		nod_lista_simpla *aux = (*cap);
		(*cap) = (*cap)->next;

		printf("\nSe sterge: %d", aux->inf);
		free(aux);
	}
}

void sterge_un_element(nod_lista_simpla **cap, int element, int *salvat) {
	if ((*cap) != NULL) {
		nod_lista_simpla *aux = (*cap);

		//sunt pe primul element
		if (aux->inf == element) {
			nod_lista_simpla *sters = aux;
			(*salvat) = aux->inf;
			(*cap) = (*cap)->next;

			free(sters);
		}
		else {

			while (aux) {
				if (aux->next->inf == element) {
					(*salvat) = aux->next->inf;

					nod_lista_simpla *sters = aux->next;
					aux->next = aux->next->next;
					free(sters);
					return;
				}
				aux = aux->next;
			}
		}
	}
	else {
		printf("\nLista este vida!");
	}
}

int main() {
	nod_lista_simpla *cap = (nod_lista_simpla*)malloc(sizeof(nod_lista_simpla));
	cap = NULL;

	cap = inserare_inceput(cap, 1);
	cap = inserare_inceput(cap, 2);
	cap = inserare_inceput(cap, 3);
	cap = inserare_inceput(cap, 4);

	cap = inserare_sfarsit(cap, 5);
	cap = inserare_sfarsit(cap, 6);
	cap = inserare_sfarsit(cap, 7);
	cap = inserare_sfarsit(cap, 8);

	printf("\n");
	afisare_lista(cap);


	int salveaza;
	sterge_un_element(&cap, 8, &salveaza);
	printf("\n S-a sters: %d", salveaza);

	printf("\n");
	afisare_lista(cap);

	dezalocare_lista(&cap);
}

