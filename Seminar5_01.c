#include <stdio.h>
#include <string.h>
#include <malloc.h>
//coada fifo

struct Student{
    int varsta;
    char *nume;
    float medie;
};

struct nodCoada{
    struct Student inf;
    struct nodCoada *next;
};

void put(struct nodCoada **prim, struct nodCoada **ultim, struct Student s){
    struct nodCoada *nou = (struct nodCoada *)malloc(sizeof(struct nodCoada));

    nou ->inf.varsta = s.varsta;
    nou ->inf.nume = (char *)malloc((strlen(s.nume) + 1) * sizeof(char));

    strcpy(nou->inf.nume, s.nume);
    nou->inf.medie = s.medie;

    nou -> next = NULL;

    if(*prim == NULL && *ultim == NULL){ //daca la inceput e vida
        *prim = nou;
        *ultim = nou;
    }
    else{
        (*ultim) -> next = nou;
        (*ultim) = nou;
    }
}

int get(struct nodCoada **prim, struct nodCoada **ultim, struct Student *s){
    if(*prim != NULL && *ultim != NULL){
        //extrag
        (*s).varsta = (*prim)->inf.varsta;
        (*s).nume = (char*)malloc((strlen((*prim)->inf.nume) + 1 ) * sizeof(char));
        strcpy((*s).nume, (*prim)->inf.nume);

        (*s).medie =(*prim)->inf.medie;

        struct nodCoada *aux = *prim; //pastrez adresa nodului curent

        *prim = (*prim) -> next;

        free(aux->inf.nume);
        free(aux);
        //il deplasez pe prim pana cand prim devine null
        //adica nu mai am ce sa scot din coada
        //cand prim devine null, ultimul nu se modifica
        //si pastreaza adresa ultimului nod care a fost sters
        //de asta il sterg in if
        return 0; // adica am extras
    }
    else
    {
        if((*prim) == NULL){
            *ultim = NULL;
            return -1;
        }
    }
}

void traversare(struct nodCoada *prim){
    struct nodCoada *temp = prim;

    while(temp){
        printf("\nVarsta: %d, Nume: %s, Medie %5.2f ", temp->inf.varsta, temp ->inf.nume, temp -> inf.medie);
        temp = temp -> next;
    }
}


void conversieCoadaVector(struct nodCoada **prim, struct nodCoada **ultim, struct Student *vect, int *nr){
    struct Student s;

    while (get(prim, ultim, &s) == 0){
        vect[(*nr)] = s;
        (*nr) ++;
    }
}

int main() {
    int n;
    printf("\nNr studenti: "); scanf("%d", &n);

    struct nodCoada *prim = NULL;
    struct nodCoada *ultim = NULL;
    struct Student s;
    char buf[20];

    for(int i = 0; i < n; i++){
        printf("\nVarsta = "); scanf("%d", &s.varsta);
        printf("Nume: "); scanf(" %[^\n]s", buf);
        s.nume = (char*)malloc((strlen(buf) + 1 ) * sizeof(char));
        strcpy(s.nume, buf);

        printf("Medie: "); scanf("%f", &s.medie);

        put(&prim, &ultim, s);
    }
    traversare(prim);

    printf("\n---------------------------------");

    struct Student *vect = (struct Student *)malloc(n * sizeof(struct Student));
    int nr = 0;

    conversieCoadaVector(&prim, &ultim, vect, &nr);
    for(int i = 0; i < nr; i++){
        printf("\nVarsta: %d, Nume: %s, Medie %5.2f ", vect[i].varsta, vect[i].nume, vect[i].medie);
    }

    for(int i = 0; i < nr; i++)
        free(vect[i].nume);
    free(vect);

    return 0;
}