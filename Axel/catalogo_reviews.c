#include "stdio.h"
#include <ctype.h>
#include "avl.h"
#include "reviews.h"
#include "catalogo_reviews.h"
#include "paginacao.h"



/** ---------------- Estruturas de Dados ---------------**/

//estructura de array de AVL por ordem alfabético para el catalogo de reviews
struct catalogoReviews{
    int totalReviews ;
    ARVORE avl_indiceR [37]; //27 letras + 9 algarismos, porque os ids podem começar por letra ou numero
};


/** ---------- Funções Sobre Estruturas de Dados ---------------**/


//Funçao auxiliar usada na função avl_create, que dado duas avl e um parâmetro faz o cast e compara
int avlComparaR(const void *avlA, const void *avlB, void *avlParam){
    char *a = (char *) avlA;
    char *b = (char *) avlB;
    return strcmp(a,b);
}
int calculaIndiceReview(char l) {
    char letra = toupper(l);
    int i = 0;
    if (isalpha(letra)) {
        i = letra - 'A';
    } else {
        i = 36;
    }
    return i;
}

//Función que inicia el cátologo de reviews

CATALOGO_REVIEWS initCatReviews() {
    int i;
    CATALOGO_REVIEWS reviews = malloc(37 * sizeof(struct catalogoReviews));
    reviews->totalReviews = 0;
    for (i = 0; i < 37; i++) {
        reviews->avl_indiceR[i]= avl_create(avlComparaR, NULL, NULL);
    }
    return reviews;
}



void inserirReviewCatalogo(CATALOGO_REVIEWS cataR, char*idR, char*idU, char*idB, float estrelas, int util, int div, int col,  char*data,  char*texto) {
    //primeiro cria REVIEW
    int indice = calculaIndiceReview(idR[0]);
    char* idReview = strdup(idR);
    REVIEW review= initReview(idR, idU, idB, estrelas, util, div, col, data, texto);
    avl_insert(cataR->avl_indiceR[indice], getReviewIdR(review), review);
    cataR->totalReviews++;
    //free (review);
}


//Funcion que calcula el numero total de reviews en un catálogo.
int getTotalReviews (CATALOGO_REVIEWS catR){
    return catR->totalReviews;
}


//Função que dado um catalogo e um caracter, devolve o indice correspondente a esse caracte
int getAVLIndiceR(CATALOGO_REVIEWS a, char c){
    int i = 0;
    char letra = toupper(c);
    if(isdigit(letra))
    {
        i = 26+(letra-48);
        return i;
    }
    if(isalpha(letra)){
        i = letra - 'A';
        return i;
    }
    else {
        i = 36;
        return i;
    }
}
//Função que dado um id de reviews valida se ele existe

int existeReview(CATALOGO_REVIEWS catR, REVIEW r){
    int lInicial = getAVLIndiceR(catR, getReviewIdR(r)[0]);
    if(avl_find(catR->avl_indiceR[lInicial], getReviewIdR(r))==NULL)return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}

//Função que dado um id devolve a informação de uma review
REVIEW getReview (CATALOGO_REVIEWS catR, char * idR) {

    int i = getAVLIndiceR(catR, idR[0]);
    REVIEW res = (REVIEW) malloc(sizeof(REVIEW));
    REVIEW r = (REVIEW) malloc(sizeof(REVIEW));

    res = (REVIEW) avl_find(catR->avl_indiceR[i], idR);
    if (res != NULL) {
        //O REVIEW EXISTE

        r = setReviewIdR(r, getReviewIdR(res));
        r = setReviewIdB(r, getReviewIdB(res));
        r = setReviewIdU(r, getReviewIdU(res));
        r = setReviewsStars(r, getReviewStars(res));
        r = setReviewsUseful(r, getReviewUseful(res));
        r = setReviewsCool(r, getReviewCool(res));
        r = setReviewsFunny(r, getReviewFunny(res));
        r = setReviewsData(r, getReviewData(res));
        r = setReviewsText(r, getReviewText(res));

        return r;

    } else {
        printf("O id indicado nao tem correspondencia!\nPor favor inserir id valido\n");
        return NULL;
    }
}

ARVORE getCatalogoReviewsPorLetra(CATALOGO_REVIEWS cat_r, char l) {
    return cat_r->avl_indiceR[calculaIndiceReview(l)];
}

ARVORE getCatalogoReviewsPorIndice(CATALOGO_REVIEWS cat_r, int i) {
    return cat_r->avl_indiceR[i];
}



/** ---------------------------- TRAVESSIAS E CONTRUÇÃO DE RESULTADO ------------------------------ **/


float* travessiaReviewsPorIdB (CATALOGO_REVIEWS cat_r, char*idBuss) {
    int k;
    int tam = 10000;
    float *stars = malloc(sizeof(float) * tam * 10000);
    int i = 0;
    int indarray =1;
    int elem_avl;

    REVIEW rev;
    TravessiaModulo trav = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        if ((cat_r->avl_indiceR[i]) != NULL) {
            elem_avl = avl_node_count(cat_r->avl_indiceR[i]);
            avl_t_init(trav, cat_r->avl_indiceR[i]); //inicio de travessia
            rev = (REVIEW) avl_t_next(trav); //devuelve el contenido, en este caso un content
            for (k = 0; k < elem_avl; k++) {
                if (strcmp(idBuss, getReviewIdB(rev))==0) {
                    // if (k == tam)
                    //     stars[k] = (float) realloc (stars, sizeof (float) * tam * 2);
                    // }
                    stars[indarray] = getReviewStars(rev);
                    //  printf("Las estrellas de este negocio son %d\n", (int) stars[indarray]);
                    indarray++;

                }
                rev = (REVIEW) avl_t_next(trav);

            }
        }
    }
    stars[0]=indarray;
    return stars;
}

char** travessiaReviewsPorStars (CATALOGO_REVIEWS cat_r, float stars) {
    int k;
    int tam = 10000;
    char **idB = malloc(sizeof(char*) * MAXTEXT * 1000);
    int i = 0;
    int indarray =1;
    int elem_avl;

    REVIEW rev;
    TravessiaModulo trav = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        elem_avl = avl_node_count(cat_r->avl_indiceR[i]);
        if (elem_avl!=0 ) {
            avl_t_init(trav, cat_r->avl_indiceR[i]); //inicio de travessia
            rev = (REVIEW) avl_t_next(trav); //devuelve el contenido, en este caso un content
            for (k = 0; k < elem_avl; k++) {
                if (stars>= getReviewStars(rev)) {
                    idB[indarray] = strdup(getReviewIdB(rev));
                    indarray++;

                }
                rev = (REVIEW) avl_t_next(trav);

            }
        }
    }
    idB[0]=indarray;
    return idB;
}

char** negociosConStars (CATALOGO_REVIEWS catR){
    char **idS = malloc(sizeof(char*) * MAXTEXT * 1000);
    int indarray=0;
    int k;

        for (k = 0; (k < catR->totalReviews); k++) {
            if(getReviewStars(catR)!=0) {
            idS[indarray] = strdup(getReviewIdB(catR));
        }
    }
    return idS;
}


CATALOGO_BUSSINES estruturaConStars (CATALOGO_REVIEWS catR, CATALOGO_BUSSINES catB) {

    int k;
    int i = 0;
    int elem_avl;

    REVIEW rev;
    BUSSINES buss;
    TravessiaModulo trav = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        elem_avl = avl_node_count(catR->avl_indiceR[i]);
        if (elem_avl != 0) {
            avl_t_init(trav, catR->avl_indiceR[i]); //inicio de travessia
            rev = (REVIEW) avl_t_next(trav); //devuelve el contenido, en este caso un content
            for (k = 0; k < elem_avl; k++) {
                buss = avl_find(getCatalogoBussinesPorLetra(catB, getReviewIdB(rev)[0]), getReviewIdB(rev));
                buss = setBussinesStars(buss, getReviewStars(rev), getBussinesTotalstars(buss));
                buss = setBussinesTotalStars(buss, (getBussinesTotalstars(buss)) + 1);
              //  avl_delete(getCatalogoBussinesPorLetra(catB, getReviewIdB(rev)[0]), getBussinesId(buss));
               //avl_insert(getCatalogoBussinesPorLetra(catB, getReviewIdB(rev)[0]), getBussinesId(buss), buss);
                avl_replace((getCatalogoBussinesPorLetra(catB, getReviewIdB(rev)[0]), getBussinesId(buss), buss);
            }
            rev = (REVIEW) avl_t_next(trav);

        }

    }

BUSSINES b= (BUSSINES)malloc (sizeof(BUSSINES));
        b= getBussines(catB,"6iYb2HFDywm3zjuRg0shjw");
    printf("id %s \n", getBussinesId(b));
    for(int i=0; i< getBussinesTotalstars(b);i++)
        printf("%f\n", getBussinesStars(b)[i]);
    return catB;
}



/**
char ** travessiaNMedioStars (CATALOGO_REVIEWS catR, char* idB){
int i,k, elem_avl;
float c=0;
float stars=0;
int indarray=0;
float mediastars=0;
float** starsmedia = malloc(sizeof(float*) * 1000);

    REVIEW rev;
    TravessiaModulo trav = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        elem_avl = avl_node_count(catR->avl_indiceR[i]);
        if (elem_avl!=0 ) {
            avl_t_init(trav, catR->avl_indiceR[i]); //inicio de travessia
            rev = (REVIEW) avl_t_next(trav); //devuelve el contenido, en este caso un content
            for (k = 0; k < elem_avl; k++) {
                if (strcmp(idB, getReviewIdB(rev))==0) {
                    stars += (getReviewStars(rev));
                    c++;
                    mediastars = stars/c;
                    starsmedia[indarray]= &mediastars;
                    indarray++;

                }

                rev = (REVIEW) avl_t_next(trav);

            }
        }

    }

    return idB;
}

int funcionQueCompara(const void *a, const void *b) {
    int aInt = *(int *) a;
    int bInt = *(int *) b;
    return bInt - aInt;
}
 **/