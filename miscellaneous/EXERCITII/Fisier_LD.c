#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Fisier {
	char *denumire_fisier;
	char *path_fisier;
	char *extensie_fisier;
	unsigned int dim_bytes;
};

//nod lista dubla
struct Nod_LD {
	Fisier info;
	Nod_LD *next;
	Nod_LD *prev;
};

char *copiaza_variabila_char(const char *deCopiat) {
	char *returnat;
	returnat = (char*)malloc(sizeof(char) * (strlen(deCopiat) + 1));
	strcpy(returnat, deCopiat);

	return returnat;
}

Fisier creare_fisier(const char *denf, const char *pathf, const char *extf, unsigned int dim) {
	Fisier f;
	f.denumire_fisier = copiaza_variabila_char(denf);
	f.path_fisier = copiaza_variabila_char(pathf);
	f.extensie_fisier = copiaza_variabila_char(extf);
	f.dim_bytes = dim;

	return f;
}

void afisare_fisier(Fisier f) {
	printf("\nDenumire fisier: %s, PathFisier: %s, ExtensieFisier: %s, DimensiuneFisier: %d",
		f.denumire_fisier, f.path_fisier, f.extensie_fisier, f.dim_bytes);
}

Nod_LD *creare_NOD(Fisier f) {
	Nod_LD *nou = (Nod_LD*)malloc(sizeof(Nod_LD));

	nou->info.denumire_fisier = copiaza_variabila_char(f.denumire_fisier);
	nou->info.path_fisier = copiaza_variabila_char(f.path_fisier);
	nou->info.extensie_fisier = copiaza_variabila_char(f.extensie_fisier);
	nou->info.dim_bytes = f.dim_bytes;

	nou->next = NULL;
	nou->prev = NULL;

	return nou;
}

void inserare_LD(Nod_LD **prim, Nod_LD **ultim, Fisier f) {
	Nod_LD *nou = creare_NOD(f);

	if (*prim == NULL && *ultim == NULL) {
		(*prim) = nou;
		(*ultim) = nou;
	}
	else {
		(*ultim)->next = nou;
		nou->prev = (*ultim);
		(*ultim) = nou;
	}
}

void traversare_normala_LD(Nod_LD *prim) {
	Nod_LD *temp = prim;
	while (temp) {
		afisare_fisier(temp->info);
		temp = temp->next;
	}
}

void traversare_inversa_LD(Nod_LD *ultim) {
	Nod_LD *temp = ultim;
	while (temp) {
		afisare_fisier(temp->info);
		temp = temp->prev;
	}
}

//numar cate fisiere au o anumita extensie
int numara_fisiere(Nod_LD *prim, const char *extensie) {
	int nr = 0;
	Nod_LD *temp = prim;
	while (temp) {
		if (strcmp(temp->info.extensie_fisier, extensie) == 0)
			nr++;
		temp = temp->next;
	}

	return nr;
}

Fisier *vector_f(Nod_LD *prim, const char* extensie) {
	int dimensiune_vector = numara_fisiere(prim, extensie);
	Fisier *vectF = (Fisier*)malloc(sizeof(Fisier) * dimensiune_vector);
	int x = 0;

	Nod_LD *temp = prim;
	while (temp) {
		if (strcmp(temp->info.extensie_fisier, extensie) == 0)
			vectF[x++] = temp->info;
		temp = temp->next;
	}

	return vectF;
}

void modifica_LD(Nod_LD *prim, const char *extensie_curenta, const char *extensie_NOUA) {
	Nod_LD *temp = prim;
	while (temp) {
		if (strcmp(temp->info.extensie_fisier, extensie_curenta) == 0) {
			free(temp->info.extensie_fisier);
			temp->info.extensie_fisier = copiaza_variabila_char(extensie_NOUA);
			break;
		}
		temp = temp->next;
	}
}

void dezalocare_LD(Nod_LD **prim) {
	Nod_LD *temp = *prim;
	while (temp) {
		Nod_LD *temp2 = temp;
		temp = temp->next;

		free(temp2->info.denumire_fisier);
		free(temp2->info.extensie_fisier);
		free(temp2->info.path_fisier);
		free(temp2);
	}
}

void extragere_LD(Nod_LD **prim, Nod_LD **ultim, char *extensie, Fisier *extras) {
	
	if ((*prim) == NULL && (*ultim) == NULL)
		return;
	else {
		//cazul 1: extrag primul element al listei
		if (strcmp((*prim)->info.extensie_fisier, extensie) == 0) {
			(*extras).denumire_fisier = copiaza_variabila_char((*prim)->info.denumire_fisier);
			(*extras).extensie_fisier = copiaza_variabila_char((*prim)->info.extensie_fisier);
			(*extras).path_fisier = copiaza_variabila_char((*prim)->info.path_fisier);
			(*extras).dim_bytes = (*prim)->info.dim_bytes;

			Nod_LD *temp = *prim;
			(*prim) = (*prim)->next;
			(*prim)->prev = NULL;

			free(temp->info.denumire_fisier);
			free(temp->info.extensie_fisier);
			free(temp->info.path_fisier);
			free(temp);
		}
		else {
			//cazul 2: extrag ultimul nod al listei
			if (strcmp((*ultim)->info.extensie_fisier, extensie) == 0) {
				(*extras).denumire_fisier = copiaza_variabila_char((*prim)->info.denumire_fisier);
				(*extras).extensie_fisier = copiaza_variabila_char((*prim)->info.extensie_fisier);
				(*extras).path_fisier = copiaza_variabila_char((*prim)->info.path_fisier);
				(*extras).dim_bytes = (*prim)->info.dim_bytes;

				Nod_LD *temp = (*ultim);
				(*ultim) = (*ultim)->prev;
				(*ultim)->next = NULL;
				
				free(temp->info.denumire_fisier);
				free(temp->info.extensie_fisier);
				free(temp->info.path_fisier);
				free(temp);
			}
			else {
				//cazul 3: extrag un nod de la mijloc
				Nod_LD *temp = (*prim);

				while (temp) {
					if (strcmp(temp->info.extensie_fisier, extensie) == 0) {
						(*extras).denumire_fisier = copiaza_variabila_char((*prim)->info.denumire_fisier);
						(*extras).extensie_fisier = copiaza_variabila_char((*prim)->info.extensie_fisier);
						(*extras).path_fisier = copiaza_variabila_char((*prim)->info.path_fisier);
						(*extras).dim_bytes = (*prim)->info.dim_bytes;
						break;
					}
					temp = temp->next;
				}
				
				Nod_LD *temp2 = temp;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;

				free(temp2->info.denumire_fisier);
				free(temp2->info.extensie_fisier);
				free(temp2->info.path_fisier);
				free(temp2);
			}
		}
	}
}

int main()
{
	Fisier f1 = creare_fisier("Studenti", "D:\\folder1\\Acasa", ".txt", 30);
	Fisier f2 = creare_fisier("PozeMunte", "D:\\folder2\\Poze", ".jpg", 100);
	Fisier f3 = creare_fisier("NoteExamen", "D:\\folder3\\note", ".word", 70);
	Fisier f4 = creare_fisier("Partituri", "D:\\folder4\\Muzica", ".txt", 20);
	Fisier f5 = creare_fisier("DeseneAnimate", "C:\\folder5\\Filme", ".wav", 30);
	Fisier f6 = creare_fisier("aaaaa", "random", ".wav", 30);

	Nod_LD *cap = NULL;
	Nod_LD *coada = NULL;

	inserare_LD(&cap, &coada, f1);
	inserare_LD(&cap, &coada, f2);
	inserare_LD(&cap, &coada, f3);
	inserare_LD(&cap, &coada, f4);
	inserare_LD(&cap, &coada, f5);
	inserare_LD(&cap, &coada, f6);

	printf("\nTRAVERSARE LISTA DUBLA DUPA INSERARE");
	printf("\n\n\tTraversare Normala");
	traversare_normala_LD(cap);

	printf("\n\n\tTraversare inversa");
	traversare_inversa_LD(coada);

	printf("\n\n-------------------");
	int dim = numara_fisiere(cap, ".txt");
	Fisier *vect = vector_f(cap, ".txt");
	
	printf("\nAFISARE ELEMENTE DIN LISTA CARE AU EXTENSIA '.TXT'");
	for (int i = 0; i < dim; i++)
		afisare_fisier(vect[i]);

	printf("\n\n-------------------");
	printf("\nMODIFIC FISIERUL CU PATH: 'C:\\folder5\\Filme' ");
	modifica_LD(cap, f5.extensie_fisier, "D:\\MODIFICAT-haha\\AlteFilme");

	printf("\nTRAVERSEZ LISTA CA SA VAD MODIFICAREA");
	traversare_normala_LD(cap);


	printf("\n\n-------------------");
	Fisier f;
	printf("\nSTERG PRIMUL NOD AL LISTEI");
	extragere_LD(&cap, &coada, f1.extensie_fisier, &f);
	traversare_normala_LD(cap);

	printf("\n\nTERG ULTIMUL NOD AL LISTEI");
	extragere_LD(&cap, &coada, f6.extensie_fisier, &f);
	traversare_normala_LD(cap);

	printf("\n\nSTERG UN NOD AL LISTEI DE LA MIJLOC");
	extragere_LD(&cap, &coada, f3.extensie_fisier, &f);
	traversare_normala_LD(cap);

	dezalocare_LD(&cap);
	printf("\n");
}
