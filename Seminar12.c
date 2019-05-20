#include <stdio.h>
#include <malloc.h>
#include <string.h>

// grafuri -> multime noduri, multime arce
// (coada + stiva) pentru a parcurge graful
// coada = parcurgere in latime
// stiva = parcurgere in lungime

// o alta representare a grafului -> lista de adiacenta
// o lista simpla cu nodurile, fiecare element avand un pointer catre o lista cu vecinii nodului
// o lista de liste (o construiec de la inceput fara sa tin cont de matricea de adiacenta)

struct nod_Stiva{
    int inf; //id-ul nodului
    struct nod_Stiva *next;
};

struct nod_Coada{
    int inf;
    struct nod_Coada *next;
};


void push(struct nod_Stiva **varf, int val){
    struct nod_Stiva *nou = (struct nod_Stiva*)malloc(sizeof(struct nod_Stiva));

    nou->inf = val;
    nou->next = NULL;

    if(*varf == NULL){
        *varf = nou;
    }
    else {
        nou -> next = *varf;
        *varf = nou;
        //inserez la inceput
    }
}

void pop(struct nod_Stiva **varf, int *val){
    if(*varf == NULL)
        return;
    else {
        *val = (*varf) -> inf;
        struct nod_Stiva *aux = *varf;
        *varf = (*varf)-> next;
        free(aux);
    }
}

void put(struct nod_Coada **prim, struct nod_Coada **ultim, int val) {
    struct nod_Coada *nou = (struct nod_Coada*)malloc(sizeof(struct nod_Coada));
    nou -> inf = val;
    nou -> next = NULL;

    if((*prim) == NULL && (*ultim) == NULL){
        (*prim) = nou;
        (*ultim) = nou;
    }
    else {
        (*ultim) -> next = nou;
        (*ultim) = nou;
        //inserez la sfarsit
    }
}

void get(struct nod_Coada **prim, struct nod_Coada **ultim, int *val){
    if((*prim) != NULL && (*ultim) != NULL) {
        *val = (*prim) -> inf;
        struct nod_Coada *aux = *prim;
        (*prim) = (*prim) -> next;
        free(aux);
    }

    if((*prim) == NULL)
        (*ultim) == NULL;
}


int main() {

    int nr; // numarul de noduri
    printf("\nNumar noduri: "); scanf("%d", &nr);

    int **mat = (int**)malloc(sizeof(int*) * nr);
    for(int i = 1; i <= nr; i ++)
        mat[i] = (int*)malloc(sizeof(int) * nr);

    for (int i = 1; i <= nr; i++) {
        for (int j = 1; j <= nr; j++) {
            mat[i][j] = 0;
        }
    }

    int nr_arce;
    printf("Numar arce: "); scanf("%d", &nr_arce);

    int ii, jj; //index sursa, destinatie
    for(int i = 0; i < nr_arce; i++) {
        printf("Sursa = ");
        scanf("%d", &ii);
        printf("Destinatia = ");
        scanf("%d", &jj);

        if (ii <= nr && jj <= nr) {
            mat[ii][jj] = 1;
            mat[jj][ii] = 1;
        }
    }

    int *vizitat = (int*)malloc(sizeof(int) * nr);
    for(int i = 1; i <= nr; i++)
        vizitat[i] = 0;

    /*printf("\nParcurgere in adancime de la nodul: ");
    int nod;
    scanf("%d", &nod);

    struct nod_Stiva *varf = NULL;
    push(&varf, nod);
    vizitat[nod] = 1;

    //parcurgere in adancime
    while (varf != NULL) {
        //atat timp cat stiva este nevida, il scot
        pop(&varf, &nod);
        printf("%d- ", nod);

        for(int k = 1; k <= nr; k++)
            if(mat[nod][k] == 1 && vizitat[k] == 0) {
                push(&varf, k);
                vizitat[k] = 1;
            }
    }*/


    //parcurgere in latime
    for(int i = 1; i <= nr; i++)
        vizitat[i] = 0;

    int nod;

    printf("\nParcurgere in latime de la nodul: ");
    scanf("%d", &nod);

    struct nod_Coada *prim = NULL, *ultim = NULL;
    put(&prim, &ultim, nod);
    vizitat[nod] = 1;

    //parcurgere in latime
    while (prim != NULL) {
        get(&prim, &ultim, &nod);
        printf("%d- ", nod);

        for(int k = 1; k <= nr; k++)
            if(mat[nod][k] == 1 && vizitat[k] == 0) {
                put(&prim, &ultim, nod);
                vizitat[k] = 1;
            }
    }


    return 0;
}