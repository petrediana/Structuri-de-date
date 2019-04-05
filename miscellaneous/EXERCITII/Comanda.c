#include "pch.h"
#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

struct Comanda {
	int cod;
	char *nume_client;
	float suma;
	int nr_produse;
};

struct Nod_Coada {
	Comanda info;
	Nod_Coada *next;
};

//functie de copiere a informatiei
Comanda copiere_informatii(Comanda c1) {
	Comanda c;
	c.cod = c1.cod;
	c.nume_client = (char*)malloc(sizeof(char) * (strlen(c1.nume_client) + 1));
	strcpy(c.nume_client, c1.nume_client);
	c.nr_produse = c1.nr_produse;
	c.suma = c1.suma;

	return c;
}

Comanda creare_comanda(int cod, const char *nume, int nr, float suma) {
	Comanda c;
	c.cod = cod;
	c.nume_client = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(c.nume_client, nume);
	c.nr_produse = nr;
	c.suma = suma;

	return c;
}

void afisare_Comanda(Comanda c) {
	printf("\nCod: %d, Nume: %s, NrProduse: %d, SumaTotala: %5.2f", c.cod, c.nume_client,
		c.nr_produse, c.suma);
}

Nod_Coada *inserare_Nod(Comanda c, Nod_Coada *next) {
	Nod_Coada *nou = (Nod_Coada*)malloc(sizeof(Nod_Coada));
	
	nou->info = copiere_informatii(c);
	nou->next = next;
	
	return nou;
}

//inserez un nod nou creat anterior la sfarsit, retin adresa ultimului nod
void put_Coada(Nod_Coada **prim, Nod_Coada **ultim, Comanda c) {
	Nod_Coada *nou = inserare_Nod(c, NULL);

	if ((*prim) == NULL && (*ultim) == NULL) {
		(*prim) = nou;
		(*ultim) = nou;
	}
	else {
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

void traversare_Coada(Nod_Coada *prim) {
	printf("\n\tTraversare Coada");
	if (prim == NULL)
		printf("\nCoada vida!");
	else {
		Nod_Coada *temp = prim;
		while (temp) {
			afisare_Comanda(temp->info);
			temp = temp->next;
		}
	}
}

//COADA -> trebuie sa respect FIFO: first in first out
//scot primul element inserat in coada

//returnez nodul extras si retin informatia extrasa
Nod_Coada *get_Coada(Nod_Coada **prim, Comanda *c) {
	if ((*prim) != NULL) {
		Nod_Coada *nod_returnat = inserare_Nod((*prim)->info, NULL); //construiesc nodul extras
		(*c) = copiere_informatii((*prim)->info); //retin informatia

		//acum trebuie sa sterg acest nod din lista
		Nod_Coada *temp = (*prim);
		(*prim) = (*prim)->next;

		free(temp->info.nume_client);
		free(temp);
		temp = NULL;

		return nod_returnat;
	}
	else
		return NULL;
	
}

//vreau sa stiu cate comenzi au suma mai mica decat 100
//sa stiu cat aloc vectorul
int numara_comenzi_dupa_suma(Nod_Coada *prim) {
	Nod_Coada *temp = prim;
	int nr = 0;
	while (temp) {
		if (temp->info.suma < 100.00)
			nr++;
		temp = temp->next;
	}

	return nr;
}

void pune_elemente_vector(Nod_Coada **prim, Comanda *vect) {
	Nod_Coada *temp = (*prim);
	Comanda c;
	int i = 0;

	while (get_Coada(&temp, &c)) {
		if (c.suma < 100.00)
			vect[i++] = copiere_informatii(c);
	}

	(*prim) = NULL;
}

//sortare descrescatoare dupa numarul de produse
void sortare_vector(Comanda *vect, int nr) {
	Comanda aux;

	for (int i = 0; i < nr - 1; i++) {
		for (int j = i + 1; j < nr; j++) {
			if (vect[i].nr_produse < vect[j].nr_produse) {
				aux = vect[i];
				vect[i] = vect[j];
				vect[j] = aux;
			}
		}
	}
}

int main()
{
	Comanda c1 = creare_comanda(20, "NumeClient1", 15, 90.75);
	Comanda c2 = creare_comanda(10, "NumeClient2", 5, 65.30);
	Comanda c3 = creare_comanda(25, "NumeClient3", 35, 50.20);
	Comanda c4 = creare_comanda(15, "NumeClient4", 17, 250.05);
	Comanda c5 = creare_comanda( 7, "NumeClient5", 20, 100);

	Nod_Coada *prim = NULL;
	Nod_Coada *ultim = NULL;

	put_Coada(&prim, &ultim, c1);
	put_Coada(&prim, &ultim, c2);
	put_Coada(&prim, &ultim, c3);
	put_Coada(&prim, &ultim, c4);
	put_Coada(&prim, &ultim, c5);

	printf("\nAFISARE ELEMENTE COADA DUPA INSERARE");
	traversare_Coada(prim);
    
	printf("\n\n~~~~~~~~~~~~~");
	Comanda comanda_extrasa;
	get_Coada(&prim, &comanda_extrasa); //extrag primul element inserat
	printf("\n\nAfisez informatia extrasa");
	afisare_Comanda(comanda_extrasa);  //afisez informatia inserata
	printf("\n\nAfisez lista dupa ce am extras primul nod inserat");
	traversare_Coada(prim);			  //traversez coada din nou, primul element este sters

	printf("\n\n~~~~~~~~~~~~~");
	int nr = 0;
	nr = numara_comenzi_dupa_suma(prim); //am cate comenzi au suma mai mica decat 100
	printf("\nSunt: %d comenzi", nr);

	Comanda *vect_comenzi = (Comanda*)malloc(sizeof(Comanda) * nr);
	pune_elemente_vector(&prim, vect_comenzi); //construiesc vectorul cu suma < 100

	printf("\n\nAfisez elementele din vector");
	for (int i = 0; i < nr; i++)
		afisare_Comanda(vect_comenzi[i]); //afisez vectorul

	sortare_vector(vect_comenzi, nr);
	printf("\n\nAfisez elementele vectorului sortate");
	for (int i = 0; i < nr; i++)
		afisare_Comanda(vect_comenzi[i]); // afisez vectorul sortat

	traversare_Coada(prim);
}

