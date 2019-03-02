#include <mem.h>
#include "lista_dubla.h"


int main() {
    struct ListaDubla lista;
    lista.first = NULL;
    lista.last = NULL;

    struct Avion avion1 = creareAvion("nume1", 100);
    struct Avion avion2 = creareAvion("nume2", 101);
    struct Avion avion3 = creareAvion("nume3", 102);
    lista = inserareInceput(lista, avion1);
    lista = inserareInceput(lista, avion2);
    lista = inserareInceput(lista, avion3);

    afisare_Inceput_spre_Sfarsit(lista);
    afisare_Sfarsit_spre_Inceput(lista);

    stergereLista(&lista);

    lista = inserareSfarsit(lista, avion1);
    lista = inserareSfarsit(lista, avion2);
    lista = inserareSfarsit(lista, avion3);
    afisare_Inceput_spre_Sfarsit(lista);
    afisare_Sfarsit_spre_Inceput(lista);

    stergereLista(&lista);

    return 0;
}