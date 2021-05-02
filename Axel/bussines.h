
#ifndef SGR_TESTE_BUSSINES_H
#define SGR_TESTE_BUSSINES_H

#include "avl.h"

#define MAXCAT 1000
#define TAM_IDS 22
#define TAM_CATEG 50

/** ---------------- Estruturas ---------------**/
typedef struct bussines * BUSSINES;

/** ---------------- Funçoẽs -------------------**/

BUSSINES initBussines(char* id, char* name, char* city, char* state, char** categories, int numCategorias);
/** -------------------- GETS -----------------------**/
int avlComparaCateg(const void *avlA, const void *avlB, void *avlParam);
char* getBussinesId(BUSSINES b);
char* getBussinesName(BUSSINES b);
char* getBussinesCity(BUSSINES b);
char* getBussinesState(BUSSINES b);
int getBussinesTotalCat(BUSSINES b);
ARVORE getBussinesCategorias(BUSSINES b);
float* getBussinesStars (BUSSINES b);
int getBussinesTotalstars (BUSSINES b);
BUSSINES setBussinesStarsArray(BUSSINES b, float* stars , int totalStars);
/** --------------- sets ------------------- **/
BUSSINES setBussinesId(BUSSINES b, char* id);
BUSSINES setBussinesName(BUSSINES b, char* nome);
BUSSINES setBussinesCity(BUSSINES b, char* city);
BUSSINES setBussinesState(BUSSINES b, char* state);
BUSSINES setBussinesTotalCategorias(BUSSINES b, int numCat);
BUSSINES setBussinesCategorias(BUSSINES b, ARVORE categoria);
BUSSINES setBussinesTotalStars(BUSSINES b, int numStars);
BUSSINES setBussinesStars (BUSSINES b, float star, int numStars);

#endif //SGR_TESTE_BUSSINES_H
