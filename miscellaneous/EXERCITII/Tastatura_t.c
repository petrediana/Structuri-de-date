#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Tastatura{
    int cod;
    char *producator;
    int numarButoane;
    float pret;
};

typedef struct nod_LD{
    struct Tastatura info;
    struct nod_LD *next;
    struct nod_LD *prev;
};
struct Tastatura creare_Tastatura(int c, char *den, int nr, float pret){
    struct Tastatura t;
    t.cod = c;
    t.producator = (char*)malloc(sizeof(char) * (strlen(den) + 1));
    strcpy(t.producator, den);
    t.numarButoane = nr;
    t.pret = pret;

    return t;
}

void sortare_Tastaturi_crescator(struct Tastatura *vect, int nr_t){
    struct Tastatura aux;
    for(int i = 0; i < nr_t - 1; i++){
        for(int j = i + 1; j < nr_t; j++){
            if(vect[i].pret < vect[j].pret){
                aux = vect[i];
                vect[i] = vect[j];
                vect[j] = aux;
            }
        }
    }
}

void afisare_Tastatura(struct Tastatura t){
    printf("\nCod: %d, Producator: %s, Numar_Butoane: %d, Pret: %5.2f",
           t.cod, t.producator, t.numarButoane, t.pret);
}

struct nod_LD *inserare_nod(struct Tastatura t){
    struct nod_LD *nou  =(struct nod_LD*)malloc(sizeof(struct nod_LD));
    nou->info.cod = t.cod;
    nou->info.producator = (char*)malloc(sizeof(char) * (strlen(t.producator) + 1));
    strcpy(nou->info.producator, t.producator);
    nou->info.numarButoane = t.numarButoane;
    nou->info.pret = t.pret;

    nou->prev = NULL;
    nou->next = NULL;

    return nou;
}

void inserare_la_sfarsit(struct nod_LD **prim, struct nod_LD **ultim, struct Tastatura t){
    struct nod_LD *nou = inserare_nod(t);

    if((*prim) == NULL  && (*ultim) == NULL){
        //daca lista mea e vida la inceput
        (*prim) = nou;
        (*ultim) = nou;
    }
    else{
        (*ultim) -> next = nou;
        nou -> prev = (*ultim);
        (*ultim) = nou;
    }
}

void traversare_in_ordine(struct nod_LD *prim){
    struct nod_LD *temp = prim;
    while(temp){
        afisare_Tastatura(temp->info);
        temp = temp->next;
    }
}

void traversare_inversa(struct nod_LD *ultim){
    struct nod_LD *temp = ultim;
    while(temp){
        afisare_Tastatura(temp->info);
        temp = temp -> prev;
    }
}

struct nod_LD *adresa_nod_gasit(struct nod_LD *prim, int COD){
    struct nod_LD *temp = prim;
    struct nod_LD *gasit = NULL;

    while(temp){
        if(temp->info.cod == COD){
            gasit = inserare_nod(temp->info);
            gasit->next = temp->next;
            gasit->prev = temp->prev;
            return gasit;
        }
        else
            temp = temp->next;
    }

    return gasit;
}

struct nod_LD *extragere_nod_cu_cod_dat(struct nod_LD **prim, struct nod_LD **ultim, int COD){
    struct nod_LD *gasit = adresa_nod_gasit(*prim, COD);

    //cazul 1: nodul gasit se afla la inceputul listei
    if(gasit->info.cod == (*prim)->info.cod){
        struct nod_LD *temp = *prim;
        (*prim) = (*prim) -> next;
        (*prim) -> prev = NULL;
        free(temp->info.producator);
        free(temp);

        return gasit;
    }
    else{
        //cazul 2: nodul gasit se afla la sfarsitul listei
        if(gasit->info.cod == (*ultim)->info.cod){
            struct nod_LD *temp = (*ultim);
            (*ultim) = (*ultim) ->prev;
            (*ultim) -> next = NULL;

            free(temp->info.producator);
            free(temp);
            return gasit;
        }
        else{
            //cazul 3: nodul se afla undeva in lista
            struct nod_LD *temp = gasit;
            /*gasit->info = gasit->next->info;


            gasit->info.producator = (char*)malloc(sizeof(char) * (strlen(gasit->next->info.producator) + 1));
            strcpy(gasit->info.producator, gasit->next->info.producator);

            gasit->next = gasit->next->next;
            gasit->next->next->prev = gasit->next;*/

            gasit->prev->next = gasit->next;
            gasit->next->prev = gasit->prev;
            free(temp->info.producator);
            free(temp);
            return gasit;
        }
    }
}



int main() {
    struct nod_LD *cap = NULL;
    struct nod_LD *coada = NULL;

    struct Tastatura t1 = creare_Tastatura(1, "Tast1", 30, 25.00);
    struct Tastatura t2 = creare_Tastatura(2, "Tast2", 20, 100.00);
    struct Tastatura t3 = creare_Tastatura(3, "Tast3", 40, 15.00);

    struct Tastatura vect[] ={t1, t2, t3};
    sortare_Tastaturi_crescator(vect, 3);
    for(int i = 0; i < 3; i++){
        //afisare_Tastatura(vect[i]);
        inserare_la_sfarsit(&cap,&coada ,vect[i]);
    }

    printf("\n\tAfsare in ordine: ");
    traversare_in_ordine(cap);

    printf("\n\tAfisare inversa: ");
    traversare_inversa(coada);

    printf("\n---");
    afisare_Tastatura(adresa_nod_gasit(cap, 1) -> info);
    printf("\n---");

    printf("\n\nEXTRAg  NOD: ");
    extragere_nod_cu_cod_dat(&cap, &coada, 1);
    traversare_in_ordine(cap);



    return 0;
}