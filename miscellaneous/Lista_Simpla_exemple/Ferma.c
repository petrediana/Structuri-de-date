#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct Ferma{
    char *nume;
    int nrAnimale;
};


struct nod_ls{
    struct Ferma info;
    struct nod_ls *next;
};

struct Ferma creare_ferma(const char *n, int nr){
    struct Ferma f;
    f.nrAnimale = nr;
    f.nume = (char*)malloc(sizeof(char) * (strlen(n) + 1));
    strcpy(f.nume, n);

    return f;
}

struct nod_ls *inserare_nod(struct Ferma f, struct nod_ls *next){
    struct nod_ls *nou = (struct nod_ls*)malloc(sizeof(struct nod_ls));
    nou->info.nume = (char*)malloc(sizeof(char) * (strlen(f.nume) + 1));
    strcpy(nou->info.nume, f.nume);
    nou->info.nrAnimale = f.nrAnimale;
    nou->next = next;

    return nou;
}

struct nod_ls *inserare_inceput(struct Ferma f, struct nod_ls *cap){
    struct nod_ls *nou = inserare_nod(f, cap);
    return nou;
}

struct nod_ls *inserare_sfarsit(struct Ferma f, struct nod_ls *cap){
    struct nod_ls *nou = inserare_nod(f, NULL);
    if(cap){
        struct nod_ls *temp = cap;
        while(temp->next){
            temp = temp -> next;
        }
        temp->next = nou;
    }
    else
        cap = nou;

    return cap;
}

void traversare(struct nod_ls *cap){
    printf("\n\tTraversare: ");
    while(cap){
        printf("\nNume: %s, Nr Animale: %d", cap->info.nume, cap->info.nrAnimale);
        cap = cap ->  next;
    }
}

void dezalocare(struct nod_ls **cap){
    while((*cap)){
        struct nod_ls *aux = *cap;
        (*cap) = (*cap) ->next;
        free(aux->info.nume);
        free(aux);
    }
}



int main() {

    struct Ferma f1 = creare_ferma("Ferma1", 3);
    struct Ferma f2 = creare_ferma("Ferma2", 4);
    struct Ferma f3 = creare_ferma("Ferma3", 5);
    struct Ferma f4 = creare_ferma("Ferma4", 100);
    struct Ferma f5 = creare_ferma("Ferma5555", 200);

    struct nod_ls *lista_s = NULL;
    lista_s = inserare_sfarsit(f1, lista_s);
    lista_s = inserare_sfarsit(f2, lista_s);

    lista_s = inserare_inceput(f3, lista_s);
    lista_s = inserare_inceput(f4, lista_s);

    lista_s = inserare_sfarsit(f4, lista_s);
    lista_s = inserare_sfarsit(f5, lista_s);

    lista_s = inserare_inceput(f1, lista_s);

    printf("\n\n\n%s", lista_s->info.nume);

    traversare(lista_s);
    dezalocare(&lista_s);


    traversare(lista_s);

    return 0;
}