//
// Created by Silvia Acosta on 17/04/2021.
//

#ifndef AXEL_LEITURA_H
#define AXEL_LEITURA_H

#include "catalogo_users.h"
#include "catalogo_bussines.h"
#include "catalogo_reviews.h"

#define MAXBUFUSERS 500000 /*Tamanho máximo para ler linhas em várias funções*/
#define ANOATUAL 2021

/** ---------------- Estruturas ---------------**/
//estrutura definida em time.h
typedef struct tm * DATE;

/** ---------------- Funçẽs -------------------**/
//Validaçẽs dos registos
int isDate(char * token);
int validaUser(char * linha);
int validaBussines (char * linha);
int validaReviews (char * linha);

//Colocação em estruturas
void fillCatalogo (CATALOGO_USER cataU, char * linha);

//Leitura dos ficheiros .csv
int lerFicheiroUsers(char * nomeFicheiro);
int lerFicheiroBussines(char * nomeFicheiro);
int lerFicheiroReviews(char * nomeFicheiro);

#endif //AXEL_LEITURA_H
