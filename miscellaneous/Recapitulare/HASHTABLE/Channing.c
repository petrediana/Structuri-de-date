#include "pch.h"
#include <stdio.h>
#include <malloc.h>

struct nod_lista_simpla {
	int inf;
	nod_lista_simpla *next;
};

struct hash_table {
	nod_lista_simpla **vector;
	int size;
};

int functie_hash(hash_table tabela, int cheie) {
	return cheie % tabela.size;
}

nod_lista_simpla *creare_nod(int inf, nod_lista_simpla *next) {
	nod_lista_simpla *nou = (nod_lista_simpla*)malloc(sizeof(nod_lista_simpla));

	nou->inf = inf;
	nou->next = next;

	return nou;
}

void adauga_in_lista_simpla(nod_lista_simpla **prim, int inf) {
	nod_lista_simpla *nou = creare_nod(inf, NULL);

	if ((*prim) == NULL) {
		(*prim) = nou;
	}
	else {
		nod_lista_simpla *aux = (*prim);

		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
}

void traverseaza_lista_simpla(nod_lista_simpla *prim) {
	nod_lista_simpla *aux = prim;

	while (aux) {
		printf("\nInformatia listei simple: %d", aux->inf);
		aux = aux->next;
	}
}

void dezalocare_lista_simpla(nod_lista_simpla **prim) {
	printf("\nStergere lista simpla...");
	nod_lista_simpla *aux = (*prim);

	while (aux) {
		nod_lista_simpla *temp = aux;
		aux = aux->next;

		free(temp);
	}

	(*prim) = NULL;
}

int adauga_in_hash_table(hash_table tabela, int inf) {
	int pozitie;

	if (tabela.vector != NULL) {
		pozitie = functie_hash(tabela, inf);
		adauga_in_lista_simpla(&tabela.vector[pozitie], inf);
	}

	return pozitie;
}

void traversare_hash_table(hash_table tabela) {
	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vector[i] != NULL) {
				printf("\nPozitia: %d", i);
				printf("\nTraversare element ht ->");
				traverseaza_lista_simpla(tabela.vector[i]);
			}
		}
	}
}

void dezalocare_hash_table(hash_table tabela) {
	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vector[i] != NULL) {
				printf("\nSterg elementul de pe pozitia: %d", i);
				dezalocare_lista_simpla(&tabela.vector[i]);
			}
		}
	}
}

void sterge_un_element_hash_table(hash_table tabela, int element) {
	int pozitie;
	if (tabela.vector != NULL) {
		pozitie = functie_hash(tabela, element);

		if (tabela.vector[pozitie] != NULL) {

			if (tabela.vector[pozitie]->inf == element) {
				//cazul 1: sterg primul element din lista
				printf("\n\t Primul element din lista: -> %d", tabela.vector[pozitie]->inf);
				nod_lista_simpla *aux = tabela.vector[pozitie];
				tabela.vector[pozitie] = tabela.vector[pozitie]->next;
				
				free(aux);
				return;
			}
			else {
				//cazul 2: sterg alt element care nu e primul
				nod_lista_simpla *aux = tabela.vector[pozitie];

				int count = 0;
				bool ok = false;
				while (aux->next && !ok) {
					++count;
					if (aux->next->inf == element) {
						ok = true;
						break;
					}

					aux = aux->next;
				}

				if (ok) {
					printf("\n\tSterg un element din lista: (elementul)-> %d | (pozitia in lista) -> %d", aux->next->inf, count + 1);
					nod_lista_simpla *sterge = aux->next;
					aux->next = aux->next->next;

					free(sterge);
					return;
				}
			}
		}
	}
}

void main() {
	nod_lista_simpla *prim = NULL;

	adauga_in_lista_simpla(&prim, 101);
	adauga_in_lista_simpla(&prim, 202);
	adauga_in_lista_simpla(&prim, 300);
	adauga_in_lista_simpla(&prim, 456);
	adauga_in_lista_simpla(&prim, 505);
	
	traverseaza_lista_simpla(prim);
	dezalocare_lista_simpla(&prim);
	printf("\n\n\tHash table ");

	hash_table tabela;
	tabela.size = 101;
	tabela.vector = (nod_lista_simpla**)malloc(sizeof(nod_lista_simpla*) * tabela.size);

	for (int i = 0; i < tabela.size; i++)
		tabela.vector[i] = NULL;

	adauga_in_hash_table(tabela, 101);
	adauga_in_hash_table(tabela, 202);
	adauga_in_hash_table(tabela, 303);
	adauga_in_hash_table(tabela, 300);
	adauga_in_hash_table(tabela, 456);
	adauga_in_hash_table(tabela, 505);

	traversare_hash_table(tabela);
	printf("\n\n");

	printf("\nSterg elemente din ht!!");
	sterge_un_element_hash_table(tabela, 101);
	traversare_hash_table(tabela);

	printf("\n");
	sterge_un_element_hash_table(tabela, 303);
	traversare_hash_table(tabela);

	printf("\n");
	sterge_un_element_hash_table(tabela, 505);
	traversare_hash_table(tabela);

	sterge_un_element_hash_table(tabela, 101);

	printf("\n\n");
	dezalocare_hash_table(tabela);
}

