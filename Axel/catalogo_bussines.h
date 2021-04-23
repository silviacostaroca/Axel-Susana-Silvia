
#ifndef GRUPO66_CATALOGO_BUSSINES_H
#define GRUPO66_CATALOGO_BUSSINES_H

#include <stdbool.h>
#include "avl.h"
#include "bussines.h"
#include "paginacao.h"

#define TAM_IDS 22
#define MAXCATEGORIAS 1000

/** ---------------- Estruturas ---------------**/
typedef struct catalogoBussines *CATALOGO_BUSSINES;

CATALOGO_BUSSINES initCatBussines();
int calculaIndiceBussines(char l);
void inserirBussinesCatalogo(CATALOGO_BUSSINES cataB, char*idB, char*nameB, char*city, char*state, char**categorias, int nBussines);
int getTotalBussines(CATALOGO_BUSSINES catB);
int existeBussines(CATALOGO_BUSSINES catB, BUSSINES b);
BUSSINES getBussines(CATALOGO_BUSSINES catB, char * idB);
ARVORE getCatalogoBussinesPorLetra(CATALOGO_BUSSINES cat_b, char l);
ARVORE getCatalogoBussinesPorIndice(CATALOGO_BUSSINES cat_b, int i);
/** ------ TRAVESSIAS ------ **/
void freeTravessia(TravessiaModulo trav);
TABLE travessiaBussinesPorLetra (CATALOGO_BUSSINES cat_b, char letra);
//void quicksort(void** resultados, int (*funcaoComparacao)(), int n, void* param);



#endif //GRUPO66_CATALOGO_BUSSINES_H


