#include <stdio.h>
#include <malloc.h>
#include "Lista_s.h"



int main() {

    /*int nr_produse;
    printf("Nr de produse: ");
    scanf("%d", &nr_produse);
    struct Produs *vp = (struct Produs *)malloc(nr_produse * sizeof(struct Produs))
    citire_vector(vp, nr_produse);
    dezalocare_vector(vp, nr_produse);*/

    struct Produs p;
    int nr_elemente, i;
    printf("\nNr elemente pt lista: "); scanf("%d", &nr_elemente);

    struct Nod *Lista_mea = NULL;
    for(i = 0; i < nr_elemente; i++) { // inserare inversa! primul intrat, devine ultimul
        citire_produs(&p);
        Lista_mea = creareNod(p, Lista_mea);
    }
    printf("\nAfisare inversa: ");
    afisare_lista(Lista_mea);
    Lista_mea = sterge_lista(Lista_mea);


    printf("\nAfisare in ordinea de intrare: ");
    for(i = 0; i < nr_elemente; i++) {
        citire_produs(&p);
        Lista_mea = inserare_sfarsit(Lista_mea, p);
    }
    afisare_lista(Lista_mea);
    Lista_mea = sterge_lista(Lista_mea);
    return 0;
}

