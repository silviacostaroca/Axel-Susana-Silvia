#include "stdio.h"
#include <ctype.h>
#include "avl.h"
#include "reviews.h"
#include "catalogo_reviews.h"



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

