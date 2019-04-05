#include <stdio.h>
#include <malloc.h>
#include <string.h>
//channing
//vector care are pointeri la o lista simpla

struct Student{
    int cod;
    char *nume;
    float medie;
};

struct Nod_LS{
    struct Student info;
    struct Nod_LS *next;
};

struct HashTable{
    struct Nod_LS **vect;
    int size;
};

int functia_Hash(struct HashTable tabela, int cheie){
    return cheie % tabela.size;
}

int inserare(struct HashTable tabela, struct Student s){
    //returnez pozitia din cardul vectorului unde am inserat
    int pozitie = -1;

    if(tabela.vect != NULL){
        pozitie = functia_Hash(tabela, s.cod);
        struct Nod_LS *nou = (struct Nod_LS*)malloc(sizeof(struct Nod_LS));
        nou->info.cod = s.cod;
        nou->info.nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1));
        strcpy(nou->info.nume, s.nume);
        nou->info.medie = s.medie;
        nou->next = NULL;

        if(tabela.vect[pozitie] == NULL){
            tabela.vect[pozitie] = nou;
        }
        else{
            struct Nod_LS *temp = tabela.vect[pozitie];
            while(temp->next)
                temp = temp->next;
            temp->next = nou;
        }
    }

    return pozitie;
}

void traversare(struct HashTable tabela){
    if(tabela.vect != NULL){
        for(int i = 0; i < tabela.size; i++){
            if(tabela.vect[i] != NULL){
                struct Nod_LS *temp = tabela.vect[i];
                printf("\nPozitia: %d", i);
                while(temp){
                    printf("\nCod: %d, Nume: %s, Medie: %5.2f", temp->info.cod,
                            temp->info.nume, temp->info.medie);
                    temp = temp->next;
                }
            }
        }
    }
}


void dezalocare(struct HashTable tabela){
    if(tabela.vect != NULL){
        for(int i = 0; i < tabela.size; i++) {
            if (tabela.vect[i] != NULL) {
                struct Nod_LS *temp = tabela.vect[i];
                while(temp){
                    struct Nod_LS *temp2 = temp ->next;
                    free(temp->info.nume);
                    free(temp);
                    temp = temp2;
                }

            }
        }
}
        free(tabela.vect);
}

int stergere(struct HashTable tabela, int cod){
    int poziie = -1;

    if(tabela.vect != NULL){
        poziie = functia_Hash(tabela, cod);

        if(tabela.vect[poziie] == NULL)
            return -1;
        else{
            if(tabela.vect[poziie]->info.cod == cod){
                if(tabela.vect[poziie] ->next == NULL){
                    struct Nod_LS *temp = tabela.vect[poziie];
                    free(temp->info.nume);
                    free(temp);
                    tabela.vect[poziie] = NULL;
                }
                else{
                    struct Nod_LS *temp = tabela.vect[poziie];
                    tabela.vect[poziie] = temp -> next;
                    free(temp->info.nume);
                    free(temp);
                }
            }
            else{
                struct Nod_LS *temp = tabela.vect[poziie];
                while(temp->next != NULL && temp ->next->info.cod != cod)
                    temp = temp->next;

                struct Nod_LS *p = temp->next;
                if(p->next != NULL){
                    //e la jumate in lista
                    temp -> next = p->next;
                    free(p->info.nume);
                    free(p);
                }
                else{
                    temp -> next = NULL;
                    free(p->info.nume);
                    free(p);
                }
            }
        }
    }

    return poziie;
}

int main() {
    int n;
    printf("\nNr studenti: "); scanf("%d", &n);

    struct HashTable tabela;
    tabela.size = 101;
    tabela.vect = (struct Nod_LS **)malloc(sizeof(struct Nod_LS*) * tabela.size);
    for(int i = 0; i < tabela.size; i++)
        tabela.vect[i] = NULL;

    char buf[20];
    struct Student s;
    for(int i = 0; i < n; i++){
        printf("\nCod = "); scanf("%d", &s.cod);
        printf("Nume = "); scanf("%s", buf);
        s.nume = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
        strcpy(s.nume, buf);
        printf("Medie = "); scanf("%f", &s.medie);

        inserare(tabela, s);
    }

    traversare(tabela);

    stergere(tabela, 205);
    printf("\n------");
    traversare(tabela);


    dezalocare(tabela);
    return 0;
}