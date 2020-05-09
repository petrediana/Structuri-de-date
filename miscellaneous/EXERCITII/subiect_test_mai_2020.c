#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct Magazin {
    int id;
    char* denumire;
    char* localitate;
    float suprafata;
    int numar_angajati;
};

struct Nod_ls {
    struct Magazin *info;
    struct Nod_ls *next;
};

struct HashTable {
    struct Magazin **vector;
    int dimensiune;
};

// METODE PENTRU STRUCTURA MAGAZIN //
char *aloca_char_steluta(char *cuvant);
struct Magazin *creare_magazin(int id, char *denumire, char *localitate, float suprafata, int nr_ang);
struct Magazin *copiaza_pointer_magazin_deep_copy(struct Magazin *de_copiat);
void afisare_magazin(struct Magazin *magazin);
void dezalocare_memorie_magazin(struct Magazin *magazin);

// METODE PENTRU SORTARE LISTA DUPA ID!!!! //
int numar_elemente_LS(struct Nod_ls *cap) {
	int nr = 0;
	struct Nod_ls *temp = cap;
	while(temp) {
		nr++;
		temp = temp->next;
	}

	return nr;
}

struct Nod_ls *adresa_nod_cu_pozitie_data(struct Nod_ls *cap, int index) {
	int poz = 0;
	struct Nod_ls *temp = cap;
	while (temp) {
		if (index == poz)
			return temp;
		temp = temp->next;
		poz++;
	}
	return NULL;
}

void sortare_LS(struct Nod_ls *cap) {
	int n = numar_elemente_LS(cap);

	for (int i = 0; i < n - 1; ++i) {
		struct Nod_ls* temp1 = adresa_nod_cu_pozitie_data(cap, i);

		for (int j = i + 1; j < n; ++j) {
			struct Nod_ls* temp2 = adresa_nod_cu_pozitie_data(cap, j);

			if (temp1->info->id > temp2->info->id) {
                struct Magazin *aux = temp1->info;
                temp1->info = temp2->info;
                temp2->info = aux;
            }
		}
	}
}

// METODE PENTRU LISTA SIMPLA //
struct Nod_ls *creare_nod_ls(struct Magazin *magazin, struct Nod_ls *next) {
    struct Nod_ls *nou = (struct Nod_ls*)malloc(sizeof(struct Nod_ls));
    
    nou->info = (struct Magazin*)malloc(sizeof(struct Magazin));
    nou->info = copiaza_pointer_magazin_deep_copy(magazin);
    nou->next = next;

    return nou;    
}

struct Nod_ls *inserare_nod_ls(struct Magazin *magazin, struct Nod_ls *cap) {
    struct Nod_ls *nou = creare_nod_ls(magazin, cap);
    sortare_LS(nou);
    return nou;
}

void traversare_lista_simpla(struct Nod_ls *cap) {
    printf("\n\n\t Traversare lista simpla: ");
    while (cap) {
        afisare_magazin(cap->info);
        cap = cap->next;
    }
}

void dezalocare_lista_simpla(struct Nod_ls **cap) {
    while ((*cap)) {
        struct Nod_ls *aux = (*cap);
        (*cap) = (*cap)->next;
        dezalocare_memorie_magazin(aux->info);
        free(aux);
    }
}

// FUNCTIA PENTRU MODIFICARE DENUMIRE EX 2 //
void modifica_denumire_element_ls(struct Nod_ls *cap, char *den_noua, char *den_initiala, char* loc_initiala) {
    if (den_noua == NULL || cap == NULL) {
        return;
    } else {
        while ((cap)) {
            if (strcmp((cap)->info->denumire, den_initiala) == 0
                && strcmp((cap)->info->localitate, loc_initiala) == 0) {
                    
                    free((cap)->info->denumire);
                    (cap)->info->denumire = aloca_char_steluta(den_noua);
                    return;
                }
            (cap) = (cap)->next;
        }
    }
}

// FUNCTIA PENTRU NUMARUL MEDIU DE ANGAJARI EX 3 //
float determina_nr_mediu_angajati(struct Nod_ls *cap, char *loc) {
    if (loc == NULL || cap == NULL) {
        return -1;
    } else {
        float total_angajati = 0;
        float nr_localitati_cu_angajati = 0;
        while (cap) {
            if (strcmp(cap->info->localitate, loc) == 0) {
                ++nr_localitati_cu_angajati;
                total_angajati += (float) cap->info->numar_angajati;
            }
            cap = cap->next;
        }

        return (float)(total_angajati / nr_localitati_cu_angajati);
    }
}

// FUNCTII PENTRU TABELA DISPERSIE //
struct HashTable initializare_tabela_dispersie(int dim) {
    struct HashTable h;
    int i;
    
    h.vector = (struct Magazin**)malloc(sizeof(struct Magazin*) * dim);
    for(i = 0; i < dim; i++){
        h.vector[i] = NULL;
    }        

    h.dimensiune = dim;
    return h;
}

int calcul_functie_hash(struct HashTable h, struct Magazin *magazin){
    int suma = 0, i;
    for(i = 0; i < strlen(magazin->denumire); ++i)
        suma += magazin->denumire[i];

    return (suma % h.dimensiune);
}

int inserare_hash_magazin(struct HashTable h, struct Magazin *magazin){
    if(h.dimensiune > 0) {
        int HashCode = calcul_functie_hash(h, magazin);

        if(h.vector[HashCode]) {
            // coliziune
            int index = (HashCode - 1) % h.dimensiune;
            while(index != HashCode){
                if(h.vector[index] == NULL) { 
                    h.vector[index] = (struct Magazin*)malloc(sizeof(struct Magazin));
                    h.vector[index] = copiaza_pointer_magazin_deep_copy(magazin);
                    break;
                }
                else {
                    index = (index - 1) % h.dimensiune;
                }
            }

            if(index == HashCode) {
                return -1; // tabela este full
            }           

            return index;
        }
        else {
            h.vector[HashCode] = (struct Magazin*)malloc(sizeof(struct Magazin));
            h.vector[HashCode] = copiaza_pointer_magazin_deep_copy(magazin);
            return HashCode;
        }
    }
    else {
        return  -2;
    }
}

void afisare_tabela_dispersie(struct HashTable h){
    int i;
    for(i = 0; i < h.dimensiune; i++){
        if(h.vector[i]) {
            afisare_magazin(h.vector[i]);
            printf(" --- pozitia: %d ", i);
        }
    }
}

struct HashTable insereaza_date_din_lista(struct Nod_ls *cap) {
    int dim = numar_elemente_LS(cap);
    struct HashTable hash = initializare_tabela_dispersie(dim);

    while (cap) {
        inserare_hash_magazin(hash, cap->info);
        cap = cap->next;
    }

    return hash;
}

void dezalocare_HashTable(struct HashTable h) {
	if (h.vector != NULL) {
		for (int i = 0; i < h.dimensiune; i++) {
			if (h.vector[i] != NULL) {
				dezalocare_memorie_magazin(h.vector[i]);
			}
		}
		free(h.vector);
		h.vector = NULL;
	}
}

int main() {
    struct Magazin *m1 = creare_magazin(1, "den1", "loc", 10.01, 10);
    struct Magazin *m2 = creare_magazin(2, "den2", "loc2", 11.01, 11);
    struct Magazin *m3 = creare_magazin(3, "den3", "loc", 11.01, 13);

    struct Nod_ls *lista_simpla = NULL;
    lista_simpla = inserare_nod_ls(m1, lista_simpla);
    lista_simpla = inserare_nod_ls(m2, lista_simpla);
    lista_simpla = inserare_nod_ls(m3, lista_simpla);

    printf("\n\nAFISARE DATE INITIALE");
    traversare_lista_simpla(lista_simpla);

    printf("\n\nMODIFIC NUMELE ELEMENTULUI CU ID 2");
    modifica_denumire_element_ls(lista_simpla, "den NOUA", "den2", "loc2");
    traversare_lista_simpla(lista_simpla);

    printf("\n\nAFISARE NUMAR MEDIU ANGAJATI");
    printf("\n\tNr mediu: %5.2f", determina_nr_mediu_angajati(lista_simpla, "loc"));


    printf("\n\nAFISARE TABELA DISPERSIE");
    struct HashTable hash = insereaza_date_din_lista(lista_simpla);
    afisare_tabela_dispersie(hash);

    dezalocare_lista_simpla(&lista_simpla);
    dezalocare_HashTable(hash);
    return 0;
}

// IMPLEMENTARE METODE PENTRU STRUCTURA MAGAZIN //
char *aloca_char_steluta(char *cuvant) {
    char *cuvant_de_alocat = (char*)malloc(sizeof(char) * (strlen(cuvant) + 1));
    strcpy(cuvant_de_alocat, cuvant);

    return cuvant_de_alocat;
}

struct Magazin *creare_magazin(int id, char *denumire, char *localitate, float suprafata, int nr_ang) {
    struct Magazin *magazin_de_returnat = (struct Magazin*)malloc(sizeof(struct Magazin));
    magazin_de_returnat->id = id;
    magazin_de_returnat->denumire = aloca_char_steluta(denumire);
    magazin_de_returnat->localitate = aloca_char_steluta(localitate);
    magazin_de_returnat->suprafata = suprafata;
    magazin_de_returnat->numar_angajati = nr_ang;

    return magazin_de_returnat;
}

struct Magazin *copiaza_pointer_magazin_deep_copy(struct Magazin *de_copiat) {
    struct Magazin *copie = (struct Magazin*)malloc(sizeof(struct Magazin));
    copie->id = de_copiat->id;
    copie->denumire = aloca_char_steluta(de_copiat->denumire);
    copie->localitate = aloca_char_steluta(de_copiat->localitate);
    copie->suprafata = de_copiat->suprafata;
    copie->numar_angajati = de_copiat->numar_angajati;

    return copie;
}

void afisare_magazin(struct Magazin *magazin) {
    printf("\nId: %d, Denumire: %s, Localitate: %s, Suprafata: %5.2f, Nr_Ang: %d",
        magazin->id, magazin->denumire, magazin->localitate, magazin->suprafata, magazin->numar_angajati);
}

void dezalocare_memorie_magazin(struct Magazin *magazin) {
    free(magazin->denumire);
    free(magazin->localitate);

    free(magazin);
}