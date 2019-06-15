#include "pch.h"
#include <stdio.h>
#include <malloc.h>

struct pInt {
	int p;
};

struct hash_table {
	pInt **vector;
	int size;
};

int functie_hash(hash_table tabela, int cheie) {
	return cheie % tabela.size;
}

int adauga_ht(hash_table tabela, pInt *p) {
	int pozitie;

	if (tabela.vector != NULL) {
		pozitie = functie_hash(tabela, p->p);

		if (tabela.vector[pozitie] == NULL) {
			tabela.vector[pozitie] = p;
		}
		else {
			int index = 1;
			while (pozitie + index < tabela.size) {
				if (tabela.vector[pozitie + index] == NULL) {
					pozitie += index;
					tabela.vector[pozitie] = p;
					break;
				}
				++index;
			}
		}
	}

	return pozitie;
}

void afisare_ht(hash_table tabela) {
	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vector[i] != NULL) {
				printf("\nPozitia: %d", i);
				printf("\nInformatia -> %d", tabela.vector[i]->p);
			}
		}
	}
}

void dezalocare(hash_table table) {
	if (table.vector != NULL) {
		for (int i = 0; i < table.size; i++) {
			if (table.vector[i] != NULL) {
				free(table.vector[i]);
			}
		}
		free(table.vector);
	}
}

int sterge_element(hash_table table, pInt *element) {
	int pozitie;

	if (table.vector != NULL) {
		pozitie = functie_hash(table, element->p);
		if (table.vector[pozitie]->p == element->p && table.vector[pozitie] != NULL) {
			free(table.vector[pozitie]);
			table.vector[pozitie] = NULL;
		}
		else {
			int index = 1;
			while (pozitie + index < table.size) {
				if (table.vector[pozitie + index]->p == element->p && table.vector[pozitie] != NULL) {
					pozitie += index;
					free(table.vector[pozitie]);
					table.vector[pozitie] = NULL;
					break;
				}
				++index;
			}
		}
	}

	return pozitie;
}

void main() {
	hash_table tabela;
	tabela.size = 101;
	tabela.vector = (pInt**)malloc(sizeof(pInt*) * tabela.size);

	for (int i = 0; i < tabela.size; i++)
		tabela.vector[i] = NULL;

	pInt *p1, *p2, *p3, *p4, *p5;

	p1 = (pInt*)malloc(sizeof(pInt));
	p2 = (pInt*)malloc(sizeof(pInt));
	p3 = (pInt*)malloc(sizeof(pInt));
	p4 = (pInt*)malloc(sizeof(pInt));
	p5 = (pInt*)malloc(sizeof(pInt));

	p1->p = 101;
	p2->p = 202;
	p3->p = 306;
	p4->p = 404;
	p5->p = 200;

	adauga_ht(tabela, p1);
	adauga_ht(tabela, p2);
	adauga_ht(tabela, p3);
	adauga_ht(tabela, p4);
	adauga_ht(tabela, p5);

	afisare_ht(tabela);

	printf("\n\n");
	sterge_element(tabela, p4);
	afisare_ht(tabela);



	dezalocare(tabela);
}