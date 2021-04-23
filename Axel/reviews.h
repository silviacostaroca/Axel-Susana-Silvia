//
// Created by Silvia Acosta on 19/04/2021.
//

#ifndef AXEL_REVIEWS_H
#define AXEL_REVIEWS_H

#define MAXTEXT 5000000
#define TAM_IDS 22
typedef struct review * REVIEW;



REVIEW initReview (char*idR, char*idB, char*idU, float estrelas, int util, int div, int col,  char*data,  char*texto);

char* getReviewIdU(REVIEW r);
char* getReviewIdB(REVIEW r);
char* getReviewIdR(REVIEW r);
float getReviewStars(REVIEW r);
int getReviewUseful(REVIEW r);
int getReviewFunny(REVIEW r);
int getReviewCool(REVIEW r);
char* getReviewData(REVIEW r);
char* getReviewText(REVIEW r);


REVIEW setReviewIdU(REVIEW r, char* id);
REVIEW setReviewIdB(REVIEW r, char* id);
REVIEW setReviewIdR(REVIEW r, char* id);
REVIEW setReviewsUseful(REVIEW r, int util);
REVIEW setReviewsFunny(REVIEW r, int div);
REVIEW setReviewsCool(REVIEW r, int col);
REVIEW setReviewsStars(REVIEW r, float estrelas);
REVIEW setReviewsData(REVIEW r, char* data);
REVIEW setReviewsText(REVIEW r, char* texto);



#endif //AXEL_REVIEWS_H
