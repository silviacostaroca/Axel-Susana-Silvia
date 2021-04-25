#ifndef GRUPO66_BUSSINES_H
#define GRUPO66_BUSSINES_H

#define MAXCAT 1000
#define TAM_IDS 22
#define TAM_CATEG 50

/** ---------------- Estruturas ---------------**/
typedef struct bussines * BUSSINES;

/** ---------------- Funçoẽs -------------------**/

BUSSINES initBussines(char* id, char* name, char* city, char* state, char** categories, int numCategorias);

/** -------------------- GETS -----------------------**/
char* getBussinesId(BUSSINES b);
char* getBussinesName(BUSSINES b);
char* getBussinesCity(BUSSINES b);
char* getBussinesState(BUSSINES b);
int getBussinesTotalCat(BUSSINES b);
char** getBussinesCategorias(BUSSINES b);

/** --------------- sets ------------------- **/
BUSSINES setBussinesId(BUSSINES b, char* id);
BUSSINES setBussinesName(BUSSINES b, char* nome);
BUSSINES setBussinesCity(BUSSINES b, char* city);
BUSSINES setBussinesState(BUSSINES b, char* state);
BUSSINES setBussinesTotalCategorias(BUSSINES b, int numCat);
BUSSINES setBussinesCategorias(BUSSINES b, char** categories, int totalCat);

#endif //GRUPO66_BUSSINES_H
