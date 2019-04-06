#include "pch.h"
#include <iostream>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

struct Student {
	int cod;
	char *nume;
	float medie;
};

struct Nod_LS {
	Student info;
	Nod_LS *next;
};

struct HashTable {
	Nod_LS **vector;
	int dim;
};

Student creare_student(int cod, const char *nume, float medie) {
	Student s;
	s.cod = cod;
	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(s.nume, nume);
	s.medie = medie;

	return s;
}

Student copiaza_informatie(Student deCopiat) {
	Student s;
	s.cod = deCopiat.cod;
	s.nume = (char*)malloc(sizeof(char) * (strlen(deCopiat.nume) + 1));
	strcpy(s.nume, deCopiat.nume);
	s.medie = deCopiat.medie;

	return s;
}

void afiseaza_student(Student s) {
	printf("\nCod: %d, Nume: %s, Medie: %5.2f", s.cod, s.nume, s.medie);
}

Nod_LS *creare_nod(Nod_LS *next, Student inf) {
	Nod_LS *nou = (Nod_LS*)malloc(sizeof(Nod_LS));
	nou->info = copiaza_informatie(inf);
	nou->next = next;

	return nou;
}

void inserare_lista_sfarsit(Nod_LS **prim, Student inf) {
	Nod_LS *nou = creare_nod(NULL, inf);

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

void traversare_lista(Nod_LS *prim) {
	Nod_LS *temp = prim;
	while (temp) {
		afiseaza_student(temp->info);
		temp = temp->next;
	}
	printf("\n");
}

void dezalocare_lista(Nod_LS **prim) {
	Nod_LS *temp = (*prim);
	while (temp) {
		Nod_LS *temp2 = temp;
		temp = temp->next;
		free(temp2->info.nume);
		free(temp2);
	}
}

int Hash_function(HashTable tabela, int cheie) {
	return cheie % tabela.dim;
}

HashTable initializare_Hash(int size) {
	HashTable h;

	h.vector = (Nod_LS**)malloc(sizeof(Nod_LS*) * size);
	h.dim = size;
	for (int i = 0; i < h.dim; i++)
		h.vector[i] = NULL;

	return h;
}

int inserare_HashTable(HashTable tabela, Student s) {
	if (tabela.vector != NULL) {
		int pozitie = Hash_function(tabela, s.cod);
		inserare_lista_sfarsit(&tabela.vector[pozitie], s);
		return pozitie;
	}
	else
		return -1;

}

void traversare_HashTable(HashTable tabela) {
	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vector[i] != NULL) {
				printf("\nPozitia pe care ma aflu: %d", i);
				traversare_lista(tabela.vector[i]);
			}
		}
	}
}

void dezalocare_HashTable(HashTable tabela) {
	if (tabela.vector != NULL) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vector[i] != NULL)
				dezalocare_lista(&tabela.vector[i]);
		}
	}
	free(tabela.vector);
}

int stergere(HashTable tabela, int cod) {
	if (tabela.vector != NULL) {
		int pozitie = Hash_function(tabela, cod);

		if (tabela.vector[pozitie] == NULL)
			return -1;
		else {
			if (tabela.vector[pozitie]->info.cod == cod) {
				if (tabela.vector[pozitie]->next == NULL) {
					Nod_LS *temp = tabela.vector[pozitie];
					free(temp->info.nume);
					free(temp);
					tabela.vector[pozitie] = NULL;

				}
				else {
					Nod_LS *temp = tabela.vector[pozitie];
					tabela.vector[pozitie] = temp->next;
					free(temp->info.nume);
					free(temp);

				}
			}
			else {
				Nod_LS *temp = tabela.vector[pozitie];
				while (temp->next != NULL && temp->next->info.cod != cod)
					temp = temp->next;

				Nod_LS *p = temp->next;
				if (p->next != NULL) {
					temp->next = p->next;
					free(p->info.nume);
					free(p);
				}
				else {
					temp->next = NULL;
					free(p->info.nume);
					free(p);
				}
			}
		}
		return pozitie;
	}
}

int main()
{
	Student s1 = creare_student(202, "Nume1", 8.35);
	Student s2 = creare_student(505, "Nume2", 7.40);
	Student s3 = creare_student(205, "Nume3", 9.20);
	Student s4 = creare_student(606, "Nume3", 9.20);

	HashTable tabela;
	tabela = initializare_Hash(101);

	inserare_HashTable(tabela, s1);
	inserare_HashTable(tabela, s2);
	inserare_HashTable(tabela, s3);
	inserare_HashTable(tabela, s4);

	traversare_HashTable(tabela);

	printf("\n\n-------");
	stergere(tabela, 205);
	traversare_HashTable(tabela);

	dezalocare_HashTable(tabela);
}

