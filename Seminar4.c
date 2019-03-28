#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
//STIVA ->LIFO

struct Carte{
    int cod;
    char *titlu;
    float pret;
};

struct Nod_Stiva{
    struct Carte info;
    struct Nod_Stiva *next;
};

void push(struct Nod_Stiva **varf, struct Carte c){
    struct Nod_Stiva *nou = (struct Nod_Stiva *)malloc(sizeof(struct Nod_Stiva));
    nou->info.cod = c.cod;
    nou->info.titlu = (char *)malloc((strlen(c.titlu) + 1 ) *sizeof(char));
    strcpy(nou->info.titlu, c.titlu);
    nou->info.pret = c.pret;

    if(*varf == NULL){
        *varf = nou; //daca stiva e goala
    }
    else{
        nou->next = *varf;
        *varf = nou;
    }
}

int pop(struct Nod_Stiva **varf, struct Carte *val){
    if(*varf == NULL)
        return  -1;
    else
    {
        (*val).cod = (*varf) -> info.cod;
        (*val).titlu = (char *)malloc(((strlen((*varf)->info.titlu) +1) * sizeof(char)));
        strcpy((*val).titlu, (*varf)->info.titlu);
        (*val).pret = (*varf)->info.pret;

        struct Nod_Stiva *aux = *varf;
        *varf = (*varf) -> next;

        free(aux->info.titlu);
        free(aux);

        return 0;
    }
}

void traversare_lista(struct Nod_Stiva *varf){
    struct Nod_Stiva *temp = varf;

    while(temp != NULL){
        printf("\nCod: %d, Titlu: %s, Pret: %5.2f", temp->info.cod, temp->info.titlu, temp->info.pret);
        temp = temp -> next;
    }
}

void conversie_la_vector(struct Nod_Stiva **varf, struct Carte *vect, int *nr){
    struct Carte val;

    //atat timp cat pot sa extrag un nod din stiva
    //atunci inserez val in vector
    while(pop(varf, &val) == 0){
        vect[*nr] = val;
        (*nr) ++;
    }
}

int main() {

    int nr_elemente;
    printf("\nNr de carti: ");
    scanf("%d", &nr_elemente);

    struct Nod_Stiva *varf = NULL;
    struct Carte c;
    char  buf[20];

    for(int i = 0; i < nr_elemente; i++){
        printf("\nCod: "); scanf("%d", &c.cod);
        printf("\nTitlu: ");

        scanf(" %[^\n]s", buf);
        strcpy(c.titlu, buf);

        printf("\nPret: "); scanf("%f", &c.pret);

        push(&varf, c);
    }
    traversare_lista(varf);
    struct Carte c1;
    pop(&varf, &c1);
    printf("\nCartea extrasa are cod: %d", c1.cod);
    //while(pop(&varf, &c) == 0);
    struct Carte *vect = (struct Carte*) malloc(sizeof(struct Carte) * nr_elemente);
    int nr = 0;

    conversie_la_vector(&varf, vect, &nr);

    for(int i = 0; i < nr; i++){
        printf("\nCod: %d, Titlu: %s, Pret: %5.2f", vect[i].cod, vect[i].titlu, vect[i].pret);
    }

    for(int i = 0; i < nr; i++){
        free(vect[i].titlu);
    }
    free(vect);

    return 0;
}