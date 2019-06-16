#include "pch.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct CotaIntretinere {
	char *adresa;
	int nr_strada;
	int nr_apartament; // ->cheie de cautare!!
	int nr_persoane;
	int an;
	int luna;
	float valoare_intretinere;
};

struct nod_lista_simpla {
	CotaIntretinere inf;
	nod_lista_simpla *next;
};

struct hash_table {
	nod_lista_simpla **vector;
	int size;
};

CotaIntretinere initializare_cota_intretinere(const char *adresa, int nr_strada, int nr_apartament, int nr_persoane,
	int an, int luna, float valoare_intretinere) {
	
	CotaIntretinere cota;
	cota.adresa = (char*)malloc(sizeof(char) * (strlen(adresa) + 1));
	strcpy(cota.adresa, adresa);

	cota.nr_strada = nr_strada;
	cota.nr_apartament = nr_apartament;
	cota.nr_persoane = nr_persoane;
	cota.an = an;
	cota.luna = luna;
	cota.valoare_intretinere = valoare_intretinere;

	return cota;
}

CotaIntretinere copiaza_cota(CotaIntretinere de_copiat) {
	CotaIntretinere cota;
	cota.adresa = (char*)malloc(sizeof(char) * (strlen(de_copiat.adresa) + 1));
	strcpy(cota.adresa, de_copiat.adresa);

	cota.nr_strada = de_copiat.nr_strada;
	cota.nr_apartament = de_copiat.nr_apartament;
	cota.nr_persoane = de_copiat.nr_persoane;
	cota.an = de_copiat.an;
	cota.luna = de_copiat.luna;
	cota.valoare_intretinere = de_copiat.valoare_intretinere;

	return cota;
}

void afisare_cota(CotaIntretinere cota) {
	printf("\nAdresa: %s, NrStrada: %d, NrApartament: %d, NrPersoane: %d, An: %d, Luna: %d, Val: %5.2f",
		cota.adresa, cota.nr_strada, cota.nr_apartament, cota.nr_persoane, cota.an, cota.luna, cota.valoare_intretinere);
}

void dezalocare_cota(CotaIntretinere cota) {
	free(cota.adresa);
}

nod_lista_simpla *creare_nod(CotaIntretinere inf, nod_lista_simpla *next) {
	nod_lista_simpla *nou = (nod_lista_simpla*)malloc(sizeof(nod_lista_simpla));

	nou->inf = copiaza_cota(inf);
	nou->next = next;

	return nou;
}

void adauga_element_in_lista_simpla(nod_lista_simpla **prim, CotaIntretinere inf) {
	nod_lista_simpla *nou = creare_nod(inf, NULL);

	if ((*prim) == NULL) {
		//daca lista este vida la inceput o initializez
		(*prim) = nou;
	}
	else {
		//altfel inserez la sfarsitul listei
		nod_lista_simpla *aux = (*prim);
		while (aux->next)
			aux = aux->next;

		aux->next = nou;
	}
}

void traverseaza_lista_simpla(nod_lista_simpla *prim) {
	nod_lista_simpla *aux = prim;
	printf("\n\tTraversare elemente din lista simpla");

	while (aux) {
		afisare_cota(aux->inf);
		aux = aux->next;
	}
}

void dezalocare_lista_simpla(nod_lista_simpla **prim) {
	nod_lista_simpla *aux = (*prim);
	printf("\n\n\tStergere lista simpla...");
	while (aux) {
		nod_lista_simpla *sterge = aux;
		aux = aux->next;

		dezalocare_cota(sterge->inf);
		free(sterge);
	}
	(*prim) = NULL;
}

int functie_hash(hash_table tabela, int nr_apartament) {
	return nr_apartament % tabela.size;
}

int adaugare_element_hash_table(hash_table tabela, CotaIntretinere inf) {
	int pozitie;

	if (tabela.vector != NULL) {
		pozitie = functie_hash(tabela, inf.nr_apartament);

		//adaug elemente pe pozitie
		adauga_element_in_lista_simpla(&tabela.vector[pozitie], inf);
	}

	return pozitie;
}

void traversare_hash_table(hash_table tabela) {
	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vector[i] != NULL) {
				printf("\n\nIndex pozitie curenta: (afisare) ->> %d", i);
				traverseaza_lista_simpla(tabela.vector[i]);
			}
		}
	}
}

void dezalocare_tabela_hash(hash_table tabela) {
	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vector[i] != NULL) {
				printf("\n\tIndex pozitie curenta: (stergere) %d", i);
				dezalocare_lista_simpla(&tabela.vector[i]);
			}
		}
	}
}

//valoarea totala anuala a unui apartament
// nr_apartament specificat, an de calcul + adresa apartament 
//3)
float calculeaza_valoarea_de_plata_anuala(hash_table tabela, int nr_apartament, int an, const char *adresa) {
	float val = 0.00;

	if (tabela.vector != NULL) {
		int pozitie = functie_hash(tabela, nr_apartament);

		if (tabela.vector[pozitie] != NULL) {
			//exista pozitia, deci pot sa caut apartamentul cu acest numar
			//am doua cazuri pe care trebuie sa le tratez: 1. apartamentul este pe prima pozitie; 2. nu este pe prima pozitie

			if (tabela.vector[pozitie]->inf.nr_apartament == nr_apartament
				&& tabela.vector[pozitie]->inf.an == an && !strcmp(tabela.vector[pozitie]->inf.adresa, adresa)) {
				printf("\n\tAm gasit apartamentul pe prima pozitie in lista! Ce apartament caut? NrApartament: %d, An: %d, Adresa: %s",
					nr_apartament, an, adresa);
				afisare_cota(tabela.vector[pozitie]->inf);

				val = 12 * tabela.vector[pozitie]->inf.valoare_intretinere;
				return val;
			}
			else { //nu am gasit pe prima pozitie, caut in lista

				nod_lista_simpla *aux = tabela.vector[pozitie];
				bool gasit = false;

				while (aux) {
					if (aux->inf.nr_apartament == nr_apartament && aux->inf.an == an && !strcmp(aux->inf.adresa, adresa)) {
						gasit = true;
						break;
					}
					aux = aux->next;
				}

				if (gasit) {
					printf("\n\tAm gasit apartamentul in lista! Ce apartament caut? NrApartament: %d, An: %d, Adresa: %s",
						nr_apartament, an, adresa);
					afisare_cota(aux->inf);
					val = aux->inf.valoare_intretinere * 12;
					
					return val;
				}
				else {
					printf("\n\tApartamentul cautat nu exista in hash table :(");
				}

			}
		}
	}
	else {
		return val;
	}
}

//cate cote au val mai mare decat un prag
//4)
int cate_cote_cu_prag_dat(hash_table tabela, float prag) {
	int nr = 0;

	if (tabela.vector != NULL) {
		//acum parcurg toata tabela si verific...
		//trebuie sa am grija la elementele din lista (sa le parcurg si pe ele!!)
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vector[i] != NULL) {
				nod_lista_simpla *aux = tabela.vector[i];

				while (aux) {
					if (aux->inf.valoare_intretinere > prag) {
						++nr;
						afisare_cota(aux->inf);
					}
					aux = aux->next;
				}
			}				
		}
	}

	return nr;
}

//sterg cotele cu nr_apartament, adresa specificat
//5)
void sterge_din_hash_table(hash_table tabela, int nr_apartament, const char *adresa) {
	if (tabela.vector != NULL) {
		int pozitie = functie_hash(tabela, nr_apartament);

		if (tabela.vector[pozitie] != NULL) {
			//caut daca e prima pozitie din lista
			if (tabela.vector[pozitie]->inf.nr_apartament == nr_apartament &&
				!strcmp(tabela.vector[pozitie]->inf.adresa, adresa)) {
				printf("\n\n\tSterg de pe prima pozitie in lista..");
				afisare_cota(tabela.vector[pozitie]->inf);

				nod_lista_simpla *aux = tabela.vector[pozitie];
				tabela.vector[pozitie] = tabela.vector[pozitie]->next;

				dezalocare_cota(aux->inf);
				free(aux);
			}
			else {
				//nu e prima pozitie si il caut...
				//trebuie sa ma pozitionez pe elementul din spatele elementului pe care il caut

				nod_lista_simpla *aux = tabela.vector[pozitie];
				bool gasit = false;

				while (aux->next) {
					if (aux->next->inf.nr_apartament == nr_apartament && !strcmp(aux->next->inf.adresa, adresa)) {
						gasit = true;
						break;
					}
					aux = aux->next;
				}

				if (gasit) {
					printf("\n\n\tSterg un element din lista:");
					afisare_cota(aux->next->inf);

					nod_lista_simpla *sterge = aux->next;
					aux->next = aux->next->next;

					dezalocare_cota(sterge->inf);
					free(sterge);
				}
			}
		}
		else {
			printf("\nNu exista acest apartament...");
		}
	}
}


void main() {
	//initializez 5 cote
	CotaIntretinere c1 = initializare_cota_intretinere("Adresa1", 10, 101, 2, 2019, 6, 400.20);
	CotaIntretinere c2 = initializare_cota_intretinere("Adresa2", 11, 202, 3, 2019, 5, 420.02);
	CotaIntretinere c3 = initializare_cota_intretinere("Adresa3", 12, 303, 1, 2019, 10, 200.02);
	CotaIntretinere c4 = initializare_cota_intretinere("Adresa4", 13, 400, 4, 2019, 7, 500.02);
	CotaIntretinere c5 = initializare_cota_intretinere("Adresa5", 14, 261, 2, 2019, 6, 375.02);

	//testez lista simpla
	nod_lista_simpla *prim = NULL;

	adauga_element_in_lista_simpla(&prim, c1);
	adauga_element_in_lista_simpla(&prim, c2);
	adauga_element_in_lista_simpla(&prim, c3);
	adauga_element_in_lista_simpla(&prim, c4);
	adauga_element_in_lista_simpla(&prim, c5);

	traverseaza_lista_simpla(prim);
	dezalocare_lista_simpla(&prim);
	printf("\n\n\tTABELA HASH\n\n");

	hash_table tabela;
	tabela.size = 101;
	tabela.vector = (nod_lista_simpla**)malloc(sizeof(nod_lista_simpla*) * tabela.size);

	for (int i = 0; i < tabela.size; i++)
		tabela.vector[i] = NULL;

	printf("---AFISARE ELEMENTE TABELA DUPA INSERARE---");
	adaugare_element_hash_table(tabela, c1);
	adaugare_element_hash_table(tabela, c2);
	adaugare_element_hash_table(tabela, c3);
	adaugare_element_hash_table(tabela, c4);
	adaugare_element_hash_table(tabela, c5);

	traversare_hash_table(tabela);


	printf("\n\n---FUNCTIA DE LA PCT 3---");
	printf("\n\tVal anuala ->>> %5.2f", calculeaza_valoarea_de_plata_anuala(tabela, 101, 2019, "Adresa1"));
	printf("\n\tVal anuala ->>> %5.2f", calculeaza_valoarea_de_plata_anuala(tabela, 303, 2019, "Adresa3"));
	printf("\n\tVal anuala ->>> %5.2f", calculeaza_valoarea_de_plata_anuala(tabela, 999, 2000, "StrCeva")); //woo nu crapa

	printf("\n\n---FUNCTIA DE LA PCT 4---");
	printf("\nCate cote: %d | prag = 400", cate_cote_cu_prag_dat(tabela, 400));

	printf("\n\n---FUNCTIA DE LA PCT 5---");
	sterge_din_hash_table(tabela, 303, "Adresa3");
	sterge_din_hash_table(tabela, 101, "Adresa1");
	sterge_din_hash_table(tabela, 261, "Adresa5");

	printf("\n\n---AFISARE ELEMENTE TABELA DUPA CE STERG---");
	traversare_hash_table(tabela);

	printf("\n\n---DEZALOCARE TABELA HASH---");
	dezalocare_tabela_hash(tabela);

	/*const char a[20] = "Aaa";
	const char b[20] = "Aaa";
	printf(strcmp(a, b) ? "da" : "nu");
	*/
}
