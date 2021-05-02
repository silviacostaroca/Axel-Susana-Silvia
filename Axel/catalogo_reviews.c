#include "stdio.h"
#include <ctype.h>
#include "avl.h"
#include "reviews.h"
#include "user.h"
#include "catalogo_reviews.h"
#include "catalogo_bussines.h"
#include "catalogo_users.h"
#include "paginacao.h"



/** ---------------- Estruturas de Dados ---------------**/

//estructura de array de AVL por ordem alfabético para el catalogo de reviews
struct catalogoReviews{
    int totalReviews ;
    ARVORE avl_indiceR [37]; //27 letras + 9 algarismos, porque os ids podem começar por letra ou numero
};


//estruturas auxiliares
struct states{
    char* idUStates;
    char** state;
    int totalStates;
};



/** ---------- Funções Sobre Estruturas de Dados ---------------**/

char * getIdU(QUERY7 s){
    return s->idUStates;
}


//Funçao auxiliar usada na função avl_create, que dado duas avl e um parâmetro faz o cast e compara
int avlComparaR(const void *avlA, const void *avlB){
    char *a = (char *) avlA;
    char *b = (char *) avlB;
    return strcmp(a,b);
}
int calculaIndiceReview(char l) {
    char letra = toupper(l);
    int i;
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
    REVIEW review= initReview(idR, idU, idB, estrelas, util, div, col, data, texto);
    avl_insert(cataR->avl_indiceR[indice], getReviewIdR(review), review);
    cataR->totalReviews++;

}


//Funcion que calcula el numero total de reviews en un catálogo.
int getTotalReviews (CATALOGO_REVIEWS catR){
    return catR->totalReviews;
}


//Função que dado um catalogo e um caracter, devolve o indice correspondente a esse caracte
int getAVLIndiceR(CATALOGO_REVIEWS a, char c){
    int i;
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
    REVIEW res;
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
    int i;
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
    int tam;
    char **idB = malloc(sizeof(char*) * MAXTEXT * tam);
    int i;
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
                if (stars== getReviewStars(rev)) {
                    idB[indarray] = strdup(getReviewIdB(rev));
                    //  printf("Las estrellas de este negocio son %d\n", (int) stars[indarray]);
                    indarray++;

                }
                rev = (REVIEW) avl_t_next(trav);

            }
        }
    }
    idB[0]=indarray;
    return idB;
}
/**
bool searchWord(char *cadena,  char *word){
    int length = strlen(word);
    bool result = true;
    for(int i=0;i<strlen(cadena);i++){
        if (strstr(cadena,word)){
            if (*(cadena+i-1) == ' ' && *(cadena+i+length) == ' ' && ispunct (*(cadena+i-1))!=0
            && ispunct(*(cadena+i+length))!=0){
                for(int j=0; j<length; j++){
                    result = *(cadena+i+j) == *(word+j) ? true & result : false & result;
                    return result;
                }
            }
        }
    }
    return false;
}
 **/

char** travessiaReviewsPorPalabra (CATALOGO_REVIEWS cat_r, char* palabra) {
    int k;
    int tam = 100000;
    char **idR = malloc(sizeof(char*) * MAXTEXT * tam);
    int i;
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
                if (strstr(getReviewText(rev),palabra)!=NULL) {
                    idR[indarray] = strdup(getReviewIdR(rev));
                    indarray++;
                }
                rev = (REVIEW) avl_t_next(trav);
            }
        }
    }
    idR[0]=indarray;
    return idR;
}
CATALOGO_BUSSINES estruturaConStars (CATALOGO_REVIEWS catR, CATALOGO_BUSSINES catB) {
    int k;
    int i;
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
                if (buss!=NULL) {
                    buss = setBussinesStars(buss, getReviewStars(rev), getBussinesTotalstars(buss));
                    buss = setBussinesTotalStars(buss, (getBussinesTotalstars(buss)) + 1);
                    avl_replace(getCatalogoBussinesPorLetra(catB, getReviewIdB(rev)[0]), getBussinesId(buss), buss);
                }
                rev = (REVIEW) avl_t_next(trav);
            }

        }
    }
    return catB;
}


TABLE travessiaReviewPorIdU(CATALOGO_REVIEWS catR, CATALOGO_BUSSINES catB, char* idU){
    TABLE pagina;
    int k, i, j, totBussines = 0;
    int elem_avl;
    BUSSINES buss;
    REVIEW rev;
    ARVORE aux = avl_create(avlComparaR, NULL, NULL);
    TravessiaModulo trav = avl_trav_alloc();
    TravessiaModulo travRes = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        elem_avl = avl_node_count(catR->avl_indiceR[i]);
        if (elem_avl != 0){
            avl_t_init(trav, catR->avl_indiceR[i]);
            rev = (REVIEW) avl_t_next(trav);
            for (k = 0; k < elem_avl; k++) {
                char * id;
                id = getReviewIdU(rev);
                if(strcmp(idU, id)==0){
                    //sendo o idu vamos guardar a informação do negócio
                    buss = (BUSSINES) avl_find(getCatalogoBussinesPorLetra(catB, getReviewIdB(rev)[0]), getReviewIdB(rev));
                    if(buss != NULL){
                        avl_insert(aux, getBussinesId(buss), buss);
                        totBussines++;
                    }
                }
                rev = (REVIEW) avl_t_next(trav);

            }
        }
    }
    avl_t_init(travRes, aux);
    buss = (BUSSINES) avl_t_next(travRes);
    pagina = (TABLE) initPagResulatos(totBussines, 1);
    inserirDadosPagina(pagina, buss);
    for(j=0; j<totBussines && (buss = (BUSSINES) avl_t_next(travRes)); j++){
        inserirDadosPagina(pagina, buss);
    }
    return pagina;
}


//query 7

int existeState(char** states, char* newState, int totalSts){
    int i=0;
    for(i=0; i<totalSts; i++){
        if(strcmp(states[i], newState)==0)
            return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}


TABLE travessiaRevUsersEstados (CATALOGO_REVIEWS cat_r, CATALOGO_BUSSINES cat_b) {
    TABLE pagina = (TABLE)malloc(sizeof(TABLE));
    int k=0, i = 0, j=0, totUsers = 0;
    int elem_avl;
    BUSSINES buss;
    REVIEW rev;
    QUERY7 res = (QUERY7)malloc(sizeof(QUERY7));
    res->state = (char **) malloc(sizeof(char *) * 50 * 100);
    res->idUStates = (char *) malloc(sizeof(char) * TAM_IDS);
    QUERY7 avlRes = (QUERY7)malloc(sizeof(QUERY7));
    QUERY7 query7 = (QUERY7)malloc(sizeof(QUERY7));
    ARVORE aux = avl_create(avlComparaR, NULL, NULL);
    ARVORE resposta = avl_create(avlComparaR, NULL, NULL);
    TravessiaModulo trav = avl_trav_alloc();
    TravessiaModulo travRes = avl_trav_alloc();
    TravessiaModulo travUsers = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        elem_avl = avl_node_count(cat_r->avl_indiceR[i]);
        if (elem_avl != 0) {
            avl_t_init(trav, cat_r->avl_indiceR[i]); //inicio de travessia
            rev = (REVIEW) avl_t_next(trav); //devuelve el contenido, en este caso un content
            for (k = 0; k < elem_avl; k++) {



                char *id = strdup(getReviewIdU(rev));
                avlRes = (QUERY7) avl_find(aux, id);
                if (avlRes == NULL) {
                    buss = (BUSSINES) avl_find(getCatalogoBussinesPorLetra(cat_b, getReviewIdB(rev)[0]),getReviewIdB(rev));
                    if (buss != NULL) {
                        res->idUStates = strdup(id);
                        res->totalStates = 1;
                        res->state[0] = strdup(getBussinesState(buss));
                        avl_insert(aux, id, res);
                    }
                } else {
                    buss = (BUSSINES) avl_find(getCatalogoBussinesPorLetra(cat_b, getReviewIdB(rev)[0]), getReviewIdB(rev));
                    if (buss != NULL) {
                        if (existeState(avlRes->state, getBussinesState(buss), avlRes->totalStates) == EXIT_FAILURE) {
                            avlRes->state[avlRes->totalStates] = strcpy(avlRes->state[0], getBussinesState(buss));
                            avlRes->totalStates++;
                            avlRes->idUStates = getReviewIdU(rev);
                            //avl_insert(aux,avlRes->idUStates, avlRes);
                            avl_replace(aux, avlRes->idUStates, avlRes);
                        }
                    }
                }
                rev = (REVIEW) avl_t_next(trav);
            }
        }
    }
    avl_trav_free(trav);
    //vai criar uma avl só para os users que foram a mais do que um estado
    avl_t_init(travRes, aux);
    query7 = (QUERY7) avl_t_next(travRes);
    int tamanho = (int)avl_node_count(aux);
    for(int y = 0; y<tamanho;y++){
        if(query7->totalStates > 1)
            avl_insert(resposta, query7->idUStates, query7);
        query7 = (QUERY7) avl_t_next(travRes);
    }
    avl_trav_free(travRes);
    //ultima travessia paa colocar na pagina de resultados
    int totalUsers= (int)avl_node_count(resposta);
    pagina = (TABLE) initPagResulatos(totalUsers, 1);
    avl_t_init(travUsers, resposta);
    query7 = (QUERY7) avl_t_next(travUsers);
    for(j=0; j<totalUsers; j++){
        inserirDadosPagina(pagina, query7);
        query7 = (QUERY7) avl_t_next(travUsers);
    }
    return pagina;
}