#include <stdio.h>
#include <mem.h>
#include <malloc.h>
#include "lista_dubla.h"


struct Avion creareAvion(char * numep, int nrp){
    struct Avion avion;
    avion.numePilor = (char*)malloc((strlen(numep) + 1) * sizeof(char));
    strcpy(avion.numePilor, numep);
    avion.nrPasageri = nrp;
    return avion;
}

struct Nod_LD *creareNod(struct Avion a, struct Nod_LD *next, struct Nod_LD *prev){
    struct Nod_LD *nou = (struct Nod_LD*)malloc(sizeof(struct Nod_LD));
    nou -> info = creareAvion(a.numePilor, a.nrPasageri);
    nou -> next = next;
    nou -> prev = prev;

    return nou;
}

struct ListaDubla inserareInceput(struct ListaDubla lista, struct Avion a){
    struct Nod_LD *nou = creareNod(a, lista.first, NULL);
    if(lista.first != NULL){
        lista.first -> prev = nou;
        lista.first = nou;
        return lista;
    }
    else{
        lista.first = nou;
        lista.last = nou;
        return lista;
    }
}

struct ListaDubla inserareSfarsit(struct ListaDubla lista, struct Avion a){
    struct Nod_LD *nou = creareNod(a, NULL, lista.last);
    if(lista.last != NULL){
        lista.last ->next = nou;
        lista.last = nou;
    }
    else{//pointeaza catre null
        lista.first = nou;
        lista.last = nou;
    }
    return lista;

}

void afisareAvion(struct Avion avion){
    printf("\nNume: %s, NrPasageri: %d", avion.numePilor, avion.nrPasageri);
}

void afisare_Inceput_spre_Sfarsit(struct ListaDubla lista){
    struct Nod_LD *p = lista.first;
    while(p != NULL){
        afisareAvion(p -> info);
        p = p -> next;
    }
    printf("\n");
}

void afisare_Sfarsit_spre_Inceput(struct ListaDubla lista){
    struct Nod_LD *p = lista.last;
    while(p != NULL){
        afisareAvion(p->info);
        p = p -> prev;
    }
    printf("\n");
}

void stergereLista(struct ListaDubla *lista){
    struct Nod_LD *p = lista->first;
    while(p != NULL){ //pointez catre un nod care exista
        free(p->info.numePilor);
        struct Nod_LD *temp = p;
        p = p->next;
        free(temp);
    }
    lista -> first = NULL;
    lista -> last = NULL;
}

