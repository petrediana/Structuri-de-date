#include <stdio.h>
#include <malloc.h>
#include <string.h>
/*
 * vector -> spatiu contiguu de memorie
 * lista -> [4B inf utila(int)], [4B pointer de legatura](contine adresa urmatorului nod)
 *
 */

struct Produs{
    int *cod;
    char *denumire;
    float pret;
    float cantitate;
};

struct Nod{
    struct Produs *info;
    struct Nod *next;
    struct Nod *prev;
};

struct Nod *inserare(struct Nod *cap, struct Produs *p){
    struct Nod *nodNou = (struct Nod *)malloc(sizeof(struct Nod));
    nodNou->info = (struct Produs *)malloc(sizeof(struct Produs));

    nodNou->info->cod = (int *)malloc(sizeof(int));

   *(nodNou -> info->cod) = *(p->cod);
    nodNou ->info->denumire = (char *)malloc((strlen(p->denumire) + 1) * sizeof(char));
    strcpy(nodNou->info->denumire, p->denumire);
    nodNou->info->cantitate = p->cantitate;
    nodNou->info->pret = p->pret;
    nodNou->next = NULL;
    nodNou->prev = NULL;

    if(cap == NULL)
        cap = nodNou;
    else{
        struct Nod *temp = cap;
        while(temp -> next != NULL){
            temp = temp -> next;
        }
        temp ->next = nodNou;
        nodNou->prev = temp;
    }
    return cap;
}

void traversare(struct Nod *cap){
    struct Nod *temp = cap;
    while(temp != NULL){
        printf("\nCod: %d, Denumire: %s, Pret %5.2f, Cantiate: %5.2f |",
               *(temp->info->cod), temp->info->denumire, temp->info->pret, temp->info->cantitate);
        temp = temp -> next;
    }
}

void dezalocare(struct Nod *cap){
    struct Nod *temp = cap;
    while(temp != NULL){
        free(temp->info->denumire);
        free(temp->info->cod);
        struct Nod *temp2 = temp -> next;
        free(temp -> info);
        free(temp);
        temp = temp2;
    }
}

int main() {
    int nr_produse;
    printf("\nNr produse: "); scanf("%d", &nr_produse);

    struct Nod *cap = NULL;
    struct Produs *p= NULL;
    char buf[20];

    for(int i = 0; i < nr_produse; i++){
        p = (struct Produs*)malloc(sizeof(struct Produs));
        p->cod = (int *)malloc(sizeof(int));
        printf("\nCod: "); scanf("%d", p->cod);
        printf("Denumire: "); scanf("%s", buf);
        p->denumire = (char*)malloc((strlen(buf) + 1) * sizeof(char));
        strcpy(p->denumire, buf);
        printf("Pret: "); scanf("%f", &p->pret);
        printf("Cantitate: "); scanf("%f", &p->cantitate);

        cap = inserare(cap, p);
        free(p->denumire);
        free(p->cod);
        free(p);
    }
    traversare(cap);
    dezalocare(cap);

    return 0;
}