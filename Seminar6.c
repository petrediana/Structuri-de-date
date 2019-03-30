#include <stdio.h>
#include <string.h>
#include <malloc.h>
//tabela de dispersie

//chainning, linear probing quadratic probing, rehasing, overflow area -> cum putem trata coliziunea

//implementare linear probing
struct Student{
    int cod;
    char *nume;
    float medie;
};

struct HashTable{
    struct Student **vect;
    int size;
};

int functieHash(struct HashTable tabela, int cheie){
    return cheie % tabela.size;
}

int inserare(struct HashTable tabela, struct Student *s){
    int pozitie;

    if(tabela.vect != NULL){
        pozitie = functieHash(tabela, (*s).cod);
        if(tabela.vect[pozitie] == NULL){
            tabela.vect[pozitie] = s;
        }
        else{
            int index = 1;
            while(pozitie + index < tabela.size){
                if(tabela.vect[pozitie + index] == NULL){
                    pozitie += index;
                    tabela.vect[pozitie] = s;
                    break;
                }
                index ++;
            }
        }
    }

    return pozitie;
}

void traversare(struct HashTable tabela){
    if(tabela.vect)
        for(int i = 0; i < tabela.size; i++)
            if(tabela.vect[i]) {
                printf("\nPozitie: %d", i);
                printf("\nCod: %d, Nume: %s, Medie %5.2f",
                       tabela.vect[i]->cod, tabela.vect[i]->nume, tabela.vect[i]->medie);
            }
}

void dezalocare(struct HashTable tabela){
    if(tabela.vect)
        for(int i = 0; i < tabela.size; i++)
            if(tabela.vect[i]) {
                free(tabela.vect[i]->nume);
                free(tabela.vect[i]);
            }
    free(tabela.vect);
}

int stergere(struct HashTable tabela, int cod){//cod = cheie de cautare
    int pozitie;
    if(tabela.vect != NULL){
        pozitie = functieHash(tabela, cod);

        if(tabela.vect[pozitie] == NULL)
            return -1;
        else{
            if(tabela.vect[pozitie]->cod == cod){
                free(tabela.vect[pozitie]->nume);
                free(tabela.vect[pozitie]);
                tabela.vect[pozitie] = NULL;
            }
            else{
                int index = 1;
                while(pozitie + index < tabela.size){
                    if(tabela.vect[pozitie + index] != NULL && tabela.vect[pozitie + index] -> cod == cod){
                        free(tabela.vect[pozitie]->nume);
                        free(tabela.vect[pozitie]);
                        tabela.vect[pozitie] = NULL;
                        pozitie += index;
                        break;
                    }
                    index ++;
                }
            }
        }
    }

    return pozitie;
}

int main() {
    int n; // nr de studenti
    printf("\nNr studenti = "); scanf("%d", &n);

    struct HashTable tabela;
    tabela.size = 101;
    tabela.vect = (struct Student **)malloc(sizeof(struct Student*) * tabela.size);

    for(int i = 0; i < tabela.size;i++)
        tabela.vect[i] = NULL;

    struct Student *s;
    char buf[20];

    for(int i = 0; i < n; i++){
        s = (struct Student*)malloc(sizeof(struct Student));
        printf("\nCod: ");
        scanf("%d", &s->cod);

        printf("Nume: ");
        scanf("%s", buf);
        s->nume = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
        strcpy(s->nume, buf);

        printf("Medie: ");
        scanf("%f", &s->medie);

        inserare(tabela, s);
    }

    traversare(tabela);
    stergere(tabela, 505);
    printf("\n--------------------------");
    traversare(tabela);
    dezalocare(tabela);
    return 0;
}