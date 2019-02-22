#include <stdio.h>
#include <malloc.h>
#include <mem.h> //biblioteca pt strlen, strcpy

//magazin cu n produse
//

struct Produs{
    int cod;
    char *denumire;
    float pret;
    float cantitate;
};

void citire_vector(struct Produs *p, int nr_p){
    char buf[20];

    for(int i = 0 ; i < nr_p; i++){
        printf("\nCod: "); scanf("%d", &p[i].cod);

        printf("\nDenumire: "); scanf("%s", buf);
        p[i].denumire = (char*)malloc((strlen(buf) + 1) *sizeof(char));
        strcpy(p[i].denumire, buf);

        printf("\nPretul: "); scanf("%f", &p[i].pret);
        printf("\nCantitate: "); scanf("%f", &p[i].cantitate);


    }
}

void afisare_vector(struct Produs *p, int nr_p){
    for(int i = 0; i < nr_p; i++){
        printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f|",
               p[i].cod, p[i].denumire, p[i].pret, p[i].cantitate);

    }
}

void dezalocare_vector(struct Produs *p, int nr_p){

    for(int i = 0;i < nr_p; i++){
        free(p[i].denumire);
    }
    free(p);
}

void citire_4vectori(int *cod, char **den, float *pret, float *cant, int n){
    char buf[20];

    for(int i = 0 ; i < n; i++){
        printf("\nCod: "); scanf("%d", &cod[i]);

        printf("\nDenumire: "); scanf("%s", buf);
        den[i] = (char*)malloc((strlen(buf) + 1) *sizeof(char));
        strcpy(den[i], buf);

        printf("\nPretul: "); scanf("%f", &pret[i]);
        printf("\nCantitate: "); scanf("%f", &cant[i]);
}}

void afisare_4vectori(int *cod, char **den, float *pret, float *cant, int n){
    for(int i = 0; i < n; i++){
        printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f|",
               cod[i], den[i], pret[i], cant[i]);

    }
}

void dezalocare_4vectori(int *cod, char **den, float *pret, float *cant, int n){
    free(cod);
    for(int i = 0; i < n; i++)
        free(den[i]);
    free(den);
    free(pret);
    free(cant);
}

int main() {

    int nr_produse;
    printf("Nr de produse: ");
    scanf("%d", &nr_produse);

    struct Produs *vp = (struct Produs *)malloc(nr_produse * sizeof(struct Produs));

    citire_vector(vp, nr_produse);
    afisare_vector(vp, nr_produse);
    dezalocare_vector(vp, nr_produse);

    int *coduri = (int *)malloc(nr_produse * sizeof(int));
    char **denumire = (char **)malloc(nr_produse * sizeof(char*));
    float *preturi =(float *)malloc(nr_produse * sizeof(float));
    float *cantitati = (float *)malloc(nr_produse * sizeof(float));

    citire_4vectori(coduri, denumire, preturi, cantitati, nr_produse);
    afisare_4vectori(coduri, denumire, preturi, cantitati, nr_produse);
    dezalocare_4vectori(coduri, denumire, preturi, cantitati, nr_produse);

    float **mat = (float**)malloc(nr_produse * sizeof(float*));
    for(int i = 0; i < nr_produse; i++)
        mat[i] = (float *)malloc(3 * sizeof(float));



    return 0;
}