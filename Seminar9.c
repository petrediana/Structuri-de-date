#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

//arbore binar -> fiecare nod nu are mai mult de 2 fii
// arbore echilibrat -> nu difera nivelul subarborelui stanga fata de cel dreapta cu mai mult de 1
// preordine = radacina, stanga, dreapta
// inordine = stanga, radacina, dreapta
// postordine = stanga, dreapta, radacina

struct Student{
    int cod;
    char *nume;
    float medie;
};

struct Nod_Arbore{
    struct Student info;
    struct Nod_Arbore *left;
    struct Nod_Arbore *right;
};

struct Nod_Arbore *creare_nod(struct Student s, struct Nod_Arbore *st, struct Nod_Arbore *dr){
    struct Nod_Arbore *nou = (struct Nod_Arbore*)malloc(sizeof(struct Nod_Arbore));
    nou->info.cod = s.cod;
    nou->info.nume = (char*)malloc(sizeof(char) * (strlen(s.nume) + 1));
    strcpy(nou->info.nume, s.nume);
    nou->info.medie = s.medie;

    nou->right = dr;
    nou->left = st;

    return nou;
}

//verific locul in care inserez
struct Nod_Arbore *inserare(struct Student s, struct Nod_Arbore *radacina){
    struct Nod_Arbore *aux = radacina;

    if(radacina == NULL){
        aux = creare_nod(s, NULL, NULL);
        return aux;
    }
    else {
        while(true){
            if(s.cod < aux->info.cod)
                if(aux->left != NULL) //ramura stanga
                    aux = aux -> left;
            else
                {
                    aux->left = creare_nod(s, NULL, NULL);
                    return radacina;
                }
            else //sunt pe ramura dreapta
            if(s.cod > aux->info.cod)
                if(aux->right != NULL)
                    aux = aux -> right;
            else{
                    aux -> right = creare_nod(s, NULL, NULL);
                    return radacina;
                }
            else{
                //alfel nu inserez deloc, cheie duplicata
                return radacina;
            }
        }
    }
}

//traversare preordine
void preordine( struct Nod_Arbore *radacina){
    if(radacina != NULL){
        printf("\nCod: %d, Nume: %s, Medie: %5.2f", radacina->info.cod, radacina->info.nume, radacina->info.medie);
        preordine(radacina->left);
        preordine(radacina->right);
    }
}

//traversare inordine
void inordine( struct Nod_Arbore *radacina){
    if(radacina != NULL){
        inordine(radacina->left);
        printf("\nCod: %d, Nume: %s, Medie: %5.2f", radacina->info.cod, radacina->info.nume, radacina->info.medie);
        inordine(radacina->right);
    }
}

//traversare postordine
void postordine( struct Nod_Arbore *radacina){
    if(radacina != NULL){
        postordine(radacina->left);
        postordine(radacina->right);
        printf("\nCod: %d, Nume: %s, Medie: %5.2f", radacina->info.cod, radacina->info.nume, radacina->info.medie);
    }
}
void dezalocare(struct Nod_Arbore *radacina){
    if(radacina != NULL){
        struct Nod_Arbore *stanga = radacina->left;
        struct Nod_Arbore *dreapta = radacina -> right;
        free(radacina->info.nume);
        free(radacina);
        dezalocare(stanga);
        dezalocare(dreapta);
    }
}

int maxim(int a, int b){
    return a < b ? b : a;
}

int nrNiveluri(struct Nod_Arbore *radacina){
    if(radacina){
        return 1 + maxim(nrNiveluri(radacina->left), nrNiveluri(radacina->right));
    }
    else
        return 0;
}

struct Nod_Arbore *cautare(struct Nod_Arbore *radacina, int cheie){
    if(radacina != NULL){
        if(radacina->info.cod == cheie)
            return radacina;
        else
            if(cheie < radacina->info.cod)
                return cautare(radacina->left, cheie);
        else
                return cautare(radacina->right, cheie);
    }
    else
        return NULL;
}
void conversie_ARbore_vector(struct Nod_Arbore *radacina, struct Student *vect, int *nr){
    if(radacina){
        vect[(*nr)] = radacina->info;
        (*nr) ++;
        conversie_ARbore_vector(radacina->left, vect, nr);
        conversie_ARbore_vector(radacina->right, vect, nr);
    }
}


int main() {

    int n; //nr noduri;
    printf("\nNumar noduri: "); scanf("%d", &n);

    struct Nod_Arbore *radacina = NULL;
    struct Student s;
    char buf[20];

    for(int i = 0; i < n; i++){
        printf("\nCod: ");
        scanf("%d", &s.cod);

        printf("Nume: ");
        scanf("%s", buf);
        s.nume = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
        strcpy(s.nume, buf);

        printf("Medie: ");
        scanf("%f", &s.medie);

        radacina = inserare(s, radacina);
    }

    inordine(radacina);
    printf("\nInaltime arbore este: %d", nrNiveluri(radacina));

    struct Nod_Arbore *nod_cautat = cautare(radacina, 13);
    printf("\nNumele cautat: %s", nod_cautat->info.nume);

    printf("\n-------------");
    struct Student *vect = (struct Student*)malloc(sizeof(struct Student) * n);
    int nr = 0;
    conversie_ARbore_vector(radacina, vect, &nr);
    for(int i = 0; i < nr; i++)
        printf("\nCod: %d, Nume: %s, Medie: %5.2f", vect[i].cod, vect[i].nume, vect[i].medie);

    free(vect);
    dezalocare(radacina);
    return 0;
}