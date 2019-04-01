#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct Persoana{
    char *nume;
    int varsta;
};

struct Nod_Coada{
    struct Persoana info;
    struct Nod_Coada *next;
};

struct Persoana creare_persoana(const char *nume, int varsta){
    struct Persoana p;
    p.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(p.nume, nume);
    p.varsta = varsta;

    return p;
}

struct Nod_Coada *inserare_Nod(struct Persoana p, struct Nod_Coada *next){
    struct Nod_Coada *nou = (struct Nod_Coada*)malloc(sizeof(struct Nod_Coada));
    nou->info.nume = (char*)malloc(sizeof(char) * (strlen(p.nume) + 1));
    strcpy(nou->info.nume, p.nume);
    nou->info.varsta = p.varsta;
    nou -> next = next;

    return nou;
}

void put(struct Nod_Coada **prim, struct Nod_Coada **ultim, struct Persoana p){
    struct Nod_Coada *nou = inserare_Nod(p, NULL);

    if(*prim == NULL && *ultim == NULL){ //daca la inceput e vida
        (*prim) = nou;
        (*ultim) = nou;
    }
    else{
        (*ultim) -> next = nou;
        (*ultim) = nou;
    }
}

int get(struct Nod_Coada **prim, struct Nod_Coada **ultim, struct Persoana *p){
    if(*prim != NULL && *ultim != NULL){
        (*p).nume = (char*)malloc(sizeof(char) * (strlen((*prim)->info.nume) + 1));
        strcpy((*p).nume, (*prim)->info.nume);
        (*p).varsta = (*prim)->info.varsta;

        struct Nod_Coada *aux = (*prim);
        (*prim) = (*prim) -> next;

        free(aux->info.nume);
        free(aux);
        return 0;
    }
    else{
        if((*prim) == NULL)
            (*ultim) = NULL;
        return -1;
    }
}


void traversare(struct Nod_Coada *prim){
    struct Nod_Coada *temp = prim;

    while(temp){
        printf("\nNume: %s, Varsta: %d", temp->info.nume, temp->info.varsta);
        temp = temp -> next;
    }
}

void conversie_coada_vector(struct Nod_Coada **prim, struct Nod_Coada **ultim, struct Persoana *vect, int *nr){
    struct Persoana p;

    while(get(prim, ultim, &p) == 0)
        vect[(*nr) ++] = p;
}


int main(){

    struct Nod_Coada *cap = NULL;
    struct Nod_Coada *coada = NULL;
    struct Persoana p;
    int nr_persoane, i;
    char buf[20];

    printf("\nNumar persoane: "); scanf("%d", &nr_persoane);
    for(i = 0; i < nr_persoane; i++){
        printf("\nVarsta: ");
        scanf("%d", &p.varsta);

        printf("Nume: ");
        scanf(" %[^\n]s", buf);
        p.nume = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
        strcpy(p.nume, buf);

        put(&cap, &coada, p);
        free(p.nume);
    }

    traversare(cap);

    return 0;
}