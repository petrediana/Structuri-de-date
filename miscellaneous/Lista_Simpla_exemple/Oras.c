#include <stdio.h>
#include <string.h>
#include <malloc.h>


struct Oras{
    char *denumire;
    int cod;
};

struct nod_ls{
    struct Oras info;
    struct nod_ls *next;
};

struct Oras creare_oras(char *n, int c){
    struct Oras o;
    o.denumire = (char*)malloc(sizeof(char) * (strlen(n) + 1));
    strcpy(o.denumire, n);
    o.cod = c;

    return o;
}

void afisare_Oras(struct Oras o){
    printf("\nDenumire: %s, Cod: %d", o.denumire, o.cod);
}

struct nod_ls *inserare_nod(struct Oras o, struct nod_ls *next){
    struct nod_ls *nou = (struct nod_ls*)malloc(sizeof(struct nod_ls));
    nou->info.cod = o.cod;
    nou->info.denumire = (char*)malloc(sizeof(char) * (strlen(o.denumire) + 1));
    strcpy(nou->info.denumire, o.denumire);

    nou ->next = next;

    return nou;
}

struct nod_ls *inserare_inceput(struct Oras o, struct nod_ls *cap){
    struct nod_ls *nou = inserare_nod(o, cap);
    return nou;
}

struct nod_ls *inserare_sfarsit(struct Oras o, struct nod_ls *cap){
    struct nod_ls *nou = inserare_nod(o, NULL);

    if(cap){
        struct nod_ls *temp = cap;
        while(temp->next){
            temp = temp->next;
        }
        temp->next = nou;
    }
    else
        cap = nou;

    return cap;
}


void traversare(struct nod_ls *cap){
    printf("\n\n\tTraversare: ");
    while (cap){
        afisare_Oras(cap->info);
        cap = cap -> next;
    }
}

void dezalocare(struct nod_ls **cap){
    while ((*cap)){
        struct nod_ls *aux = (*cap);
        (*cap) = (*cap) -> next;
        free(aux->info.denumire);
        free(aux);
    }
}

int main() {
    struct Oras o1 = creare_oras("Bucuresti", 1234);
    struct Oras o2 = creare_oras("Iasi", 1000);
    struct Oras o3 = creare_oras("Galati", 3000);

    struct nod_ls *lista_s = NULL;
    lista_s = inserare_sfarsit(o1, lista_s);
    lista_s = inserare_sfarsit(o2, lista_s);
    lista_s = inserare_inceput(o3, lista_s);

    traversare(lista_s);
    dezalocare(&lista_s);

    traversare(lista_s);
    return 0;
}