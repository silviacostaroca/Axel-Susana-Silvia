//
// Created by Silvia Acosta on 31/03/2021.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "avl.h"
#include "catalogo_reviews.h"

struct review{
    char *idReview;
    char *idUser;
    char *idBussines;
    float *stars;
    int *useful;
    int *funny;
    int *cool;
    char *date;
    char *text [MAXTEXT];
};
struct catalogoReviews{
    int totalReviews ;
   TABLE avl_indiceR [36]; //27 letras + 9 algarismos, porque os ids podem começar por letra ou numero
};

