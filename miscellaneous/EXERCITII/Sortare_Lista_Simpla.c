//#include "pch.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

//SORTARE ELEMENTE LISTA SIMPLA
// -> select sort
struct Masina {
	char *model;
	int cod;
	float pret;
	int caiPutere;
};

struct Nod_LS {
	Masina *info;
	Nod_LS *next;
};

Masina *creare_masina(const char *mo, int c, float p, int cp) {
	Masina *m = (Masina*)malloc(sizeof(Masina));
	
	m->model = (char*)malloc(sizeof(char) * (strlen(mo) + 1));
	strcpy(m->model, mo);
	m->cod = c;
	m->pret = p;
	m->caiPutere = cp;

	return m;
}

void afisare_masina(Masina *m) {
	printf("\nModel: %s, Cod: %d, Pret: %5.3f, CaiPutere: %d",
		m->model, m->cod, m->pret, m->caiPutere);
}

Nod_LS *inserare_nod(Masina *m, Nod_LS *next) {
	Nod_LS *nou = (Nod_LS*)malloc(sizeof(Nod_LS));
	nou->info = m;
	nou->next = next;

	return nou;
}

void inserare_lista(Nod_LS **prim, Nod_LS **ultim, Masina *informatie) {
	Nod_LS *nou = inserare_nod(informatie, NULL);

	if ((*prim) == NULL && (*ultim) == NULL) {
		//daca lista este vida
		(*prim) = nou;
		(*ultim) = nou;
	}
	else {
		//am deja elemente in lista
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

void traversare_lista(Nod_LS *prim) {
	Nod_LS *temp = prim;
	while (temp) {
		afisare_masina(temp->info);
		temp = temp->next;
	}
}

void dezalocare_lista(Nod_LS **prim) {
	Nod_LS *temp = (*prim);
	while (temp) {
		Nod_LS *temp2 = temp;
		temp = temp->next;

		free(temp2->info->model);
		free(temp2->info);
		free(temp2);
		
	}
}

int numar_elemente_LS(Nod_LS *prim) {
	int nr = 0;
	Nod_LS *temp = prim;
	while(temp) {
		nr++;
		temp = temp->next;
	}

	return nr;
}

Nod_LS *adresa_nod_cu_pozitie_data(Nod_LS *prim, int index) {
	int poz = 0;
	Nod_LS *temp = prim;
	while (temp) {
		if (index == poz)
			return temp;
		temp = temp->next;
		poz++;
	}
	return NULL;
}

void sortare_LS(Nod_LS *cap) {
	int n = numar_elemente_LS(cap);

	for (int i = 0; i < n - 1; i++) {
		Nod_LS* temp1 = adresa_nod_cu_pozitie_data(cap, i);
		for (int j = i + 1; j < n; j++) {
			Nod_LS* temp2 = adresa_nod_cu_pozitie_data(cap, j);
			if (temp1->info->caiPutere > temp2->info->caiPutere){
				Masina *aux = temp1->info;
				temp1->info = temp2->info;
				temp2->info = aux;
			}
		}
	}
}

int main()
{
	Masina *m5 = creare_masina("Matiz", 10, 5.000, 47);
	Masina *m2 = creare_masina("Suzuki", 5, 18.000, 122); 
	Masina *m1 = creare_masina("Mustang", 13, 36.000, 170);
	Masina *m3 = creare_masina("Renault", 11, 16.000, 80);
	Masina *m4 = creare_masina("Vitara", 50, 12.000, 65);

	Nod_LS *cap = NULL;
	Nod_LS *coada = NULL;

	inserare_lista(&cap, &coada, m1);
	inserare_lista(&cap, &coada, m2);
	inserare_lista(&cap, &coada, m3);
	inserare_lista(&cap, &coada, m4);
	inserare_lista(&cap, &coada, m5);
	printf("\nAfisare elemente lista:");
	traversare_lista(cap);

	printf("\n\nSORTARE LISTA DUPA CAI PUTERE");
	sortare_LS(cap);
	traversare_lista(cap);

	dezalocare_lista(&cap);
	return 0;
}
