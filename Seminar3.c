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

void inserare(struct Nod **cap, struct Produs *p, struct Nod **coada){
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

    if(*cap == NULL) {
        *cap = nodNou;
        nodNou->next = *cap;
        nodNou->prev = *cap;
        *coada = nodNou;
    }
    else{
        struct Nod *temp = *cap;
        while(temp -> next != *cap){
            temp = temp -> next;
        }
        temp ->next = nodNou;
        nodNou->prev = temp;
        *coada = nodNou;

        (*coada) -> next = *cap;
        (*cap) -> prev = *coada;
    } //lista dubla circulara
    //return cap;
}

void traversare(struct Nod *cap){
    struct Nod *temp = cap;
    while(temp ->next != cap){
        printf("\nCod: %d, Denumire: %s, Pret %5.2f, Cantiate: %5.2f |",
               *(temp->info->cod), temp->info->denumire, temp->info->pret, temp->info->cantitate);
        temp = temp -> next;
    }
    printf("\nCod: %d, Denumire: %s, Pret %5.2f, Cantiate: %5.2f |",
           *(temp->info->cod), temp->info->denumire, temp->info->pret, temp->info->cantitate);
}

void dezalocare(struct Nod *cap){
    struct Nod *temp = cap;
    while(temp->next != cap){
        free(temp->info->denumire);
        free(temp->info->cod);
        struct Nod *temp2 = temp -> next;
        free(temp -> info);
        free(temp);
        temp = temp2;
    }
    free(temp->info->denumire);
    free(temp->info->cod);
    free(temp -> info);
    free(temp);
}

void traversare_inversa(struct Nod *coada){
    struct Nod *temp = coada;
    while(temp -> prev != coada){
        printf("\nCod: %d, Denumire: %s, Pret %5.2f, Cantiate: %5.2f |",
               *(temp->info->cod), temp->info->denumire, temp->info->pret, temp->info->cantitate);
        temp = temp -> prev;
    }
    printf("\nCod: %d, Denumire: %s, Pret %5.2f, Cantiate: %5.2f |",
           *(temp->info->cod), temp->info->denumire, temp->info->pret, temp->info->cantitate);
}

void conversie_lista_Vector(struct Nod **cap, struct Produs **vect, int *nr){
    struct Nod *temp = *cap;
    while(temp -> next != *cap){
        vect[*nr] = temp -> info;
        (*nr) ++;

        struct Nod *temp2 = temp -> next;
        free(temp);
        temp = temp2;
    }
    vect[*nr] = temp -> info;
    (*nr) ++;
    free(temp);
}

void sterge_produs_denumire(struct Nod **cap, struct Nod **coada, char *den){
    if( strcmp((*cap) -> info -> denumire, den) == 0){ // cazul in care e la inceputul listei
        struct Nod *aux = *cap;

        (*cap) = (*cap) -> next;
        (*coada) -> next = (*cap);
        (*cap) -> prev = *coada;

        free(aux -> info->cod);
        free(aux->info->denumire);
        free(aux->info);
        free(aux);

        return;
    }
    else{
        struct Nod *temp = *cap;
        while(temp -> next != *cap){
            if(strcmp(temp -> info -> denumire, den) == 0){ // cazul in care e pe la mijloc
                struct Nod *urmator = temp -> next;
                struct Nod *anterior = temp -> prev;

                anterior -> next = urmator;
                urmator -> prev = anterior;

                free(temp -> info -> cod);
                free(temp -> info -> denumire);
                free(temp -> info);
                free(temp);
                return;
            }
            else{
                temp = temp -> next;
            }
        }

        if(strcmp(temp -> info -> denumire, den) == 0){ //cazul in care e ultimul nod
            struct Nod *urmator = temp -> next;
            struct Nod *anterior = temp -> prev;

            anterior -> next = urmator;
            urmator -> prev = anterior;

            free(temp -> info -> cod);
            free(temp -> info -> denumire);
            free(temp -> info);
            free(temp);
            return;
        }
    }
}

int main() {
    int nr_produse;
    printf("\nNr produse: "); scanf("%d", &nr_produse);

    struct Nod *cap = NULL;
    struct Nod *coada = NULL;
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

        inserare(&cap, p, &coada);
        free(p->denumire);
        free(p->cod);
        free(p);
    }
    traversare(cap);
    printf("\nTraversare invers: \n");
    traversare_inversa(coada);
    //dezalocare(cap);


    char denumire[30];
    printf("\nDenumire produs de sters: "); scanf("%s", denumire);
    sterge_produs_denumire(&cap, &cap, denumire);






    struct Produs **vect = (struct Produs**)malloc(sizeof(struct Produs*) * nr_produse);
    int nr = 0;
    conversie_lista_Vector(&cap, vect, &nr);


    printf("\nAfisare vector: \n");
    for(int i = 0; i < nr; i++){
        printf("\nCod: %d, Denumire: %s, Pret %5.2f, Cantiate: %5.2f |",
               *(vect[i] -> cod), vect[i]->denumire, vect[i]->pret,vect[i]->cantitate);
    }

    for(int i = 0; i < nr; i++){
        free(vect[i] -> cod);
        free(vect[i] -> denumire);
        free(vect[i]);
    }
    free(vect);

    return 0;
}