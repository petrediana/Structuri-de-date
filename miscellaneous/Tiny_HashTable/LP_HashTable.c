#include "pch.h"
#include <iostream>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
//LINEAR PROBING

struct Student {
	int cod;
	char *nume;
	float medie;
};

struct HashTable {
	Student **vect;
	int size;
};

Student *creare_student(int cod, const char *nume, float medie) {
	Student *s = (Student*)malloc(sizeof(Student));
	s->cod = cod;
	s->nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(s->nume, nume);
	s->medie = medie;

	return s;
}


void afiseaza_student(Student *s) {
	printf("\nCod: %d, Nume: %s, Medie: %5.2f", s->cod, s->nume, s->medie);
}

void dezalocare_Student(Student *s) {
	free(s->nume);
	free(s);
}

int functie_Hash(HashTable tabela, int cheie) {
	return cheie % tabela.size;
}

HashTable initializare_HashTable(int size) {
	HashTable h;
	h.size = size;
	h.vect = (Student**)malloc(sizeof(Student*) * size);
	for (int i = 0; i < size; i++)
		h.vect[i] = NULL;

	return h;
}

int inserare_HashTable(HashTable tabela, Student *info) {
	if (tabela.vect != NULL) {
		int pozitie = functie_Hash(tabela, (*info).cod);
		
		if (tabela.vect[pozitie] == NULL) {
			//nu am coliziune, pot sa inserez
			tabela.vect[pozitie] = info;
		}
		else {
			//am coliziune, trebuie sa inserez pe urmatoarea pozitie libera
			int index = 1;
			while (index + pozitie < tabela.size) {
				if (tabela.vect[index + pozitie] == NULL) {
					tabela.vect[index + pozitie] = info;
					pozitie += index;
					break;
				}
				else
					index++;

			}
		}

		return pozitie;
	}
}

void traversare_HashTable(HashTable tabela) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vect[i] != NULL) {
				printf("\nPozitia: %d", i);
				afiseaza_student(tabela.vect[i]);
			}
		}
	}
}

void dezalocare_HashTable(HashTable tabela) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vect[i] != NULL) {
				dezalocare_Student(tabela.vect[i]);
			}
		}
		free(tabela.vect);
		tabela.vect = NULL;
	}
}

int stergere(HashTable tabela, int cheie) {
	if (tabela.vect != NULL) {
		int pozitie = functie_Hash(tabela, cheie);

		if (tabela.vect[pozitie]->cod == cheie) {
			dezalocare_Student(tabela.vect[pozitie]);
			tabela.vect[pozitie] = NULL;
		}
		else {
			int index = 1;
			while (pozitie + index < tabela.size) {
				if (tabela.vect[pozitie + index]->cod == cheie) {
					dezalocare_Student(tabela.vect[pozitie + index]);
					tabela.vect[pozitie + index] = NULL;
					pozitie += index;
					break;
				}
				index++;
			}
		}
		return pozitie;
	}
}

int main()
{
	Student *s1 = creare_student(202, "Nume1", 8.35);
	Student *s2 = creare_student(505, "Nume2", 5.60);
	Student *s3 = creare_student(205, "Nume3", 7.22);

	HashTable tabela = initializare_HashTable(101);
	inserare_HashTable(tabela, s1);
	inserare_HashTable(tabela, s2);
	inserare_HashTable(tabela, s3);

	traversare_HashTable(tabela);
	printf("\n\n---------");
	stergere(tabela, 205);
	traversare_HashTable(tabela);


	dezalocare_HashTable(tabela);
}
