// Conversia unei matrice in matrice rara memorata ca lista simpla
#include "pch.h"
#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

struct Element {
	int linie;
	int coloana;
	int valoare;
};

struct Nod_LS {
	Element *info;
	Nod_LS *next;
};

int **citire_Matrice(int *n, int *m) {
	printf("\nNumar de linii: "); scanf("%d", n);
	printf("Numar de coloane: "); scanf("%d", m);

	int **matrice = (int**)malloc(sizeof(int*) * (*n));
	for (int i = 0; i < (*n); i++) {
		matrice[i] = (int*)malloc(sizeof(int) * (*m));
		for (int j = 0; j < (*m); j++)
			scanf("%d", &matrice[i][j]);
	}

	return matrice;
}

void afisare_Matrice(int **matrice, int NRlinii, int NRcoloane) {
	printf("\n\n\tAfisare matrice rara:\n");
	for (int i = 0; i < NRlinii; i++) {
		for (int j = 0; j < NRcoloane; j++)
			printf("%d ", matrice[i][j]);
		printf("\n");
	}
}
//returnez un element din matrice
//dat de [x][y]
int element_pozitie_x_y(Nod_LS *prim, int x, int y) {
	Nod_LS *temp = prim;
	
	while (temp) {
		if (temp->info->linie == x && temp->info->coloana == y)
			return temp->info->valoare;
		else
			temp = temp->next;
	}

	return -1;//caz in care nu gasesc elementul
}

void afisare_matrice_LS(Nod_LS *cap, int Nr_linii, int Nr_coloane) {
	printf("\n\tAfisare matrice rara din lista\n");
	for (int i = 0; i < Nr_linii; i++) {
		for (int j = 0; j < Nr_coloane; j++)
			printf("%d    ", element_pozitie_x_y(cap, i, j));
		printf("\n");
	}
}

void inserare_LS(Nod_LS **prim, int val, int linie, int coloana) {
	Nod_LS *nou = (Nod_LS*)malloc(sizeof(Nod_LS));
	nou->info = (Element*)malloc(sizeof(Element));
	nou->info->coloana = coloana;
	nou->info->linie = linie;
	nou->info->valoare = val;
	nou->next = NULL;

	if ((*prim) == NULL) {
		(*prim) = nou;
	}
	else {
		Nod_LS *temp = (*prim);
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void traversare_LS(Nod_LS *prim) {
	printf("\n\tTraversare lista simpla");
	Nod_LS *temp = prim;
	while (temp) {
		printf("\nElementul: [%d][%d] = %d", temp->info->linie, temp->info->coloana,
			temp->info->valoare);
		temp = temp->next;
	}
}

void dezalocare_LS(Nod_LS **prim) {
	Nod_LS *temp = (*prim);
	while (temp) {
		Nod_LS *temp2 = temp;
		temp = temp->next;
		free(temp2->info);
		free(temp2);
	}
}

int main()
{
	Nod_LS *cap = NULL;
	int n, m;
	int **matrice = citire_Matrice(&n, &m);
	afisare_Matrice(matrice, n, m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (matrice[i][j] != 0) {
				inserare_LS(&cap, matrice[i][j], i, j);
			}
		}
	}

	printf("\n\n------");
	traversare_LS(cap);
	
	printf("\n\n------");
	afisare_matrice_LS(cap, n, m);

	dezalocare_LS(&cap);
}

