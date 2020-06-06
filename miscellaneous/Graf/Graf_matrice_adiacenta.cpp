#include "pch.h"
#include<stdio.h>
#include<malloc.h>

struct nod_stiva {
	int inf;
	nod_stiva *next;
};

struct nod_coada {
	int inf;
	nod_coada *next;
};

void push_stiva(nod_stiva **varf, int inf) {
	nod_stiva *nou = (nod_stiva*)malloc(sizeof(nod_stiva));
	nou->inf = inf;
	nou->next = NULL;

	if ((*varf) == NULL) {
		(*varf) = nou;
	}
	else {
		nou->next = (*varf);
		(*varf) = nou;
	}
}

int pop(nod_stiva **varf, int *extras) {
	if ((*varf) != NULL) {
		(*extras) = (*varf)->inf;

		nod_stiva *aux = (*varf);
		(*varf) = (*varf)->next;

		free(aux);
		return 1;
	}
	else return -1;
}

void traversare_stiva(nod_stiva *varf) {
	nod_stiva *aux = varf;
	while (aux) {
		printf("\nInformatia: %d", aux->inf);
		aux = aux->next;
	}
}

void put_coada(nod_coada **prim, nod_coada **ultim, int inf) {
	nod_coada *nou = (nod_coada*)malloc(sizeof(nod_coada));
	nou->inf = inf;
	nou->next = NULL;

	if ((*prim) == NULL && (*ultim) == NULL) {
		(*prim) = nou;
		(*ultim) = (*prim);
	}
	else {
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

void get_coada(nod_coada **prim, nod_coada **ultim, int *extras) {
	if ((*prim) != NULL && (*ultim) != NULL) {
		(*extras) = (*prim)->inf;

		nod_coada *aux = (*prim);
		(*prim) = (*prim)->next;
		free(aux);
	}

	if (*prim == NULL)
		*ultim = NULL;
}

void traversare_coada(nod_coada *prim) {
	nod_coada *aux = prim;

	while (aux) {
		printf("\nInformatia: %d", aux->inf);
		aux = aux->next;
	}
}

void main() {
	int nr_arce = 4;
	int nr_noduri = 4;
	
	int **matrice_adiacenta = (int**)malloc(sizeof(int*) *nr_noduri);
	for (int i = 0; i < nr_noduri; i++)
		matrice_adiacenta[i] = (int*)malloc(sizeof(int) * nr_noduri);

	for (int i = 0; i < nr_noduri; i++)
		for (int j = 0; j < nr_noduri; j++)
			matrice_adiacenta[i][j] = 0;

	int x, y;
	/*for (int i = 0; i < nr_arce; i++) {
		printf("\nNod inceput: "); scanf("%d", &x);
		printf("\nNod sfarsit: "); scanf("%d", &y);

		matrice_adiacenta[x - 1][y - 1] = 1;
		matrice_adiacenta[y - 1][x - 1] = 1;
	}*/

	int muchii[] = { 1, 2, 1, 3, 1, 4, 4, 3 };
	for (int i = 0; i < nr_arce; i++) {
		x = muchii[i * 2];
		y = muchii[i * 2 + 1];

		matrice_adiacenta[x - 1][y - 1] = 1;
		matrice_adiacenta[y - 1][x - 1] = 1;

	}

	printf("\nMatricea de adiacenta a grafului\n");
	for (int i = 0; i < nr_noduri; i++) {
		for (int j = 0; j < nr_noduri; j++)
			printf("%d ", matrice_adiacenta[i][j]);
		printf("\n");
	}

	int *vizitat_coada = (int*)malloc(sizeof(int) * nr_noduri);
	for (int i = 0; i < nr_noduri; i++)
		vizitat_coada[i] = 0;

	nod_coada *prim = NULL;
	nod_coada *ultim = NULL;

	int nod_inceput_coada;
	printf("\nDe la ce nod parcurg in latime?: -> ");
	scanf("%d", &nod_inceput_coada);

	put_coada(&prim, &ultim, nod_inceput_coada - 1);
	vizitat_coada[nod_inceput_coada - 1] = 1;

	printf("Parcurgere in latime de la nodul: %d||", nod_inceput_coada - 1);
	while (prim != NULL) {
		get_coada(&prim, &ultim, &nod_inceput_coada);
		printf(" => %d", nod_inceput_coada);

		for (int i = 0; i < nr_noduri; i++) {
			if (matrice_adiacenta[nod_inceput_coada][i] == 1 && vizitat_coada[i] == 0) {
				put_coada(&prim, &ultim, i);
				vizitat_coada[i] = 1;
			}
		}
	}

	int *vizitat_stiva = (int*)malloc(sizeof(int) * nr_noduri);
	for (int i = 0; i < nr_noduri; i++)
		vizitat_stiva[i] = 0;

	nod_stiva *varf = NULL;
	
	int nod_inceput_stiva;
	printf("\n\nDe la ce nod parcurg in adancime?: ");
	scanf("%d", &nod_inceput_stiva);

	printf("Incep sa parcug in adancime de la nodul: %d||", nod_inceput_stiva - 1);
	push_stiva(&varf, nod_inceput_stiva - 1);
	vizitat_stiva[nod_inceput_stiva - 1] = 1;

	while (varf != NULL) {
		pop(&varf, &nod_inceput_stiva);
		printf(" => %d", nod_inceput_stiva);

		for (int i = 0; i < nr_noduri; i++) {
			if (matrice_adiacenta[nod_inceput_stiva][i] == 1 && vizitat_stiva[i] == 0) {
				push_stiva(&varf, i);
				vizitat_stiva[i] = 1;
			}
		}
	}


	for (int i = 0; i < nr_noduri; i++)
		free(matrice_adiacenta[i]);
	free(matrice_adiacenta);

	free(vizitat_coada);
	free(vizitat_stiva);
}