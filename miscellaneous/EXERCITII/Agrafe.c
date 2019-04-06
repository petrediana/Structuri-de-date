#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Agrafa {
	int cod_agrafa;
	int dimensiune;
	char *culoare;
};

struct CutieAgrafe {
	int cod_cutie;
	int numarAgrafe;
	Agrafa *agrafe;
};

//LSC  = lista simpla circulara
struct Nod_LSC {
	CutieAgrafe info;
	Nod_LSC *next;
};

Agrafa creare_agrafa(int cod, int dim, const char *culoare) {
	Agrafa a;
	a.cod_agrafa = cod;
	a.dimensiune = dim;
	a.culoare = (char*)malloc(sizeof(char) * (strlen(culoare) + 1));
	strcpy(a.culoare, culoare);

	return a;
}

Agrafa copiere_agrafa(Agrafa deCopiat) {
	Agrafa a;
	a.cod_agrafa = deCopiat.cod_agrafa;
	a.dimensiune = deCopiat.dimensiune;
	a.culoare = (char*)malloc(sizeof(char) * (strlen(deCopiat.culoare) + 1));
	strcpy(a.culoare, deCopiat.culoare);

	return a;
}

void afisare_agrafa(Agrafa a) {
	printf("\nCodAgrafa: %d, DimensiuneAgrafa: %d, CuloareAgrafa: %s", a.cod_agrafa, a.dimensiune,
		a.culoare);
	
}

CutieAgrafe creare_cutieAgrafe(int cod, int nr_ag, Agrafa *a) {
	CutieAgrafe ca;
	ca.cod_cutie = cod;
	ca.numarAgrafe = nr_ag;
	
	ca.agrafe = (Agrafa*)malloc(sizeof(Agrafa) * ca.numarAgrafe);
	for (int i = 0; i < ca.numarAgrafe; i++)
		ca.agrafe[i] = copiere_agrafa(a[i]);

	return ca;
}

CutieAgrafe copiere_CutieAgrafe(CutieAgrafe deCopiat) {
	CutieAgrafe ca;
	ca.cod_cutie = deCopiat.cod_cutie;
	ca.numarAgrafe = deCopiat.numarAgrafe;

	ca.agrafe = (Agrafa*)malloc(sizeof(Agrafa) * ca.numarAgrafe);
	for (int i = 0; i < ca.numarAgrafe; i++)
		ca.agrafe[i] = copiere_agrafa(deCopiat.agrafe[i]);

	return ca;
}

void afisare_CutieAgrafe(CutieAgrafe ca) {
	printf("\nCodCutie: %d, Dimensiune: %d, Agrafe: ", ca.cod_cutie, ca.numarAgrafe);
	for (int i = 0; i < ca.numarAgrafe; i++)
		afisare_agrafa(ca.agrafe[i]);
	printf("\n");
}

Nod_LSC *creare_Nod(CutieAgrafe ca) {
	Nod_LSC *nou = (Nod_LSC*)malloc(sizeof(Nod_LSC));
	nou->info = copiere_CutieAgrafe(ca);
	nou->next = NULL;

	return nou;
}

void inserare_in_LSC(Nod_LSC **prim, Nod_LSC **ultim, CutieAgrafe ca) {
	Nod_LSC *nou = creare_Nod(ca);

	if ((*prim) == NULL && (*ultim) == NULL) {
		//la inceput lista este vida
		nou->next = nou; 
		(*prim) = nou;
		(*ultim) = nou;
	}
	else {
		//exista deja elemente in LSC
		nou->next = (*prim);
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

void traversare_LSC(Nod_LSC *prim) {
	Nod_LSC *temp = prim;
	while (temp->next != prim) {
		afisare_CutieAgrafe(temp->info);
		temp = temp->next;
	}
	afisare_CutieAgrafe(temp->info);
}

CutieAgrafe stergere_nodLSC_cu_cod(Nod_LSC **prim, Nod_LSC **ultim, int COD) {
	if ((*prim) == NULL || (*ultim) == NULL) {
		CutieAgrafe ca;
		ca.cod_cutie = -1;
		return ca;
	}

	//cazul 1: extrag primul nod din lista
	if ((*prim)->info.cod_cutie == COD) {
		CutieAgrafe ca_returnat = copiere_CutieAgrafe((*prim)->info);
		Nod_LSC *temp = (*prim);
		(*prim) = (*prim)->next;
		(*ultim)->next = (*prim);

		//sterg nodul
		for (int i = 0; i < temp->info.numarAgrafe; i++) {
			free(temp->info.agrafe[i].culoare);
		}
		free(temp->info.agrafe);
		free(temp);

		return ca_returnat;
	}
	else {
		//cazul 2: extrag ultimul nod din lista
		if ((*ultim)->info.cod_cutie == COD) {
			CutieAgrafe ca_returnat = copiere_CutieAgrafe((*ultim)->info);

			Nod_LSC *temp = (*ultim);
			Nod_LSC *temp2 = (*prim);

			while (temp2->next != (*ultim))
				temp2 = temp2->next;

			temp2->next = (*prim);
			(*ultim) = temp2;

			//sterg nodul
			for (int i = 0; i < temp->info.numarAgrafe; i++) {
				free(temp->info.agrafe[i].culoare);
			}
			free(temp->info.agrafe);
			free(temp);

			return ca_returnat;
		}
		else {
			//cazul 3: e undeva la mijloc
			Nod_LSC *temp = (*prim);

			while (temp->next->next->info.cod_cutie == COD && temp->next != (*ultim))
				temp = temp->next;
			CutieAgrafe ca_returnat = copiere_CutieAgrafe(temp->next->info);

			Nod_LSC *p = temp->next;
			temp->next = p->next;

			//sterg nodul
			for (int i = 0; i < p->info.numarAgrafe; i++)
				free(p->info.agrafe[i].culoare);
			free(p->info.agrafe);
			free(p);

			return ca_returnat;
		}
	}
}

void afisare_stergere_CutieAgrafe_cu_dimensiune_mare(Nod_LSC **prim, Nod_LSC **ultim, int DIMENSIUNE) {
	Nod_LSC *temp = (*prim);


	while (temp != (*ultim)) {
		int nr = 0;
		for (int i = 0; i < temp->info.numarAgrafe; i++) {
			if (temp->info.agrafe[i].dimensiune > DIMENSIUNE)
				nr++;
		}
		

		if (nr == temp->info.numarAgrafe)
			afisare_CutieAgrafe(stergere_nodLSC_cu_cod(&temp, ultim, temp->info.cod_cutie));
		
	}

	int nr = 0;
	for (int i = 0; i < temp->info.numarAgrafe; i++) {
		if (temp->info.agrafe[i].dimensiune > DIMENSIUNE)
			nr++;
	}


	if (nr == temp->info.numarAgrafe)
		afisare_CutieAgrafe(stergere_nodLSC_cu_cod(&temp, ultim, temp->info.cod_cutie));
}

int main()
{
	Agrafa a1 = creare_agrafa(10, 3, "Alb");
	Agrafa a2 = creare_agrafa(11, 5, "Verde");
	Agrafa a3 = creare_agrafa(12, 2, "Rosu");
	Agrafa a4 = creare_agrafa(13, 1, "Negru");
	Agrafa a5 = creare_agrafa(43, 6, "Marsala");

	Agrafa av1[] = { a1, a2 };
	Agrafa av2[] = { a3, a2, a1 };
	Agrafa av3[] = { a4, a5 };

	CutieAgrafe ca1 = creare_cutieAgrafe(100, 2, av1);
	CutieAgrafe ca2 = creare_cutieAgrafe(101, 3, av2);
	CutieAgrafe ca3 = creare_cutieAgrafe(102, 2, av3);
	CutieAgrafe ca4 = creare_cutieAgrafe(103, 1, av3);
	CutieAgrafe ca5 = creare_cutieAgrafe(104, 1, av1);

	Nod_LSC *cap = NULL;
	Nod_LSC *coada = NULL;

	inserare_in_LSC(&cap, &coada, ca1);
	inserare_in_LSC(&cap, &coada, ca2);
	inserare_in_LSC(&cap, &coada, ca3);
	inserare_in_LSC(&cap, &coada, ca4);
	inserare_in_LSC(&cap, &coada, ca5);

	printf("\n\tTRAVERSARE LSC DUPA INSERARE");
	traversare_LSC(cap);

	printf("\n\n----------------------------------");

	printf("\nEXTRAG PRIMUL NOD DIN LSC");
	printf("\n\nAfisez Cutia de Agrafe extrasa");
	afisare_CutieAgrafe((stergere_nodLSC_cu_cod(&cap, &coada, 100)));
	printf("\nTraversez lista");
	traversare_LSC(cap);

	printf("\nEXTRAG ULTIMUL NOD DIN LISC");
	printf("\n\nAfisez Cutia de Agrafe extrasa");
	afisare_CutieAgrafe((stergere_nodLSC_cu_cod(&cap, &coada, 104)));
	printf("\nTraversez lista");
	traversare_LSC(cap);

	printf("\nEXTRAG UN NOD DE LA MIJLOC DIN LISC");
	printf("\n\nAfisez Cutia de Agrafe extrasa");
	afisare_CutieAgrafe((stergere_nodLSC_cu_cod(&cap, &coada, 102)));
	printf("\nTraversez lista");
	traversare_LSC(cap);

	printf("\n\n----------------------------------");
	printf("\nSterg agrafele cu dimensiunea mai mare ca 1");
	afisare_stergere_CutieAgrafe_cu_dimensiune_mare(&cap, &coada, 1);
	
	printf("\nAFISEZ CE A MAI RAMAS IN LISTA");
	traversare_LSC(coada);

}
