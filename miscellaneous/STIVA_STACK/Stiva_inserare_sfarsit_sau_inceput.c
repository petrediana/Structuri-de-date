#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct Carte{
    char *denumire;
    int cod;
    float pret;
};

struct nod_Stiva{
    struct Carte info;
    struct nod_Stiva *next;
};


struct Carte creare_Carte(char *den, int co, float f){
    struct Carte c;
    c.denumire = (char*)malloc(sizeof(char) * (strlen(den) + 1));
    strcpy(c.denumire, den);
    c.cod = co;
    c.pret = f;

    return c;
}

void afisare_Carte(struct Carte c){
    printf("\n\nDenumire: %s, Cod: %d, Pret: %5.2f", c.denumire,c.cod, c.pret);
}


//!!!
struct nod_Stiva *inserare_nod(struct Carte c, struct nod_Stiva *next){
    struct nod_Stiva *nou = (struct nod_Stiva*)malloc(sizeof(struct nod_Stiva));
    nou->info.denumire =(char*)malloc(sizeof(char) * (strlen(c.denumire) + 1));
    strcpy(nou->info.denumire, c.denumire);
    nou->info.cod = c.cod;
    nou->info.pret = c.pret;

    nou->next = next;

    return nou;
}

//inserare la sfarsit
void push_sfarsit(struct Carte c, struct nod_Stiva **cap){
    struct nod_Stiva *nou = inserare_nod(c, NULL);

    if((*cap)){//lista nu este goala
        struct nod_Stiva *temp = (*cap);
        while(temp->next){
            temp = temp -> next;
        }
        temp -> next = nou;
    }
    else{ //stiva este goala
        (*cap) = nou;
    }
}
int pop_sfarsit(struct Carte *val_extrasa, struct nod_Stiva **cap){
    if((*cap) == NULL){
        return -1;
        //stiva mea e goala
    }
    else{
        struct nod_Stiva *aux = (*cap);
        struct nod_Stiva *pen = (*cap);

        while(pen->next->next){
            pen = pen->next;
        }//trebuie sa retin adresa penultimului nod

        while(aux->next) {
            aux = aux->next;
        }

        (*val_extrasa).cod = aux->info.cod;
        (*val_extrasa).pret = aux->info.pret;
        (*val_extrasa).denumire = (char*)malloc(sizeof(char) * (strlen(aux->info.denumire) + 1));
        strcpy((*val_extrasa).denumire, aux->info.denumire);

        afisare_Carte((*val_extrasa));

        free(aux->info.denumire);
        pen->next = NULL;
        free(aux);


        return 0;
    }
}

void push_inceput(struct nod_Stiva **cap, struct Carte c){
    (*cap) = inserare_nod(c, *cap);
}

int pop_inceput(struct Carte *val_extrasa, struct nod_Stiva **cap){
    if(cap == NULL){
        return -1;
        //stiva este goala
    }
    else{
        //doar extrag primul element
        (*val_extrasa).denumire = (char*)malloc(sizeof(char) * (strlen((*cap)->info.denumire) + 1));
        strcpy((*val_extrasa).denumire, (*cap)->info.denumire);
        (*val_extrasa).cod = (*cap)->info.cod;
        (*val_extrasa).pret = (*cap)->info.pret;

        afisare_Carte((*val_extrasa));

        struct nod_Stiva *aux = *cap;
        (*cap) = (*cap) -> next;

        free(aux->info.denumire);
        free(aux);

        return 0;
    }
}


void traversare(struct nod_Stiva *cap){
    printf("\n\tTraversare: ");
    while(cap){
        printf("\nDenumire: %s, Cod: %d, Pret: %5.2f", cap->info.denumire, cap->info.cod, cap->info.pret);
        cap = cap->next;
    }
}

void dezalocare(struct nod_Stiva **nod){
    while((*nod)){
        free((*nod)->info.denumire);
        free(*nod);
        (*nod) = (*nod) -> next;
    }
}

int main() {
    struct Carte c1 = creare_Carte("Carte1", 1, 25.5);
    struct Carte c2 = creare_Carte("Carte2", 2, 50.02);
    struct Carte c3 = creare_Carte("Carte3", 3, 10.05);
    struct Carte c4 = creare_Carte("Carte4", 4, 100.02);

    printf("\n-------INSERARE LA SFARSIT----------");
    //--------------------------------------------
    //INSERARE LA SFARSITUL LISTEI
    //CAUT SI ELIMIN ULTIMUL ELEMENT INSERAT
    struct nod_Stiva *stack = NULL;
    push_sfarsit(c1, &stack);
    push_sfarsit(c2, &stack);
    push_sfarsit(c3, &stack);
    push_sfarsit(c4, &stack);

    traversare(stack);

    struct Carte c_extrasa;
    pop_sfarsit(&c_extrasa, &stack);
    printf("   <-- Elementul extras\n");

    traversare(stack);

    //--------------------------------------------

    printf("\n\n-------INSERARE LA INCEPUT----------");
    //--------------------------------------------
    //INSERARE LA INCEPUTUL LISTEI
    //CAUT SI ELIMIN PRIMUL ELEMENT INSERAT

    struct nod_Stiva *stiva = NULL;
    struct Carte c_extras2;

    push_inceput(&stiva, c1);
    push_inceput(&stiva, c2);
    push_inceput(&stiva, c3);
    push_inceput(&stiva, c4);

    traversare(stiva);

    pop_inceput(&c_extras2, &stiva);
    printf("   <-- Elementul extras\n");

    traversare(stiva);

    dezalocare(&stiva);
    dezalocare(&stack);
    return 0;
}