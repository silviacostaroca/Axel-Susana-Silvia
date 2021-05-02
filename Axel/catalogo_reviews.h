#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include <ctype.h>
#include <stdbool.h>
#include "avl.h"
#include "reviews.h"
#include "catalogo_bussines.h"

#define TAM_IDS 22
#define MAXTEXT 5000000

typedef struct catalogoReviews *CATALOGO_REVIEWS;
typedef struct states* QUERY7;

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


float* travessiaReviewsPorIdB (CATALOGO_REVIEWS cat_r, char* idBuss);
char** travessiaReviewsPorIdU (CATALOGO_REVIEWS cat_r, char*idUser);
char** travessiaReviewsPorStars (CATALOGO_REVIEWS cat_r, float stars);
char** travessiaReviewsPorPalabra (CATALOGO_REVIEWS cat_r, char* palabra);

CATALOGO_BUSSINES estruturaConStars (CATALOGO_REVIEWS catR, CATALOGO_BUSSINES catB);
bool searchWord(char *cadena,  char *word);
TABLE travessiaReviewPorIdU(CATALOGO_REVIEWS catR, CATALOGO_BUSSINES catB, char* idU);

char * getIdU(QUERY7 s);
int existeState(char** states, char* newState, int totalSts);
TABLE travessiaRevUsersEstados (CATALOGO_REVIEWS cat_r, CATALOGO_BUSSINES cat_b);
