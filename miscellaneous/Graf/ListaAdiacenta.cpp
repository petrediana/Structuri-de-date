#include "pch.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct facultate {
	int id;
	char *nume;
};
struct nod_lista_principala;

struct nod_lista_secundara {
	nod_lista_principala *inf;
	nod_lista_secundara *next;
};

struct nod_lista_principala {
	nod_lista_secundara *vecini;
	facultate inf;
	nod_lista_principala *next;
};

facultate pune_facultate(int id, const char* nume) {
	facultate f;
	f.id = id;
	f.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(f.nume, nume);

	return f;
}

nod_lista_principala *inserare_nod_lista_principala(nod_lista_principala *cap, facultate inf) {
	nod_lista_principala *nou = (nod_lista_principala*)malloc(sizeof(nod_lista_principala));
	nou->inf = inf;
	nou->next = NULL;
	nou->vecini = NULL;

	if (cap != NULL) {
		nod_lista_principala *temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}

nod_lista_secundara *inserare_nod_lista_secundara(nod_lista_secundara *cap, nod_lista_principala *inf) {
	nod_lista_secundara *nou = (nod_lista_secundara*)malloc(sizeof(nod_lista_secundara));
	nou->next = NULL;
	nou->inf = inf;

	if (cap != NULL) {
		nod_lista_secundara *temp = cap;
		while (temp->next)
			temp = temp->next;

		temp->next = nou;
		return cap;
	}
	else {
		return nou;
	}
}

nod_lista_principala *cautare_dupa_id(nod_lista_principala *cap, int id) {
	while (cap != NULL && cap->inf.id != id) {
		cap = cap->next;
	}

	return cap;
}

void inserare_arc_in_graf(nod_lista_principala *graf, int id_start, int id_stop) {
	if (graf != NULL) {
		nod_lista_principala *nod_start = cautare_dupa_id(graf, id_start);
		nod_lista_principala *nod_stop = cautare_dupa_id(graf, id_stop);

		if (nod_start != NULL && nod_stop != NULL) {
			nod_start->vecini = inserare_nod_lista_secundara(nod_start->vecini, nod_stop);
			nod_stop->vecini = inserare_nod_lista_secundara(nod_stop->vecini, nod_start);
		}
	}
}

void afisare_lista_secundara(nod_lista_secundara *cap) {
	while (cap != NULL) {
		printf("\n\t %d, %s", cap->inf->inf.id, cap->inf->inf.nume);
		cap = cap->next;
	}
}

void afisare_lista_principala(nod_lista_principala *cap) {
	while (cap != NULL) {
		printf("\nAvem urmatorii vecini pentru: %d, %s\n-> ", cap->inf.id, cap->inf.nume);
		afisare_lista_secundara(cap->vecini);

		cap = cap->next;
	}
}

int numara_noduri_in_graf(nod_lista_principala *graf) {
	int contor = 0;
	while (graf) {
		++contor;
		graf = graf->next;
	}

	return contor;
}

struct nod_lista_simpla {
	int id_fac_informatie;
	nod_lista_simpla *next;
};

void push_stiva(nod_lista_simpla **varf, int inf) {
	nod_lista_simpla *nou = (nod_lista_simpla*)malloc(sizeof(nod_lista_simpla));
	nou->id_fac_informatie = inf;
	nou->next = NULL;

	if ((*varf) == NULL) {
		(*varf) = nou;
	}
	else {
		nou->next = (*varf);
		(*varf) = nou;
	}
}

void pop_stiva(nod_lista_simpla **varf, int *inf_extrasa) {
	if ((*varf) == NULL) {
		return;
	}
	else {
		(*inf_extrasa) = (*varf)->id_fac_informatie;

		nod_lista_simpla *aux = (*varf);
		(*varf) = (*varf)->next;
		free(aux);
	}
}

void put_coada(nod_lista_simpla **prim, nod_lista_simpla **ultim, int inf) {
	nod_lista_simpla *nou = (nod_lista_simpla*)malloc(sizeof(nod_lista_simpla));
	nou->id_fac_informatie = inf;
	nou->next = NULL;

	if ((*prim) == NULL && (*ultim) == NULL) {
		(*prim) = nou;
		(*ultim) = nou;
	}
	else {
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

void get_coada(nod_lista_simpla **prim, nod_lista_simpla**ultim, int *inf_extrasa) {
	if ((*prim) != NULL) {
		(*inf_extrasa) = (*prim)->id_fac_informatie;

		nod_lista_simpla *aux = (*prim);
		(*prim) = (*prim)->next;
		free(aux);
	}

	if (*prim == NULL)
		(*ultim) = NULL;
}

void parcurgere_graf_in_adancime(nod_lista_principala *graf, int id_nod_start) {
	printf("\n\nParcurgere graf in adancime folosind stiva!!");
	if (graf != NULL) {
		int numar_noduri = numara_noduri_in_graf(graf);
		nod_lista_simpla *varf_stiva = NULL;

		int *vector_vizitat_stiva = (int*)malloc(sizeof(int) * numar_noduri);
		for (int i = 0; i < numar_noduri; i++)
			vector_vizitat_stiva[i] = 0;

		printf("\nNod de start: %d ||", id_nod_start);
		push_stiva(&varf_stiva, id_nod_start);
		vector_vizitat_stiva[id_nod_start] = 1;

		int noduri_parcurse;
		while (varf_stiva != NULL) {
			pop_stiva(&varf_stiva, &noduri_parcurse);
			printf(" => %d", noduri_parcurse);

			nod_lista_principala *nod_curent = cautare_dupa_id(graf, noduri_parcurse);
			nod_lista_secundara *p = nod_curent->vecini;

			while (p != NULL) {
				if (vector_vizitat_stiva[p->inf->inf.id] == 0) {
					push_stiva(&varf_stiva, p->inf->inf.id);
					vector_vizitat_stiva[p->inf->inf.id] = 1;
				}
				p = p->next;
			}

		}
	}
}

void parcurgere_graf_in_latime(nod_lista_principala *graf, int id_nod_inceput) {
	printf("\n\nParcurgere grafic in latime folosind coada!!");
	if (graf != NULL) {
		int numar_noduri = numara_noduri_in_graf(graf);
		nod_lista_simpla *coada_prim = NULL, *coada_ultim = NULL;

		int *vector_vizitat_coada = (int*)malloc(sizeof(int) * numar_noduri);
		for (int i = 0; i < numar_noduri; i++)
			vector_vizitat_coada[i] = 0;

		printf("\nNod de start: %d ||", id_nod_inceput);
		put_coada(&coada_prim, &coada_ultim, id_nod_inceput);
		vector_vizitat_coada[id_nod_inceput] = 1;

		int noduri_parcurse;
		while (coada_prim != NULL) {
			get_coada(&coada_prim, &coada_ultim, &noduri_parcurse);
			printf(" => %d", noduri_parcurse);

			nod_lista_principala *nod_curent = cautare_dupa_id(graf, noduri_parcurse);
			nod_lista_secundara *p = nod_curent->vecini;

			while (p != NULL) {
				if (vector_vizitat_coada[p->inf->inf.id] == 0) {
					put_coada(&coada_prim, &coada_ultim, p->inf->inf.id);
					vector_vizitat_coada[p->inf->inf.id] = 1;
				}
				p = p->next;
			}
		}
	}
}

void main() {

	facultate f1 = pune_facultate(0, "Fac0");
	facultate f2 = pune_facultate(1, "Fac1");
	facultate f3 = pune_facultate(2, "Fac2");
	facultate f4 = pune_facultate(3, "Fac3");

	facultate fs[] = { f1, f2, f3, f4 };
	nod_lista_principala *graf = NULL;

	int nr_noduri = 4;
	for (int i = 0; i < nr_noduri; i++) {
		graf = inserare_nod_lista_principala(graf, fs[i]);
	}

	printf("\n---Afisare noduri inserate in graf");
	afisare_lista_principala(graf);

	int muchii[] = { 0, 1, 0, 2, 2, 3 };
	int nr_muchii = 3;

	int x, y;
	for (int i = 0; i < nr_muchii; i++) {
		x = muchii[i * 2];
		y = muchii[i * 2 + 1];

		inserare_arc_in_graf(graf, x, y);
	}

	printf("\n\n---Afisare noduri si vecini");
	afisare_lista_principala(graf);

	parcurgere_graf_in_adancime(graf, 2);

	parcurgere_graf_in_latime(graf, 2);
}
