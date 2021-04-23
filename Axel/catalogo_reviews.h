//
// Created by Silvia Acosta on 17/04/2021.
//

#ifndef GRUPO66_CATALOGO_REVIEWS_H
#define GRUPO66_CATALOGO_REVIEWS_H



#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include <ctype.h>
#include <stdbool.h>
#include "avl.h"
#include "reviews.h"

#define TAM_IDS 22
#define MAXTEXT 5000000

typedef struct catalogoReviews *CATALOGO_REVIEWS;

CATALOGO_REVIEWS initCatReviews();
void inserirReviewCatalogo(CATALOGO_REVIEWS cataR, char*idR, char*idU, char*idB, float estrelas, int util, int div, int col,  char*data,  char*texto);
char* getReviewIdU(REVIEW r);
char* getReviewIdB(REVIEW r);
char* getReviewIdR(REVIEW r);
float getReviewStars(REVIEW r);
int getReviewUseful(REVIEW r);
int getReviewFunny(REVIEW r);
int getReviewCool(REVIEW r);
char* getReviewData(REVIEW r);
char* getReviewText(REVIEW r);
REVIEW getReview (CATALOGO_REVIEWS catR, char * idR);

REVIEW setReviewIdU(REVIEW r, char* id);
REVIEW setReviewIdB(REVIEW r, char* id);
REVIEW setReviewIdR(REVIEW r, char* id);
REVIEW setReviewsUseful(REVIEW r, int util);
REVIEW setReviewsFunny(REVIEW r, int div);
REVIEW setReviewsCool(REVIEW r, int col);
REVIEW setReviewsStars(REVIEW r, float estrelas);
REVIEW setReviewsData(REVIEW r, char* data);
REVIEW setReviewsText(REVIEW r, char* texto);


#endif //GRUPO66_CATALOGO_REVIEWS_H