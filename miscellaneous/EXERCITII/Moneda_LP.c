#include "pch.h"
#include <iostream>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

struct Moneda {
	char cod_moneda[5];
	char *denumire_ext;
	char *emitent;
	int sold_valutar;
};

struct HashTable {
	Moneda **vect;
	int size;
};

Moneda *creare_moneda(const char cm[], const char*den_ext, const char *e, int sv) {
	Moneda *m = (Moneda*)malloc(sizeof(Moneda));
	strcpy(m->cod_moneda, cm);
	m->denumire_ext = (char*)malloc(sizeof(char) * (strlen(den_ext) + 1));
	strcpy(m->denumire_ext, den_ext);
	m->emitent = (char*)malloc(sizeof(char) * (strlen(e) + 1));
	strcpy(m->emitent, e);
	m->sold_valutar = sv;

	return m;
}

void dezalocare_moneda(Moneda *m) {
	free(m->denumire_ext);
	free(m->emitent);
	free(m);
}

void afisare_Moneda(Moneda *m) {
	printf("\nCodMoneda: %s, DenumireExt: %s, Emitent: %s, SoldValutar: %d", m->cod_moneda,
		m->denumire_ext, m->emitent, m->sold_valutar);
}

int functie_Hash(HashTable tabela, const char cheie[]) {
	int s = 0;
	for (int i = 0; i < strlen(cheie); i++)
		s += i;

	return s % tabela.size;
}

HashTable initializare_Tabela(int size) {
	HashTable h;
	h.size = size;
	h.vect = (Moneda**)malloc(sizeof(Moneda) * size);
	for (int i = 0; i < size; i++)
		h.vect[i] = NULL;

	return h;
}

int inserare_elemente_HashTable(HashTable tabela, Moneda *m) {
	int pozitie;
	if (tabela.vect != NULL) {
		pozitie = functie_Hash(tabela, m->cod_moneda);

		if (tabela.vect[pozitie] == NULL) {
			//pot insera, pozitia este libera
			tabela.vect[pozitie] = m;
		}
		else {
			//am o coliziune, caut urmatoarea pozitie libera
			int index = 1;
			while (pozitie + index < tabela.size) {
				if (tabela.vect[pozitie + index] == NULL) {
					tabela.vect[pozitie + index] = m;
					pozitie += index;
					break;
				}
				index++;
			}
		}
	}
	return pozitie;
}

void traversare_HashTable(HashTable tabela) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vect[i] != NULL) {
				printf("\nPozitia: %d", i);
				afisare_Moneda(tabela.vect[i]);
				printf("\n");
			}
		}
	}
}

//caut in tabela de dispersie toate monedele care au soldul valutar mai mare decat o val data
//sa stiu cat aloc vectorul
int numara_monede(HashTable tabela, int SOLD) {
	int nr = 0;
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vect[i] != NULL) {
				if (tabela.vect[i]->sold_valutar > SOLD)
					nr++;
			}
		}
	}

	return nr;
}

Moneda **vector_moneda(HashTable tabela, int SOLD) {
	int dimensiune = numara_monede(tabela, SOLD);

	Moneda **vectorM = (Moneda**)malloc(sizeof(Moneda) * dimensiune);
	for (int i = 0; i < dimensiune; i++)
		vectorM[i] = NULL;
	int x = 0;

	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vect[i] != NULL) {
				if (tabela.vect[i]->sold_valutar > SOLD) {
					vectorM[x++] = tabela.vect[i];
				}
			}
		}
	}

	return vectorM;

}

int modificare_sold_moneda_HashTable(HashTable tabela, int sold_nou, const char cheie[]) {
	int pozitie;

	if (tabela.vect != NULL) {
		pozitie = functie_Hash(tabela, cheie);
		
		if (strcmp(tabela.vect[pozitie]->cod_moneda, cheie) == 0) {
			tabela.vect[pozitie]->sold_valutar = sold_nou;
		}
		else {
			int index = 1;
			while (pozitie + index < tabela.size) {
				if (strcmp(tabela.vect[pozitie + index]->cod_moneda, cheie) == 0) {
					tabela.vect[pozitie + index]->sold_valutar = sold_nou;
					pozitie += index;
					break;
				}
				index++;
			}
		}
	}
	return pozitie;
}

void dezalocare_HashTable(HashTable tabela) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vect[i] != NULL)
				dezalocare_moneda(tabela.vect[i]);
		}
		free(tabela.vect);
	}
}

int main()
{
	Moneda *m1 = creare_moneda("RON", "Leu romanesc", "Romania", 10000000);
	Moneda *m2 = creare_moneda("BGP", "Lira UK", "Anglia", 4000);
	Moneda *m3 = creare_moneda("DOLC", "Dolar canadian", "Canada", 60000);
	Moneda *m4 = creare_moneda("DOLA", "Dolar american", "America", 500000);
	Moneda *m5 = creare_moneda("TKL", "Lira turceasca", "Turcia", 900000);

	HashTable tabela = initializare_Tabela(101);
	inserare_elemente_HashTable(tabela, m1);
	inserare_elemente_HashTable(tabela, m2);
	inserare_elemente_HashTable(tabela, m3);
	inserare_elemente_HashTable(tabela, m4);
	inserare_elemente_HashTable(tabela, m5);

	printf("\nAFISEZ ELEMENTELE DUPA CE AM INSERAT");
	traversare_HashTable(tabela);

	printf("\n\n--------------------------------");
	Moneda **vectorM = vector_moneda(tabela, 90000);
	int dim = numara_monede(tabela, 90000);
	
	printf("\nAFISEZ VECTORUL DE MONEDE CARE AU SOLDUL MAI MARE CA 90000");
	for (int i = 0; i < dim; i++)
		afisare_Moneda(vectorM[i]);

	printf("\n\n--------------------------------");
	printf("\nMODIFIC SOLDUL MONEDEI CU CODUL RON");
	printf("\n\nModificarea s-a produs pe pozitia: %d", modificare_sold_moneda_HashTable(tabela, 555, "RON"));

	printf("\nAFISEZ TABELA DUPA MODIFICARE");
	traversare_HashTable(tabela);

	dezalocare_HashTable(tabela);
}

