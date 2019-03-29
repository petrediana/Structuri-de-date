#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct Prajitura{
    char *denumire;
    int nr_prajituri;
};

struct HashTable{
    struct Prajitura **vector;
    int dimensiune;
};

struct Prajitura initializare_prajitura(const char *den, int nr){
    struct Prajitura p;
    p.denumire = (char*)malloc(sizeof(char) * (strlen(den) + 1));
    strcpy(p.denumire, den);
    p.nr_prajituri = nr;

    return p;
}

void afisare_prajitura(struct Prajitura p){
    printf("\nDenumire: %s, Nr: %d", p.denumire, p.nr_prajituri);
}

struct HashTable initializare_hash(int dim){
    struct HashTable h;
    int i;
    h.vector = (struct Prajitura**)malloc(sizeof(struct Prajitura*) * dim);
    for(i = 0; i < dim; i++)
        h.vector[i] = NULL;

    h.dimensiune = dim;

    return h;
}

int hashFunction(struct HashTable h, struct Prajitura p){
    int suma = 0, i;
    for(i = 0; i < strlen(p.denumire); i++)
        suma += p.denumire[i];

    return (suma % h.dimensiune);
}

int inserare_Prajitura(struct HashTable h, struct Prajitura p){
    if(h.dimensiune > 0){
        int HashCode = hashFunction(h, p);
        if(h.vector[HashCode]){
            //coliziune
            int index = (HashCode + 1) % h.dimensiune;
            while(index != HashCode){
                if(h.vector[index] == NULL){
                    h.vector[index] = (struct Prajitura*)malloc(sizeof(struct Prajitura));
                    h.vector[index] ->denumire = (char*)malloc(sizeof(char) * (strlen(p.denumire) + 1));
                    strcpy(h.vector[index]->denumire, p.denumire);
                    h.vector[index]->nr_prajituri = p.nr_prajituri;
                    break;
                }
                else
                    index = (index + 1) % h.dimensiune;
            }

            if(index == HashCode)
                return -1; // tabela este full

            return index;
        }
        else{
            h.vector[HashCode] = (struct Prajitura*)malloc(sizeof(struct Prajitura));
            *(h.vector[HashCode]) = initializare_prajitura(p.denumire, p.nr_prajituri);
            return HashCode;
        }



    }
    else
        return  -2;
}

void afisare_HashTable(struct HashTable h){
    int i;
    for(i = 0; i < h.dimensiune; i++){
        if(h.vector[i])
            afisare_prajitura(*(h.vector[i]));
        else
            printf("\n~~~");
    }
}

int cautare_Hash(struct HashTable h, struct Prajitura p){
    if(h.dimensiune > 0){
        int pozitie = hashFunction(h, p);
        if(strcmp(p.denumire, h.vector[pozitie] ->denumire) == 0)
            return pozitie;
        else{
            int index = (pozitie + 1) % h.dimensiune;
            while(index != pozitie && strcmp(p.denumire, h.vector[index] -> denumire) == 0){
                index = (index + 1) % h.dimensiune;
            }

            if(index == pozitie)
                return -1; // nu exista in tabela
            else
                return index;
        }
    }
    else
        return -2;
}

struct Prajitura stergere_HashTable(struct HashTable h, int index){
    if(h.dimensiune > 0 && h.vector[index] != NULL){
        struct Prajitura temp = *(h.vector[index]);
        free(h.vector[index]);
        h.vector[index] = NULL;
        return temp;
    }
    else
        return initializare_prajitura(" ", 0);
}


int main() {
    struct HashTable hash = initializare_hash(5);
    struct Prajitura p = initializare_prajitura("Profiterol", 3);
    struct Prajitura test = initializare_prajitura("Test", 1);

    inserare_Prajitura(hash, p);
    free(p.denumire);

    p = initializare_prajitura("Amandina", 5);
    inserare_Prajitura(hash, p);
    free(p.denumire);

    struct Prajitura p2 = initializare_prajitura("Tort", 10);
    inserare_Prajitura(hash, p2);
    free(p2.denumire);

    p2 = initializare_prajitura("Crema de zahar ars", 3);
    int index = inserare_Prajitura(hash, p2);
    free(p2.denumire);

    printf("\nIndex: %d", index);
    afisare_HashTable(hash);

    printf("\n---------------------------\n");

    int pozitie_Test = cautare_Hash(hash, test);
    free(test.denumire);
    afisare_prajitura(*(hash.vector[pozitie_Test]));
    return 0;
}