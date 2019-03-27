#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct Masina{
    char *serie;
    int nrKM;
};

struct HashTable{
    struct Masina **vector;
    int dimensiune;
};

void initializare_masina(struct Masina *m, char *s, int nr){
    (*m).nrKM = nr;
    (*m).serie = (char*)malloc(sizeof(char) * (strlen(s) + 1));
    strcpy((*m).serie, s);
}

struct Masina initMasina(const char* serie, int nr) {
    struct Masina m;
    m.serie = (char*)malloc(sizeof(char)*(strlen(serie) + 1));
    strcpy(m.serie, serie);
    m.nrKM = nr;

    return m;
}

void afisare_masina(struct Masina m){
    printf("\nSerie: %s, Nr_Km: %d", m.serie, m.nrKM);
}

struct HashTable initializare_HashTable(int dim){
    int i;
    struct HashTable h;
    h.vector = (struct Masina**)malloc(dim * sizeof(struct Masina*));
    for(i = 0; i < dim; i++){
        h.vector[i] = NULL;
    }
    h.dimensiune = dim;

    return h;
}

int HashFunction(struct HashTable h, struct Masina m){
    int suma = 0, i;
    for(i = 0; i < strlen(m.serie); i++)
        suma += m.serie[i];

    return  suma % h.dimensiune;
}

int inserare_masina(struct HashTable h, struct Masina m){
    if(h.dimensiune > 0){
        int pozitie = HashFunction(h, m);

        if(h.vector[pozitie]){ //am o coliziune
            int index = (pozitie + 1) % h.dimensiune;
            while(h.vector[index] != NULL && index != pozitie){
                index = (index + 1) % h.dimensiune;
            }

            if(index != pozitie){ //pot sa inserez
                h.vector[index] = (struct Masina*)malloc(sizeof(struct Masina));
                *(h.vector[index]) = initMasina(m.serie, m.nrKM);
                return index;
            }
            else
                return -1; //tabela plina deja!!
        }
        else{
            h.vector[pozitie] = (struct Masina *)malloc(sizeof(struct Masina));
            *(h.vector[pozitie]) = initMasina(m.serie, m.nrKM);
            return pozitie;
        }
    }
    else
        return -2; //dimensiunea nu exista, nu am tabela deci
}


int main() {

    struct Masina m;
    initializare_masina(&m, "1", 52000);

    struct HashTable h = initializare_HashTable(4);
    int index = inserare_masina(h, m);
    printf("\nIndex: %d", index);

    return 0;
}