#include <stdio.h>
#include <string.h>
#include <malloc.h>
//lista simpla de liste simple

struct Student {
    int varsta;
    char *nume;
    float medie;
};

struct nodls{
    struct Student inf;
    struct nodls *next;
};

struct nodlp{ //lista principala
    struct nodls *info;
    struct nodlp *next;
};

void inserareLS(struct nodls **cap, struct Student s){
    //lista secundara
    struct nodls *nou = (struct nodls *)malloc(sizeof(struct nodls));

    nou ->inf.varsta = s.varsta;
    nou ->inf.nume = (char *)malloc((strlen(s.nume) + 1) * sizeof(char));

    strcpy(nou->inf.nume, s.nume);
    nou->inf.medie = s.medie;
    nou -> next = NULL;

    if(*cap == NULL)
        *cap = nou; //daca lisa e vida
    else{//altfel pun la sfarsit

        struct nodls * temp = *cap;
        while(temp->next)
            temp = temp -> next;

        temp->next = nou;
    }
}

void inserareLP(struct nodlp **cap, struct nodls *capLS){
    struct nodlp *nou = (struct nodlp *)malloc(sizeof(struct nodlp));
    nou -> info = capLS;
    nou -> next = NULL;

    if(*cap == NULL)
        *cap = nou; //daca lisa e vida
    else{//altfel pun la sfarsit

        struct nodlp * temp = *cap;
        while(temp->next)
            temp = temp -> next;

        temp->next = nou;
    }

}

void traversareLS(struct nodls *prim){
    struct nodls *temp = prim;

    while(temp){
        printf("\nVarsta: %d, Nume: %s, Medie %5.2f ", temp->inf.varsta, temp ->inf.nume, temp -> inf.medie);
        temp = temp -> next;
    }
}

void traversareLP(struct nodlp *cap){
    struct nodlp *temp = cap;
    while(temp)
    {
        printf("\nSublista: \n");
        traversareLS(temp->info);
        temp = temp -> next;
    }
}

void dezalocareLS(struct nodls *cap){
    struct nodls *temp = cap;
    while(temp){
        struct nodls *temp2 = temp -> next;
        free(temp->inf.nume);
                free(temp);
        temp = temp2;
    }
}

void dezalocareLP(struct nodlp *cap){
    struct nodlp *temp = cap;
    while(temp){
        struct nodlp *temp2 = temp->next;
        dezalocareLS(temp->info);
        temp = temp2;

    }
}

int main() {

    int n;
    printf("\nNr studenti: "); scanf("%d", &n);

    //capul listei principale
    struct nodlp *capLP = NULL;
    struct nodls *capLSpar = NULL;
    struct nodls *capLSimpar = NULL;
    struct Student s;
    char buf[20];

    for(int i = 0; i < n; i++){
        printf("\nVarsta = "); scanf("%d", &s.varsta);
        printf("Nume: "); scanf(" %[^\n]s", buf);
        s.nume = (char*)malloc((strlen(buf) + 1 ) * sizeof(char));
        strcpy(s.nume, buf);
        printf("Medie: "); scanf("%f", &s.medie);

        if(s.varsta % 2 == 0)
            inserareLS(&capLSpar, s);
        else
            inserareLS(&capLSimpar, s);

    }
    inserareLP(&capLP, capLSpar);
    inserareLP(&capLP, capLSimpar);
    traversareLP(capLP);

    dezalocareLP(capLP);


    return 0;
}