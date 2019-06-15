#include "pch.h"
#include <stdio.h>
#include <malloc.h>

struct nod_lista_dubla {
	int inf;
	nod_lista_dubla *next;
	nod_lista_dubla *prev;
};

nod_lista_dubla *creare_nod_ld(int inf, nod_lista_dubla *next, nod_lista_dubla *prev) {
	nod_lista_dubla *nou = (nod_lista_dubla*)malloc(sizeof(nod_lista_dubla));

	nou->inf = inf;
	nou->next = next;
	nou->prev = prev;

	return nou;
}

void inserare_lista_dubla(nod_lista_dubla **prim, nod_lista_dubla **ultim, int inf) {
	nod_lista_dubla *nou = creare_nod_ld(inf, NULL, NULL);

	if ((*prim) == NULL && (*ultim) == NULL) {
		(*prim) = nou;
		(*ultim) = (*prim);
	}
	else {
		(*ultim)->next = nou;
		nou->prev = (*ultim);
		(*ultim) = nou;
	}
}

void traversare_LD_normal(nod_lista_dubla *prim) {
	nod_lista_dubla *temp = prim;
	printf("\n\nTraversare normal: ");
	
	while (temp) {
		printf("\nInformatia: %d", temp->inf);
		temp = temp->next;
	}
}

void traversare_LD_invers(nod_lista_dubla *ultim) {
	nod_lista_dubla *temp = ultim;
	printf("\n\nTraversare inversa: ");

	while (temp) {
		printf("\nInformatia: %d", temp->inf);
		temp = temp->prev;
	}
}

void dezalocare_LD(nod_lista_dubla **prim, nod_lista_dubla **ultim) {
	nod_lista_dubla *temp = (*prim);

	while (temp) {
		nod_lista_dubla *temp2 = temp;
		temp = temp->next;

		free(temp2);
	}

	(*prim) = NULL;
	(*ultim) = NULL;
}


void sterge_un_element_LD(nod_lista_dubla **prim, nod_lista_dubla **ultim, int element, int *salveaza) {
	if ((*prim) != NULL && (*ultim) != NULL) {

		//caz 1: sterg primul element din lista
		if ((*prim)->inf == element) {
			(*salveaza) = (*prim)->inf;

			nod_lista_dubla *aux = (*prim);
			(*prim) = (*prim)->next;

			free(aux);
			return;
		}

		//cazul 2: sterg ultimul element din lista
		if ((*ultim)->inf == element) {
			(*salveaza) = (*ultim)->inf;

			nod_lista_dubla *aux = (*ultim);
			(*ultim)->prev->next = NULL;
			
			free(aux);
			return;
		}

		//cazul 3: sterg un element de la mijloc -> nu primul, nu ultimul!!
		nod_lista_dubla *aux = (*prim);
		while (aux) {
			if (aux->inf == element) {
				(*salveaza) = aux->inf;

				nod_lista_dubla *sterge = aux;
				aux->prev->next = aux->next;
				aux->next->prev = aux->prev;

				free(sterge);
				return;
			}
			aux = aux->next;
		}

	}
	else {
		printf("\nLista vida!!");
	}
}

void main() {
	nod_lista_dubla *prim = NULL;
	nod_lista_dubla *ultim = NULL;

	inserare_lista_dubla(&prim, &ultim, 1);
	inserare_lista_dubla(&prim, &ultim, 2);
	inserare_lista_dubla(&prim, &ultim, 3);
	inserare_lista_dubla(&prim, &ultim, 4);
	inserare_lista_dubla(&prim, &ultim, 5);

	traversare_LD_normal(prim);
	traversare_LD_invers(ultim);

	printf("\nSterg primul element");
	int salveaza;
	sterge_un_element_LD(&prim, &ultim, 1, &salveaza);
	traversare_LD_normal(prim);


	printf("\nSterg ultimul element");
	sterge_un_element_LD(&prim, &ultim, 5, &salveaza);
	traversare_LD_normal(prim);

	printf("\nSterg un element de la mijloc");
	sterge_un_element_LD(&prim, &ultim, 3, &salveaza);
	traversare_LD_normal(prim);



	dezalocare_LD(&prim, &ultim);
}

