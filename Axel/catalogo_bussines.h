
#ifndef SGR_TESTE_CATALOGO_BUSSINES_H
#define SGR_TESTE_CATALOGO_BUSSINES_H

#include <stdbool.h>
#include "avl.h"
#include "bussines.h"
#include "paginacao.h"

#define TAM_IDS 22
#define MAXCATEGORIAS 1000
#define MAXCAT 2000

/** ---------------- Estruturas ---------------**/
typedef struct catalogoBussines *CATALOGO_BUSSINES;

/* Estruturas Auxiliares */
typedef struct query8 * QUERY8;

//typedef struct media* MEDIA;
//typedef struct cidade* CIDADE;
//typedef struct res* QUERY6;


CATALOGO_BUSSINES initCatBussines();
int calculaIndiceBussines(char l);
void inserirBussinesCatalogo(CATALOGO_BUSSINES cataB, char*idB, char*nameB, char*city, char*state, char**categorias, int nBussines);
int getTotalBussines(CATALOGO_BUSSINES catB);
int existeBussines(CATALOGO_BUSSINES catB, BUSSINES b);
int getAVLIndiceB(CATALOGO_BUSSINES a, char c);
BUSSINES getBussines(CATALOGO_BUSSINES catB, char * idB);
ARVORE getCatalogoBussinesPorLetra(CATALOGO_BUSSINES cat_b, char l);
ARVORE getCatalogoBussinesPorIndice(CATALOGO_BUSSINES cat_b, int i);
/** ------ TRAVESSIAS ------ **/
void freeTravessia(TravessiaModulo trav);
TABLE travessiaBussinesPorLetra (CATALOGO_BUSSINES cat_b, char letra);
//char** travessiaBussinesPorCidade (CATALOGO_BUSSINES cat_b, char* ciudad);
int validaStars(float* stars, float star, int totalStars);
TABLE travessiaBussinesPorCidadeEstrela (CATALOGO_BUSSINES cat_b, char* cidade, float star);
ARVORE getAvlCidades(CATALOGO_BUSSINES catB);
float calculaMedia(float* stars, int totalStars);
float compara (float a, float b);
void bolha (float totalStars, float* stars);
TABLE travessiaTopNegociosPorCidade(CATALOGO_BUSSINES catB, int n);


BUSSINES getBussinesQuery8(QUERY8 res);
float calculaMedia(float* stars, int totalStars);
int insereTopN (int totalInseridos, int n, QUERY8 * topN, QUERY8 new);
TABLE travessiaBussinesPorCategoria(CATALOGO_BUSSINES catB, int n, char* categoria);

#endif //SGR_TESTE_CATALOGO_BUSSINES_H
