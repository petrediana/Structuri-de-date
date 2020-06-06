#include "pch.h"
#include <stdio.h>
#include <malloc.h>

struct nod_arbore {
	int inf;
	nod_arbore *stanga;
	nod_arbore *dreapta;
};

nod_arbore *creare_nod(int inf, nod_arbore *stanga, nod_arbore *dreapta) {
	nod_arbore *nou = (nod_arbore*)malloc(sizeof(nod_arbore));
	
	nou->inf = inf;
	nou->stanga = stanga;
	nou->dreapta = dreapta;

	return nou;
}

nod_arbore *inserare(int inf, nod_arbore *radacina) {
	nod_arbore *aux = radacina;

	if (radacina == NULL) {
		return creare_nod(inf, NULL, NULL);
	}
	else {
		while (true) {
			//verific ramura stanga
			if (inf < aux->inf) {
				if (aux->stanga == NULL) {
					aux->stanga = creare_nod(inf, NULL, NULL);
					return radacina;
				}
				else {
					aux = aux->stanga;
				}
			}
			else {
				//verific ramura dreapta
				if (inf > aux->inf) {
					if (aux->dreapta == NULL) {
						aux->dreapta = creare_nod(inf, NULL, NULL);
						return radacina;
					}
					else {
						aux = aux->dreapta;
					}
				}
				else
					return radacina;
			}
		}
	}
}

//radacina, stanga, dreapta
void traversare_PREORDINE(nod_arbore *radacina) {
	if (radacina != NULL) {
		printf("\nInformatia -> %d", radacina->inf);
		traversare_PREORDINE(radacina->stanga);
		traversare_PREORDINE(radacina->dreapta);
	}
}

//stanga, radacina, dreapta
void traversare_INORDINE(nod_arbore *radacina) {
	if (radacina != NULL) {
		traversare_INORDINE(radacina->stanga);
		printf("\nInformatia: -> %d", radacina->inf);
		traversare_INORDINE(radacina->dreapta);
	}
}

//stanga, dreapta, radacina
void traversare_POSTORDINE(nod_arbore *radacina) {
	if (radacina != NULL) {
		traversare_POSTORDINE(radacina->stanga);
		traversare_POSTORDINE(radacina->dreapta);
		printf("\nInformatia: -> %d", radacina->inf);
	}
}

void dezalocare(nod_arbore *radacina) {
	if (radacina != NULL) {
		nod_arbore *stanga = radacina->stanga;
		nod_arbore *dreapta = radacina->dreapta;
		
		printf("\nSterg informatia -> %d", radacina->inf);
		free(radacina);	
		radacina = NULL;
		
		dezalocare(stanga);
		dezalocare(dreapta);
	}
}

int maxim(int a, int b) {
	return a > b ? a : b;
}

int numara_nivel_arbore(nod_arbore *radacina) {
	if (radacina != NULL) {
		return 1 + maxim(numara_nivel_arbore(radacina->stanga), numara_nivel_arbore(radacina->dreapta));
	}
	else
		return 0;
}

void cautare_informatie_arbore(nod_arbore *radacina, int element) {
	if (radacina != NULL) {
		if (radacina->inf == element) {
			printf("\n\tElementul gasit -> %d", radacina->inf);
			return;
		}
		else {
			if (radacina->inf > element) {
				cautare_informatie_arbore(radacina->stanga, element);
			}
			else {
				cautare_informatie_arbore(radacina->dreapta, element);
			}
		}
	}
}

void conversie_la_vector(nod_arbore *radacina, int *nr, int *v) {
	if (radacina != NULL) {

		conversie_la_vector(radacina->stanga, nr, v);
		v[(*nr)++] = radacina->inf;
		conversie_la_vector(radacina->dreapta, nr, v);
	}
}

void main() {
	nod_arbore *radacina = NULL;
	
	radacina = inserare(8, radacina);
	radacina = inserare(3, radacina);
	radacina = inserare(10, radacina);
	radacina = inserare(1, radacina);
	radacina = inserare(6, radacina);
	radacina = inserare(14, radacina);


	printf("\nAfisare preordine");
	traversare_PREORDINE(radacina);
	
	printf("\n\nAfisare inordine");
	traversare_INORDINE(radacina);

	printf("\n\nAfisare postordine");
	traversare_POSTORDINE(radacina);

	printf("\n\nNumar niveluri arbore: %d", numara_nivel_arbore(radacina));

	printf("\n\nCaut elementul 6 ");
	cautare_informatie_arbore(radacina, 6);

	int *v = (int*)malloc(sizeof(int) * 6);
	int nr = 0;
	conversie_la_vector(radacina, &nr, v);

	printf("\n\nConversie la vector:");
	for (int i = 0; i < nr; i++)
		printf(" %d ", v[i]);

	printf("\n\nDezalocare arbore");
	dezalocare(radacina);
}