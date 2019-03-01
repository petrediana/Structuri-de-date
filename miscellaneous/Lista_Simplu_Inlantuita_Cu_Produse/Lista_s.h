
#ifndef LISTA_SIMPLU_INLANTUITA_LISTA_S_H
#define LISTA_SIMPLU_INLANTUITA_LISTA_S_H

struct Produs{
    int cod;
    char *denumire;
    float pret;
    float cantitate;
};

struct Nod{
    struct Produs info;
    struct Nod *next;
};

void citire_vector(struct Produs *p, int nr_p);
void afisare_vector(struct Produs *p, int nr_p);
void afisare_produs(struct Produs p);
void citire_produs(struct Produs *p);
void dezalocare_vector(struct Produs *p, int nr_p);
struct Nod *creareNod(struct Produs p, struct Nod *n_next);
void afisare_lista (struct Nod *l);
struct Nod *sterge_lista(struct Nod *lista);
struct Nod *inserare_sfarsit(struct Nod *l, struct Produs p);

#endif //LISTA_SIMPLU_INLANTUITA_LISTA_S_H
