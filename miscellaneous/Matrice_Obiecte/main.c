#include <stdio.h>
#include <malloc.h>
#include <string.h>


struct Bilet{
    int cod;
    float pret;
    char *destinatie;
};

void initializareBilet(struct Bilet *b, int c, float p, char *d){
    (*b).cod = c;
    (*b).pret = p;
    (*b).destinatie = (char*)malloc(sizeof(char) * (strlen(d) + 1));
    strcpy((*b).destinatie, d);
}

struct Bilet citire_bilet(){
    struct Bilet b;
    char buf[20];
    printf("\nCod: "); scanf("%d", &b.cod);
    printf("\nPret: "); scanf("%f", &b.pret);
    printf("\nDestinatie: "); scanf("%s", buf);
    b.destinatie = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
    strcpy(b.destinatie, buf);

    return b;
}

void afisareBilet(struct Bilet b){
    printf("\nCod: %d, Pret: %5.2f, Destinatie: %s", b.cod, b.pret, b.destinatie);
}

struct Bilet **citire_mat(int *nr_linii, int **col){
    printf("\nNr de linii: ");
        scanf("%d", nr_linii);

    int i, j;
    struct Bilet **b;
    b = (struct Bilet**)malloc((*nr_linii) * sizeof(struct Bilet*));
    *col = (int *)malloc((*nr_linii) * sizeof(int));

    for(i = 0; i < (*nr_linii); i++){
        printf("\nLungimea liniei %d: ", i + 1);
        scanf("%d", &(*col)[i]);
        b[i] = (struct Bilet*)malloc((*col)[i] * sizeof(struct Bilet));
        for(j = 0; j < (*col)[i]; j++){
            printf("\nIntroduceti biletul[%d][%d]", i + 1, j + 1);
                b[i][j] = citire_bilet();

        }
    }
    return b;
}
void afisare_matrice(struct Bilet **b, int nr_linii, int *coloane){
    int i, j;
    for(i = 0; i < nr_linii; i++){
        printf("\nBiletele de pe linia: %d", i);
        for(j = 0; j < coloane[i]; j++)
            afisareBilet(b[i][j]);
        printf("\n");
    }
}

void afisare_vector(struct Bilet *v, int dim){
    int i;
    for(i = 0; i < dim; i++)
        afisareBilet(v[i]);
}

int main() {
    int i, j;
    struct Bilet b1;
    initializareBilet(&b1, 10, 31.25, "Bucuresti");
    afisareBilet(b1);

    struct Bilet **matrice;
    int *coloane = NULL;
    int nr_linii = 0;

    matrice = citire_mat(&nr_linii, &coloane);
    afisare_matrice(matrice, nr_linii, coloane);

    printf("\nAfisare vector: ");
    afisare_vector(matrice[0], coloane[0]);



    for(i = 0; i < nr_linii; i++){
        for(j = 0; j < coloane[i]; j++)
            free(matrice[i][j].destinatie);
        free(matrice[i]);
    }
    free(matrice);
    free(coloane);
    free(b1.destinatie);

    return 0;
}