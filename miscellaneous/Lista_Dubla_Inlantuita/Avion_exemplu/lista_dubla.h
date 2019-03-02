

#ifndef LISTA_DUBLU_INLANTUITA_LISTA_DUBLA_H
#define LISTA_DUBLU_INLANTUITA_LISTA_DUBLA_H

struct Avion{
    char *numePilor;
    int nrPasageri;
};

struct Nod_LD{
    struct Avion info;
    struct Nod_LD *next;
    struct Nod_LD *prev;
};

struct ListaDubla{
    struct Nod_LD *first;
    struct  Nod_LD *last;
};

struct Avion creareAvion(char * numep, int nrp);
struct Nod_LD *creareNod(struct Avion a, struct Nod_LD *next, struct Nod_LD *prev);
struct ListaDubla inserareInceput(struct ListaDubla lista, struct Avion a);
struct ListaDubla inserareSfarsit(struct ListaDubla lista, struct Avion a);
void afisareAvion(struct Avion avion);
void afisare_Inceput_spre_Sfarsit(struct ListaDubla lista);
void afisare_Sfarsit_spre_Inceput(struct ListaDubla lista);
void stergereLista(struct ListaDubla *lista);

#endif //LISTA_DUBLU_INLANTUITA_LISTA_DUBLA_H
