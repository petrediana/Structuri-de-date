#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Lista_s.h"


void citire_produs(struct Produs *p){
    char buf[20];

    printf("\nCod: "); scanf("%d", &p->cod);

    printf("\nDenumire: "); scanf("%s", buf);
    p->denumire = (char*)malloc((strlen(buf) + 1) *sizeof(char));
    strcpy(p->denumire, buf);

    printf("\nPretul: "); scanf("%f", &p->pret);
    printf("\nCantitate: "); scanf("%f", &p->cantitate);
}

void afisare_produs(struct Produs p){
    printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f|",
           p.cod, p.denumire, p.pret, p.cantitate);
}


void citire_vector(struct Produs *p, int nr_p){
    char buf[20];
    int i;

    for(i = 0 ; i < nr_p; i++){
        printf("\nCod: "); scanf("%d", &p[i].cod);

        printf("\nDenumire: "); scanf("%s", buf);
        p[i].denumire = (char*)malloc((strlen(buf) + 1) *sizeof(char));
        strcpy(p[i].denumire, buf);

        printf("\nPretul: "); scanf("%f", &p[i].pret);
        printf("\nCantitate: "); scanf("%f", &p[i].cantitate);


    }
}

void afisare_vector(struct Produs *p, int nr_p){
    int i;
    for(i = 0; i < nr_p; i++){
        printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f|",
               p[i].cod, p[i].denumire, p[i].pret, p[i].cantitate);

    }
}

void dezalocare_vector(struct Produs *p, int nr_p){
    int i;
    for(i = 0;i < nr_p; i++){
        free(p[i].denumire);
    }
    free(p);
}

struct Nod *creareNod(struct Produs p, struct Nod *n_next){
    struct Nod *nodNou = (struct Nod*)malloc(sizeof(struct Nod));

    nodNou -> info = p;
    nodNou -> info.denumire = (char*)malloc(strlen(p.denumire) * sizeof(char) + 1);
    strcpy(nodNou -> info.denumire, p.denumire);
    nodNou -> next = n_next;

    return nodNou;
}
void afisare_lista (struct Nod *l){
    while(l != NULL){
        afisare_produs(l -> info);
        l = l -> next;
    }
}

struct Nod *sterge_lista(struct Nod *lista){
    while(lista != NULL){
        free(lista->info.denumire);
        struct Nod *copie_temporara = lista;
        lista = lista -> next;
        free(copie_temporara);
    }
    return NULL;
}

struct Nod *inserare_sfarsit(struct Nod *l, struct Produs p){
    if(l != NULL){
        struct Nod *deplasare = l;
        while (deplasare->next != NULL){
            deplasare = deplasare -> next;
        }//ma pozitionez pe ultimul nod
        deplasare -> next = creareNod(p, NULL);
        return l;
    }
    else{//nu am lista.. l == null
        return creareNod(p, NULL);
    }
}