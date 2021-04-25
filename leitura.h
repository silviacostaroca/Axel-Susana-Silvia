
#ifndef SGR_TESTE_LEITURA_H
#define SGR_TESTE_LEITURA_H

#include "catalogo_users.h"
#include "catalogo_bussines.h"
#include "catalogo_reviews.h"

#include "user.h"
#include "bussines.h"
#include "reviews.h"
#include "time.h"

#define MAXFRIENDS 1000
#define MAXBUFFER 50000
#define MAXBUFUSERS 500000 /*Tamanho máximo para ler linhas */
#define MAXBUFBUSSINES 10000 /*Tamanho máximo para ler linhas*/
#define TAM_NAME 100
#define ANOATUAL 2021

/* ---------------- Estruturas ---------------*/
//estrutura definida em time.h
typedef struct tm * DATE;

/* ---------------- Funçẽs -------------------*/
//Validaçẽs dos registos
int isDate(char * token);
int validaUser(char * linha);
int validaBussines (char * linha);
int validaReviews (char * linha);

//Colocação em estruturas
void fillCatalogoUsers (CATALOGO_USER cataU, char * linha);
void fillCatalogoBussines (CATALOGO_BUSSINES catB, char * linha);
void fillCatalogoReviews (CATALOGO_REVIEWS catR, char * linha);

//Leitura dos ficheiros .csv
CATALOGO_USER lerFicheiroUsers(char * nomeFicheiro, CATALOGO_USER cat_users);
CATALOGO_BUSSINES lerFicheiroBussines(char * nomeFicheiro, CATALOGO_BUSSINES cat_bussines);
CATALOGO_REVIEWS lerFicheiroReviews(char * nomeFicheiro, CATALOGO_REVIEWS cat_reviews);



#endif //SGR_TESTE_LEITURA_H
