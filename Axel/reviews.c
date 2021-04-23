//
// Created by Silvia Acosta on 19/04/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "reviews.h"


struct review{
    char *idReview;
    char *idUser;
    char *idBussines;
    float stars;
    int *useful;
    int *funny;
    int *cool;
    char *date;
    char *text;

};


REVIEW initReview (char*idR, char*idB, char*idU, float estrelas, int util, int div, int col,  char*data,  char*texto){

    int tamData= strlen(data)+1;
    REVIEW review = (REVIEW) malloc (sizeof(struct review));
    review->idReview=(char*) malloc(TAM_IDS* sizeof (char ));
    review->idBussines=(char*) malloc(TAM_IDS* sizeof (char ));
    review->idUser=(char*) malloc(TAM_IDS* sizeof (char ));
    review->date = (char*) malloc(tamData*sizeof (char ));
    review->text = (char*) malloc (MAXTEXT*sizeof(char));
    review->idReview = strdup(idR);
    review->idBussines = strdup(idB);
    review->idUser = strdup(idU);
    review->date = strdup(data);
    review->stars = estrelas;
    review->useful = &util;
    review->funny = &div;
    review->cool = &col;
    review->text = strdup(texto);

    return review;

}


/** -------------------- GETS -----------------------**/
char* getReviewIdU(REVIEW r){
    return r->idUser;
}

char* getReviewIdB(REVIEW r){
    return r->idBussines;
}

char* getReviewIdR(REVIEW r){
    return r->idReview;
}
float getReviewStars(REVIEW r){
    return  r->stars;
}
int getReviewUseful(REVIEW r){
    return  r->useful;
}

int getReviewFunny(REVIEW r){
    return  r->funny;
}
int getReviewCool(REVIEW r){
    return  r->cool;
}
char* getReviewData(REVIEW r){
    return  r->date;
}
char* getReviewText(REVIEW r) {
    return r->text;
}


/** --------------- sets ------------------- **/

REVIEW setReviewIdU(REVIEW r, char* id){
    char* idU = strdup(id);
    r->idUser = strdup(idU);
    return r;
}


REVIEW setReviewIdB(REVIEW r, char* id){
    char* idB = strdup(id);
    r->idBussines = strdup(idB);
    return r;
}

REVIEW setReviewIdR(REVIEW r, char* id){
    char* idR = strdup(id);
    r->idReview = strdup(idR);
    return r;
}


REVIEW setReviewsUseful(REVIEW r, int util){
    r->useful = util;
    return r;
}

REVIEW setReviewsFunny(REVIEW r, int div){
    r->funny = div;
    return r;
}

REVIEW setReviewsCool(REVIEW r, int col){
    r->cool = col;
    return r;
}


REVIEW setReviewsStars(REVIEW r, float estrelas){
    r->stars = estrelas;
    return r;
}

REVIEW setReviewsData(REVIEW r, char* data){
    char* d = strdup(data);
    r->date = strdup(d);
    return r;
}

REVIEW setReviewsText(REVIEW r, char* texto){
    char* t = strdup(texto);
    r->text = strdup(t);
    return r;
}


