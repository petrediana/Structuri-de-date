#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

struct nod_LD{
    int info;
    struct nod_LD *prev;
    struct nod_LD *next;
};


struct nod_LD *inserare_nod(int info){
    struct nod_LD *nou =(struct nod_LD*)malloc(sizeof(struct nod_LD));
    nou->info = info;
    nou->prev = NULL;
    nou->next = NULL;

    return nou;
}


void inserare_sfarsit(struct nod_LD **prim, struct nod_LD **ultim, int info){
    struct nod_LD *nou = inserare_nod(info);

    if((*prim) == NULL && (*ultim) == NULL){
        //lista mea este vida
        (*prim) = nou;
        (*ultim) = nou;
    }
    else{
        //am elemente in lista
        nou ->prev =(*ultim);
        (*ultim) -> next = nou;
        (*ultim) = nou;
    }
}

void inserare_inceput(struct nod_LD **prim, struct nod_LD **ultim, int info){
    struct nod_LD *nou = inserare_nod(info);

    if((*prim) == NULL && (*ultim) == NULL){
        (*prim) = nou;
        (*ultim) = nou;
    }
    else{
        nou -> next = (*prim);
        (*prim) -> prev = nou;
        (*prim) = nou;
    }
}

void traversare_(struct nod_LD *prim){
    struct nod_LD *temp = prim;
    while(temp){
        printf("\nNumar: %d", temp->info);
        temp = temp->next;
    }
}

void traversare_inversa(struct nod_LD *ultim){
    struct nod_LD *temp = ultim;
    while(temp){
        printf("\nNumar: %d", temp->info);
        temp = temp->prev;
    }
}

bool cautare_element_LD(struct nod_LD *prim, int cautat){
    struct nod_LD *aux = prim;
    bool ok = false;

    if(aux != NULL){
        while(aux){
            if(aux->info == cautat){
                ok = true;
                return true;
            }
            aux = aux -> next;
        }
        if(!ok)
            return false;
    }
    else
        return false;
}


void inserare_la_stanga_unui_element(struct nod_LD **prim, int info_de_inserat, int element){
    if(cautare_element_LD((*prim), element) == false){
        printf("\nElementul in a carui stanga vrem sa inseram nu exista!");
        return;
    }
    else{
        printf("\nElementul exista in lista dubla");
        struct nod_LD *nou = inserare_nod(info_de_inserat); //nodul pe care vreau sa il inserez
        struct nod_LD *nod_dreapta = *prim;
        struct nod_LD *nod_stanga = NULL;

        while(nod_dreapta){
            if(nod_dreapta ->info == element && nod_stanga == NULL){
                /*nou -> next = nod_dreapta;
                nod_dreapta -> prev = nou;
                nod_dreapta = nou;*/
                inserare_inceput(prim, prim, info_de_inserat);

                return;
            }

            if(nod_dreapta -> info == element && nod_stanga != NULL){
                nou -> next = nod_dreapta;
                nou -> prev = nod_stanga;

                nod_dreapta -> prev = nou;
                nod_stanga -> next = nou;
                return;
            }
            else{
                nod_stanga = nod_dreapta;
                nod_dreapta = nod_dreapta -> next;
            }

        }
    }
}


int main() {

    struct nod_LD *cap = NULL;
    struct nod_LD *coada = NULL;

    inserare_sfarsit(&cap, &coada, 1);
    inserare_sfarsit(&cap, &coada, 2);
    inserare_sfarsit(&cap, &coada, 3);
    inserare_sfarsit(&cap, &coada, 4);

    printf("\n---------INSERARE SFARSIT---------");
    printf("\n\tTraversare de la primul element:");
    traversare_(cap);

    printf("\n\tTraversare de la ultimul element:");
    traversare_inversa(coada);


    struct  nod_LD *cap2 = NULL;
    struct nod_LD *coada2 = NULL;

    inserare_inceput(&cap2, &coada2, 1);
    inserare_inceput(&cap2, &coada2, 2);
    inserare_inceput(&cap2, &coada2, 3);
    inserare_inceput(&cap2, &coada2, 4);

    printf("\n---------INSERARE INCEPUT---------");
    printf("\n\tTraversare de la primul element:");
    traversare_(cap2);

    printf("\n\tTraversare de la ultimul element:");
    traversare_inversa(coada2);

    printf("\n\n%s", (cautare_element_LD(cap, 5)) ? "true" : "false");
    printf("\n%s", (cautare_element_LD(cap2, 3)) ? "true" : "false");

    printf("\n\n------------------------------------");
    inserare_la_stanga_unui_element(&cap, 100, 4);
    traversare_(cap);

    inserare_la_stanga_unui_element(&cap, 500, 1);
    traversare_(cap);

    return 0;
}