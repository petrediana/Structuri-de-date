// Test_Monitor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
//#include <iostream>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

struct Monitor {
	int cod;
	char *producator;
	float diagonala;
	int numarPorturi;

};
//lista simpla circulara
struct nod_LSC {
	struct Monitor info;
	struct nod_LSC *next;
};

struct Monitor creare_monitor(int c, const char *p, float d, int nr) {
	struct Monitor m;
	m.cod = c;
	m.producator = (char*)malloc(sizeof(char) * (strlen(p + 1)));
	strcpy(m.producator, p);
	m.diagonala = d;
	m.numarPorturi = nr;

	return m;
}

void afisare_monitor(struct Monitor m) {
	printf("\nCod: %d, Producator: %s, Diagonala: %5.2f, "
		"NumarPorturi: %d", m.cod, m.producator, m.diagonala, m.numarPorturi);
}

struct nod_LSC *inserare_element(struct Monitor m, struct nod_LSC *next) {
	struct nod_LSC *nou = (struct nod_LSC*)malloc(sizeof(struct nod_LSC));

	nou->info.cod = m.cod;
	nou->info.producator = (char*)malloc(sizeof(char) * (strlen(m.producator) + 1));
	strcpy((nou->info.producator), m.producator);
	nou->info.diagonala = m.diagonala;
	nou->info.numarPorturi = m.numarPorturi;

	nou->next = next;
	return nou;
}

//2. inserare la sfarsit si retin adresa ultimului nod inserat
void inserare_in_LSC(struct nod_LSC **primul, struct nod_LSC **ultimul, struct Monitor info) {
	struct nod_LSC *nou = inserare_element(info, NULL);

	if ((*primul) == NULL && (*ultimul) == NULL) {
		(*primul) = nou;
		(*ultimul) = nou;
		nou->next = (*primul);
	}
	else {
		nou->next = (*primul);
		(*ultimul)->next = nou;
		(*ultimul) = nou;
	}
}
//3. afisare elemente
void traversare_LSC(struct nod_LSC *primul) {
	struct nod_LSC *temp = primul;
	while (temp->next != primul) {
		afisare_monitor(temp->info);
		temp = temp->next;
	}
	afisare_monitor(temp->info);
}

//returnez adresa nodului cu un anumit cod
nod_LSC *adresa_nod(nod_LSC *prim, int COD) {
	nod_LSC *temp;
	int gasit = 0;

	temp = prim;
	while (temp->next != prim && gasit != 1) {
		if (temp->info.cod == COD) {
			gasit = 1;
			return temp;
		}
		else
			temp = temp->next;
	}
	if (temp->info.cod == COD) {
		gasit = 1;
		return temp;
	}

	if (gasit == 0)
		return NULL;
}

//4. caut si elimin nodul cu un anumit cod
nod_LSC *extragere_nod_cu_cod_dat(nod_LSC **prim, nod_LSC **ultim, int COD) {
	nod_LSC *gasit = adresa_nod(*prim, COD); //am nodul pe care vreau sa il sterg

	//cazul 1: nodul gasit se afla la inceputul liste
	if (gasit == (*prim)) {
		nod_LSC *temp = (*prim);
		(*prim) = (*prim)->next;
		(*ultim)->next = (*prim);

		free(temp->info.producator);
		free(temp);
		return gasit;
	}
	else {

		//cazul 2: nodul gasit se afla la finalul listei
		if (gasit == (*ultim)) {
			nod_LSC *temp1 = (*prim);

			while (temp1->next != (*ultim))//retin adresa penultimului nod
				temp1 = temp1->next;

			nod_LSC *temp2 = (*ultim);
			(*ultim) = temp1;
			(*ultim)->next = (*prim);

			free(temp2->info.producator);
			free(temp2);
			return gasit;
		}

		//cazul 3: nodul gasit este undeva prin lista (nu la inceput, nu la final)
		else {
			//stergerea unui nod din interiorul listei
			//retin adresa urmatorului nod
			//eu vreau sa sterg acel nod, (pe urmatorul)
			//ca sa nu pierd datele urmatoare, suprascriu peste gasit informatiile de la gasit->next
			//practic "mut" lista la stanga peste gasit
			//apoi leg gasit->next cu gasit->next->next
			nod_LSC *temp1 = gasit->next;

			gasit->info = gasit->next->info;
			gasit->info.producator = (char*)malloc(sizeof(char) * (strlen(gasit->next->info.producator) + 1));
			strcpy(gasit->info.producator, gasit->next->info.producator);

			gasit->next = gasit->next->next;

			free(temp1->info.producator);
			free(temp1);
			return gasit;
		}
	}
}

void numara_elemente(nod_LSC *prim, float DIAGONALA, int *nr) {
	nod_LSC *temp = prim;

	while (temp->next != prim) {
		if (temp->info.diagonala < DIAGONALA)
			(*nr)++;
		temp = temp->next;
	}
	if (temp->info.diagonala < DIAGONALA)
		(*nr)++;
	//numar cate elemente din lista au diagonala mai mica decat o anumita valoare
	//sa stiu cat aloc vectorul..
}

Monitor *elemente_exrase_cu_diagonala(nod_LSC **prim, nod_LSC **ultim, float DIAGONALA, int nr) {
	Monitor *m = (Monitor*)malloc(sizeof(Monitor) * nr);
	int index = 0;

	nod_LSC *temp = (*prim);
	while (temp->next != (*prim)) {
		if (temp->info.diagonala < DIAGONALA) {
			nod_LSC *gasit = adresa_nod(*prim, temp->info.cod);
				//printf("\n\n\n\n\t\t %d", gasit->info.cod);
			
			m[index] = gasit->info;
			m[index].producator = (char*)malloc(sizeof(char) * (strlen(gasit->info.producator) + 1));
			strcpy(m[index].producator, gasit->info.producator);
			index++;

		}
		temp = temp->next;
	}

	if (temp->info.diagonala < DIAGONALA) {
		nod_LSC *gasit = adresa_nod(*prim, temp->info.cod);
			//printf("\n\n\n\n\t\t %d", gasit->info.cod);

		m[index] = gasit->info;
		m[index].producator = (char*)malloc(sizeof(char) * (strlen(gasit->info.producator) + 1));
		strcpy(m[index].producator, gasit->info.producator);
		index++;
	}


	while (*prim != (*ultim)) {
		
		if ((*prim)->info.diagonala < DIAGONALA) {
				//printf("\n\n\n\n\t %d", (*prim)->info.cod);
			extragere_nod_cu_cod_dat(prim, ultim, (*prim)->info.cod);
		}
		
	}
	if ((*prim)->info.diagonala < DIAGONALA) {
			//printf("\n\n\n\n\t %d", (*prim)->info.cod);
		extragere_nod_cu_cod_dat(prim, ultim, (*prim)->info.cod);
	}

	return m;
}


int main()
{
	struct Monitor m1 = creare_monitor(10, "Monitor1", 20.00, 15);
	struct Monitor m2 = creare_monitor(11, "Monitor2", 21.01, 16);
	struct Monitor m3 = creare_monitor(12, "Monitor3", 22.02, 17);
	struct Monitor m4 = creare_monitor(13, "Monitor4", 23.03, 18);
	struct Monitor m5 = creare_monitor(14, "Monitor5", 24.04, 19);
	struct Monitor m6 = creare_monitor(15, "Monitor6", 50.04, 20);

	struct nod_LSC *cap = NULL;
	struct nod_LSC *coada = NULL;

	inserare_in_LSC(&cap, &coada, m1);
	inserare_in_LSC(&cap, &coada, m2);
	inserare_in_LSC(&cap, &coada, m3);
	inserare_in_LSC(&cap, &coada, m4);
	inserare_in_LSC(&cap, &coada, m5);
	inserare_in_LSC(&cap, &coada, m6);
	
	printf("------LISTA INITIALA---------");
	traversare_LSC(cap);

	printf("\n\nSTERG PRIMUL NOD:");
	extragere_nod_cu_cod_dat(&cap, &coada, 10);
	traversare_LSC(cap);

	printf("\n\nSTERG ULTIM NOD:");
	extragere_nod_cu_cod_dat(&cap, &coada, 15);
	traversare_LSC(cap);

	printf("\n\nSTERG UNUI NOD DIN INTERIOR:");
	extragere_nod_cu_cod_dat(&cap, &coada, 11);
	traversare_LSC(cap);

	
	int nr = 0;
	numara_elemente(cap, 24, &nr);
	//printf("\n\n%d", nr);

	Monitor *m = elemente_exrase_cu_diagonala(&cap, &coada, 24, nr);

	printf("\n\n\tVECTOR DE MONITOARE EXTRASE: ");
	for (int i = 0; i < nr; i++) {
		printf("\n\nCod: %d, Producator: %s, Diagonala: %5.2f, NrPort: %d", m[i].cod, m[i].producator,
			m[i].diagonala, m[i].numarPorturi);
	}

	printf("\n\n------CE A MAI RAMAS IN LISTA---------");
	traversare_LSC(cap);

	return 0;
}

/*

   printf("\n-------");
   printf("\n\nEXTRAGERE PRIMUL ELEMENT: ");
   extragere_nod_cu_cod(&cap, &coada, 10);
   traversare_LSC(cap);

   printf("\n\nEXTRAGERE ULTIMUL ELEMENT: ");
   extragere_nod_cu_cod(&cap, &coada, 14);
   traversare_LSC(cap);


   printf("\n\nEXTRAGERE ELEMENT MIJLOC: ");
   extragere_nod_cu_cod(&cap, &coada, 12);
   traversare_LSC(cap);

*/
/*


bool cautare_element_LSC(struct nod_LSC *prim, int COD_CAUTAT) {
	if (prim == NULL) {
		printf("\nLista este vida!");
		return false;
	}
	else {
		struct nod_LSC *temp = prim;
		while (temp->next != prim) {
			if (temp->info.cod == COD_CAUTAT) {
				printf("\nElementul exista in lista");
				return true;
			}
			else
				temp = temp->next;
		}
		if (temp->info.cod == COD_CAUTAT) {
			printf("\nElementul exista in lista");
			return true;
		}
		else {
			printf("\nElementul nu exista in lista");
			return false;
		}

	}
}


//4. extragere nod
struct nod_LSC *extragere_nod_cu_cod(struct nod_LSC **prim, struct nod_LSC **ultim, int COD) {
	struct nod_LSC *extras;

	if (!(cautare_element_LSC(*prim, COD)))
		return NULL;
	else { //am ce sa extrag, exista elementul cu codul: COD

		//cazul 1: nodul cautat se afla la inceputul listei
		if ((*prim)->info.cod == COD) {
			extras = inserare_element((*prim)->info, NULL);
			// extras -> next = extras;
			struct nod_LSC *temp = *prim;
			free(temp->info.producator);
			free(temp);
			(*prim) = (*prim)->next;
			(*ultim)->next = (*prim);

			return extras;
		}

		//cazul 2: nodul cautat este pe ultima pozitie in lista
		if ((*ultim)->info.cod == COD) {
			extras = inserare_element((*ultim)->info, NULL);
			// extras -> next = extras;
			 //trebuie sa parcurg lista, sa ma pozitionez pe penultimul element
			struct nod_LSC *temp = (*prim);
			while (temp->next != (*ultim))
				temp = temp->next;

			//in temp am acum penultimul nod
			struct nod_LSC *temp2 = temp;
			free(temp2->info.producator);
			free(temp2);
			temp->next = (*prim);
			(*ultim) = temp;

			return extras;
		}

		//cazul 3: nodul cautat este undeva in lista (nu primul, nu ultimul)
		//trebuie sa stiu nodul curent pe care sa il extrag si nodul din spate pentru a le lega corect dupa stergere

		struct nod_LSC *temp_curent = (*prim);
		struct nod_LSC *temp_prec = (*prim);

		while (temp_curent->info.cod != COD)
			temp_curent = temp_curent->next; //m am pozitionat pe nodul pe care doresc sa il extrag

		while (temp_prec->next->info.cod != COD)
			temp_prec = temp_prec->next; //m am pozitionat pe cel din spate

		extras = inserare_element(temp_curent->info, NULL);
		// extras -> next = extras;
		struct nod_LSC *temp3 = temp_curent;
		free(temp3->info.producator);
		free(temp3);
		temp_prec->next = (temp_curent)->next;
		return extras;

	}
}
*/