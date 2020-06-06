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

int get_coada(nod_coada **prim, nod_coada **ultim, int *extras) {
	if ((*prim) == NULL && (*ultim) == NULL)
		return -1;
	else {
		(*extras) = (*prim)->inf;
		
		nod_coada *temp = (*prim);
		(*prim) = (*prim)->next;

		free(temp);

		if ((*prim) == NULL)
			(*ultim) = NULL;
		return 0;
	}
}

void traversare_coada(nod_coada *prim) {
	nod_coada *aux = prim;

	while (aux) {
		printf("\nInformatia: %d", aux->inf);
		aux = aux->next;
	}
}

void main() {
	/*nod_stiva *varf = NULL;

	push_stiva(&varf, 1);
	push_stiva(&varf, 2);
	push_stiva(&varf, 3);

	printf("\n--Traversare stiva");
	traversare_stiva(varf);

	printf("\nExtrag elementele din stiva -> ");
	int extras;
	while (pop(&varf, &extras) != -1)
		printf(" %d", extras);


	nod_coada *prim = NULL;
	nod_coada *ultim = NULL;

	put_coada(&prim, &ultim, 1);
	put_coada(&prim, &ultim, 2);
	put_coada(&prim, &ultim, 3);

	printf("\n\n--Traversare coada");
	traversare_coada(prim);

	int extras2;
	printf("\nExtrag elementele din coada -> ");
	while (get_coada(&prim, &ultim, &extras2) != -1) {
		printf(" %d", extras2);
	}*/


	FILE *pFile = fopen("Date.txt", "r");
	
	int nr_noduri;
	int nr_arce;

	if (pFile) {
		fscanf(pFile, "%d%d", &nr_noduri, &nr_arce);
		printf("\nAm citit %d nr noduri, %d nr arce", nr_noduri, nr_arce);

		int **matrice = (int**)malloc(sizeof(int*) * nr_noduri);
		for (int i = 1; i <= nr_noduri; i++)
			matrice[i] = (int*)malloc(sizeof(int));

		for (int i = 1; i <= nr_noduri; i++)
			for (int j = 1; j <= nr_noduri; j++) {
				matrice[i][j] = 0;
			}
		
		int x, y;
		for (int i = 0; i < nr_arce; i++) {
			fscanf(pFile, "%d%d", &x, &y);
			printf("\n %d -> %d", x, y);

			matrice[x][y] = 1;
			matrice[y][x] = 1;
		}

		/*printf("\nMatricea de adiacenta\n");
		for (int i = 1; i <= nr_noduri; i++) {
			for (int j = 1; j <= nr_noduri; j++) {
				printf("%d ", matrice[i][j]);
			}
			printf("\n");
		}*/


		/*int *vizitat_coada;
		vizitat_coada = (int*)malloc(sizeof(int) * nr_noduri);
		for (int i = 1; i <= nr_noduri; i++)
			vizitat_coada[i] = 0;*/

		

		/*for (int i = 1; i <= nr_noduri; i++)
			free(matrice[i]);
		free(matrice);*/
	}

	//fclose(pFile);
}