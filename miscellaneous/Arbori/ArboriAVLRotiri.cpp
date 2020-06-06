#include "pch.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct nod_arbore_binar {
	int inf;
	nod_arbore_binar *stanga;
	nod_arbore_binar *dreapta;
};

nod_arbore_binar *creare_nod(int inf, nod_arbore_binar *stanga, nod_arbore_binar *dreapta) {
	nod_arbore_binar *nou = (nod_arbore_binar*)malloc(sizeof(nod_arbore_binar));

	nou->inf = inf;
	nou->stanga = stanga;
	nou->dreapta = dreapta;

	return nou;
}

nod_arbore_binar *inserare_arbore(nod_arbore_binar *radacina, int inf) {
	nod_arbore_binar *aux = radacina;

	if (radacina == NULL) {
		return creare_nod(inf, NULL, NULL);
	}
	else {
		while (true) {
			//ma duc la stanga si verific
			if (aux->inf > inf) {
				if (aux->stanga == NULL) {
					aux->stanga = creare_nod(inf, NULL, NULL);
					return radacina;
				}
				else {
					aux = aux->stanga;
				}
			}
			else {
				//ma duc la dreapta si verific
				if (aux->inf < inf) {
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
void traversare_PREORDINE(nod_arbore_binar *radacina) {
	if (radacina != NULL) {
		printf("\nInformatia: %d", radacina->inf);

		traversare_PREORDINE(radacina->stanga);
		traversare_PREORDINE(radacina->dreapta);
	}
}

//stanga, radacina, dreapta
void traversare_inordine(nod_arbore_binar *radacina) {
	if (radacina != NULL) {
		traversare_inordine(radacina->stanga);
		printf("\nInformatia: %d", radacina->inf);
		traversare_inordine(radacina->dreapta);
	}
}

//stanga, dreapta, radacina
void traversare_POSTORDINE(nod_arbore_binar *radacina) {
	if (radacina != NULL) {
		traversare_POSTORDINE(radacina->stanga);
		traversare_POSTORDINE(radacina->dreapta);
		printf("\nInformatia: %d", radacina->inf);
	}
}

int maxim(int a, int b) {
	return a > b ? a : b;
}

int calculeaza_inaltime_arbore(nod_arbore_binar *radacina) {
	if (radacina != NULL) {
		return 1 + maxim(calculeaza_inaltime_arbore(radacina->stanga), calculeaza_inaltime_arbore(radacina->dreapta));
	}
	else
		return 0;
}

void dezalocare_arbore(nod_arbore_binar *radacina) {
	if (radacina != NULL) {
		nod_arbore_binar *stanga = radacina->stanga;
		nod_arbore_binar *dreapta = radacina->dreapta;

		free(radacina);

		dezalocare_arbore(stanga);
		dezalocare_arbore(dreapta);
	}
}

int cautare_element(nod_arbore_binar *radacina, int element) {
	if (radacina->inf == element)
		return element;
	else {
		if (radacina->inf < element)
			cautare_element(radacina->dreapta, element);
		else {
			if (radacina->inf > element)
				cautare_element(radacina->stanga, element);
		}
	}
}

nod_arbore_binar *rotire_DREAPTA(nod_arbore_binar *radacina) {
	printf("\nRotire dreapta");
	nod_arbore_binar *rad_noua = radacina->stanga;
	radacina->stanga = rad_noua->dreapta;
	rad_noua->dreapta = radacina;

	radacina = rad_noua;
	return radacina;
}

void main() {
	nod_arbore_binar *radacina = NULL;

	radacina = inserare_arbore(radacina, 20);
	radacina = inserare_arbore(radacina, 15);
	radacina = inserare_arbore(radacina, 25);
	radacina = inserare_arbore(radacina, 16);

	printf("\nTraversare preordine");
	traversare_PREORDINE(radacina);

	printf("\n\nTraversare inordine");
	traversare_inordine(radacina);

	printf("\n\nTraversare postordine");
	traversare_POSTORDINE(radacina);

	printf("\n\nInaltimea arborelui este: %d", calculeaza_inaltime_arbore(radacina));

	printf("\nElement cautat: %d", cautare_element(radacina, 16));
	
	dezalocare_arbore(radacina);
}