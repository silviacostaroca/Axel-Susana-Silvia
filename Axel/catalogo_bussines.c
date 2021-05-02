#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include <ctype.h>
#include "avl.h"

#include "bussines.h"
#include "catalogo_bussines.h"
#include "paginacao.h"



struct catalogoBussines{
    int totalBussines;
    ARVORE avl_indiceB [37]; //27 letras + 9 algarismos, porque os ids podem começar por letra ou numero
};


/*********** Estruturas Auxiliares **********/

struct query8{
    BUSSINES b;
    float media;
};



/**

struct media{
    char* idB;
    float mediaStars;
};

struct cidade{
    char* cidade;
    MEDIA* bussinesMedia;
    int totalMedia;
};

struct res{
    char* cidades;
    BUSSINES buss;
};


char * getQUERY6City(QUERY6 res){
    return res->cidades;
}

BUSSINES getQUERY6Buss(QUERY6 res){
    return res->buss;
}
**/


BUSSINES getBussinesQuery8(QUERY8 res){
    return res->b;
}


int avlComparaB(const void *avlA, const void *avlB, void *avlParam){
    char *a = (char *) avlA;
    char *b = (char *) avlB;
    return strcmp(a,b);
}

//Función que crea e inicia el cátologo de bussines.

CATALOGO_BUSSINES initCatBussines(){
    int i;
    CATALOGO_BUSSINES bussines=malloc(37*sizeof(struct catalogoBussines));
    bussines->totalBussines=0;
    for(i=0;i<37;i++){
        bussines->avl_indiceB[i]= avl_create(avlComparaB, NULL, NULL);
    }
    return bussines;
}


//Función que insere un bussines en un catalogo de bussiness.
int calculaIndiceBussines(char l){
    int i=0;
    char letra = toupper(l);
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


void inserirBussinesCatalogo(CATALOGO_BUSSINES cataB, char*idB, char*nameB, char*city, char*state, char**categorias, int totalcat){
    char* idBussines = strdup(idB);
    int indice= calculaIndiceBussines(idB[0]);
    BUSSINES bussines = initBussines(idBussines, nameB, city, state, categorias, totalcat);
    avl_insert(cataB->avl_indiceB[indice], getBussinesId(bussines),bussines);
    cataB->totalBussines++;
    // free (bussines);
}


//Funcion que calcula el numero total de bussines en un catálogo.
int getTotalBussines(CATALOGO_BUSSINES catB){
    return catB->totalBussines;
}


//Função que dado um catalogo e um caracter, devolve o indice correspondente a esse caracte
int getAVLIndiceB(CATALOGO_BUSSINES a, char c){
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


//Função que dado um id de b bussines valida se ele existe

int existeBussines(CATALOGO_BUSSINES catB, BUSSINES b){
    int lInicial = getAVLIndiceB(catB, getBussinesId(b)[0]);
    if(avl_find(catB->avl_indiceB[lInicial], getBussinesId(b))==NULL)return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}

//Função que dado um id devolve a informação de um bussines
BUSSINES getBussines(CATALOGO_BUSSINES catB, char * idB){

    int i = getAVLIndiceB(catB, idB[0]);
    BUSSINES res = (BUSSINES) malloc(MAXCAT*sizeof (BUSSINES));
    BUSSINES b = (BUSSINES) malloc(MAXCAT*sizeof (BUSSINES));
    res = (BUSSINES) avl_find(catB->avl_indiceB[i], idB);
    if (res != NULL) {
        b = setBussinesName(b, getBussinesName(res));
        b = setBussinesCity(b, getBussinesCity(res));
        b = setBussinesState(b, getBussinesState(res));
        b = setBussinesStarsArray(b, getBussinesStars(res), getBussinesTotalstars(res));
        b = setBussinesTotalStars(b,getBussinesTotalstars(res));
        b = setBussinesTotalCategorias(b, getBussinesTotalCat(res));
        b = setBussinesCategorias(b, getBussinesCategorias(res));
        b = setBussinesId(b, getBussinesId(res));
        return b;
    } else {
        printf("O id indicado nao tem correspondencia!\nPor favor inserir id valido\n");
        return NULL;
    }
}

ARVORE getCatalogoBussinesPorLetra(CATALOGO_BUSSINES cat_b, char l) {
    return cat_b->avl_indiceB[calculaIndiceBussines(l)];
}

ARVORE getCatalogoBussinesPorIndice(CATALOGO_BUSSINES cat_b, int i) {
    return cat_b->avl_indiceB[i];
}


/** ---------------------------- TRAVESSIAS E CONTRUÇÃO DE RESULTADO ------------------------------ **/
void freeTravessia(TravessiaModulo trav){
    if(trav != NULL){
        avl_trav_free(trav);
    }
}

//Função usada na query 2
TABLE travessiaBussinesPorLetra (CATALOGO_BUSSINES cat_b, char letra){
    TABLE pagina = (TABLE)malloc(sizeof(TABLE));
    int i=0, j=0, k=0, totBussines = 0;
    char* nome;
    BUSSINES buss;
    int elem_avl=0;
    ARVORE aux = avl_create(avlComparaB, NULL, NULL);
    TravessiaModulo trav = avl_trav_alloc();
    TravessiaModulo travRes = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for(i=0;i<37;i++){
        elem_avl = avl_node_count(cat_b->avl_indiceB[i]);
        if(elem_avl != 0){
            avl_t_init(trav, cat_b->avl_indiceB[i]);
            buss = (BUSSINES)avl_t_next(trav);
            for(k=0; k<elem_avl; k++){
                nome = getBussinesName(buss);
                //buss = (BUSSINES)avl_t_cur(trav);
                //constroi avl com todos bussines cujo nome começa pela letra
                if(nome[0] == letra){
                    avl_insert(aux, getBussinesId(buss), buss);
                    totBussines++;
                }
                buss = (BUSSINES)avl_t_next(trav);
            }
        }
    }
    avl_t_init(travRes, aux);
    buss = (BUSSINES) avl_t_next(travRes);
    pagina = (TABLE) initPagResulatos(totBussines, 1); //total de bussines
    inserirDadosPagina(pagina, buss);
    for(j=0; j<totBussines && (buss = (BUSSINES) avl_t_next(travRes)); j++){
        inserirDadosPagina(pagina, buss);
    }
    return pagina;
}

//QUERY 5
int validaStars(float* stars, float star, int totalStars){
    int i;
    for(i=0; i<totalStars; i++){
        if(stars[i] >= star){
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}


char* strUpper2(char* str){
    char* str2 = (char*)malloc(sizeof (char)*50);
    int i=0;
    for(i=0; i<strlen(str); i++){
        str2[i]=toupper(str[i]);
    }
    return str2;
}

TABLE travessiaBussinesPorCidadeEstrela (CATALOGO_BUSSINES cat_b, char* cidade, float estrela){
    TABLE pagina = (TABLE)malloc(sizeof(TABLE));
    int k=0, i = 0, j=0, totBussines = 0;
    int elem_avl;
    BUSSINES buss;
    ARVORE aux = avl_create(avlComparaB, NULL, NULL);
    TravessiaModulo trav = avl_trav_alloc();
    TravessiaModulo travRes = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        elem_avl = avl_node_count(cat_b->avl_indiceB[i]);
        if (elem_avl != 0){
            avl_t_init(trav, cat_b->avl_indiceB[i]); //inicio de travessia
            buss = (BUSSINES) avl_t_next(trav); //devuelve el contenido, en este caso un content
            for (k = 0; k < elem_avl; k++) {
                char * city = (char*) malloc(sizeof(char)*50);
                city = strUpper2(getBussinesCity(buss));
                if (strcmp(cidade, city) == 0) {
                    if(validaStars(getBussinesStars(buss), estrela, getBussinesTotalstars(buss)) == EXIT_SUCCESS){
                        avl_insert(aux, getBussinesId(buss), buss);
                        totBussines++;
                    }
                }
                buss = (BUSSINES) avl_t_next(trav);
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

/**
//query 6
//primeiro faz uma travessia e constroi um array de cidades
ARVORE getAvlCidades(CATALOGO_BUSSINES catB){
    ARVORE cidades = avl_create(avlComparaB, NULL, NULL);
    int k=0, i = 0;
    int elem_avl;
    BUSSINES buss;
    CIDADE cidadeInfo = (CIDADE) malloc(sizeof (CIDADE));
    TravessiaModulo trav = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        elem_avl = avl_node_count(catB->avl_indiceB[i]);
        if (elem_avl != 0){
            avl_t_init(trav, catB->avl_indiceB[i]);
            buss = (BUSSINES) avl_t_next(trav);
            for (k = 0; k < elem_avl; k++) {
                if(buss != NULL){
                    cidadeInfo->cidade = strcpy(cidadeInfo->cidade, getBussinesCity(buss));
                    cidadeInfo->bussinesMedia = NULL;
                    avl_insert(cidades, getBussinesCity(buss), cidadeInfo);
                }
            }
            buss = (BUSSINES) avl_t_next(trav);
        }
    }
    return cidades;
}

float calculaMedia(float* stars, int totalStars){
    int i;
    float media;
    for(i=0; i<totalStars; i++){
        media= media + stars[i];
    }
    return media/totalStars;
}

// Função auxiliar de comparação
float compara (float a, float b){
    if (a < b)
        return 1;
    else
        return 0;
}
// Ordenação bolha //
void bolha (float totalStars, float* stars){
    int i, j;
    for (i=totalStars-1; i>0; i--) {
        int troca = 0;
        for (j=0; j<i; j++)
            if (compara(stars[j],stars[j+1])) { // troca //
                float temp = stars[j];
                stars[j] = stars[j+1];
                stars[j+1] = temp;
                troca = 1;
            }
        if (troca == 0) // nao houve troca //
            return;
    }
}


//segunda travessia calcula as medias e constroi o array das medias ordenado
//por fim devolve os primeiros n
TABLE travessiaTopNegociosPorCidade(CATALOGO_BUSSINES catB, int n) {
    TABLE pagina = (TABLE) malloc(sizeof(TABLE));
    int k = 0, i = 0, j = 0,m=0,ind =0, totBussines = 0;
    int elem_avl;
    BUSSINES buss;
    float media;
    CIDADE cidadeInfo = (CIDADE) malloc(sizeof (CIDADE));
    ARVORE cidades = getAvlCidades(catB);
    TravessiaModulo trav = avl_trav_alloc();
    TravessiaModulo travRes = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        elem_avl = avl_node_count(catB->avl_indiceB[i]);
        if (elem_avl != 0) {
            avl_t_init(trav, catB->avl_indiceB[i]);
            buss = (BUSSINES) avl_t_next(trav);
            for (k = 0; k < elem_avl; k++) {
                char *city = (char *) malloc(sizeof(char) * 50);
                city = getBussinesCity(buss);
                media = calculaMedia(getBussinesStars(buss), getBussinesTotalstars(buss));
                cidadeInfo = avl_find(cidades, city);
                if(cidadeInfo != NULL){
                    cidadeInfo->bussinesMedia[m]->idB = getBussinesId(buss);
                    cidadeInfo->bussinesMedia[m]->mediaStars = media;
                    cidadeInfo->totalMedia++;
                    avl_replace(cidades, cidadeInfo->cidade, cidadeInfo);
                }
                buss = (BUSSINES) avl_t_next(trav);

            }
        }
    }
    //No fim deste ciclo temos uma avom as cidades e os ids de negocio e medias
    //percorrer esta avl ver o top n e devolver para a pagina
    avl_t_init(travRes, cidades);
    QUERY6 res = (QUERY6)malloc(sizeof(QUERY6));
    cidadeInfo = (CIDADE) avl_t_next(travRes);
    int totalCidades = avl_node_count(cidades);
    pagina = (TABLE) initPagResulatos(totalCidades*n, 2);//tamanho = nº total de cidades * os n negócios a mostrar
    for (j = 0; j < avl_node_count(cidades); j++) {
        //percorrer array das medias
        for(ind = 0; i<cidadeInfo->totalMedia || i<n; i++);{
            res->cidades = cidadeInfo->cidade;
            res->buss = avl_find(getCatalogoBussinesPorLetra(catB, cidadeInfo->bussinesMedia[ind]->idB[0]), cidadeInfo->bussinesMedia[ind]->idB);
            inserirDadosPagina(pagina, res);
        }
        cidadeInfo = (CIDADE) avl_t_next(travRes);
    }
    return pagina;
}
**/


// QUERY 8

float calculaMedia(float* stars, int totalStars){
    int i;
    float media = 0;
    float soma = 0;
    for(i=0; i<totalStars; i++){
        soma = soma + stars[i];
    }
    media = soma/totalStars;
    return media;
}
/**
int insereTopN (int totalInseridos, int n, QUERY8 * topN, QUERY8 new){
    if(totalInseridos < n){ //o top ainda nao esta cheio, entao insere
        topN[totalInseridos] = new;
        totalInseridos++;
    }
    else{
        //ja temos o top preenchido e vamos comparar as medias
        int i = 0;
        for(i=0; i<n; i++){
            if(topN[i]->media < new->media){ //o novo tem uma media mais alta, entao substitui
                topN[i] = new;
            }
        }
    }
    return totalInseridos;
}
**/

TABLE travessiaBussinesPorCategoria(CATALOGO_BUSSINES catB, int n, char* categoria) {
    TABLE pagina = (TABLE) malloc(sizeof(TABLE));
    int k = 0, i = 0, j = 0;
    int elem_avl;
    BUSSINES buss;
    QUERY8 topNArray[n];
    for(int l=0; l<n; l++){
        topNArray[l]=NULL;
    }
    QUERY8 aux = (QUERY8)malloc(sizeof(QUERY8));
    aux->b = (BUSSINES)malloc(sizeof(BUSSINES));
    char* categ = (char*)malloc(sizeof(char)*TAM_CATEG);
    int totalInseridos = 0;
    TravessiaModulo trav = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        elem_avl = avl_node_count(catB->avl_indiceB[i]);
        if (elem_avl != 0) {
            avl_t_init(trav, catB->avl_indiceB[i]);
            buss = (BUSSINES) avl_t_next(trav);
            for (k = 0; (k < elem_avl) && (buss != NULL); k++) {
                categ = (char*) avl_find(getBussinesCategorias(buss), categoria);
                if(categ != NULL){ //O negocio tem aquela categoria
                    //Calcula a media de stars
                    aux->b = buss;
                    aux->media = calculaMedia(getBussinesStars(buss), getBussinesTotalstars(buss));
                    //Valida se tem lugar no top ou nao
                    if(totalInseridos < n){ //o top ainda nao esta cheio, entao insere
                        topNArray[totalInseridos]= aux;
                        totalInseridos++;
                    }
                    else{
                        //ja temos o top preenchido e vamos comparar as medias
                        int i = 0;
                        for(i=0; i<n; i++){
                            if(topNArray[i]->media < aux->media){ //o novo tem uma media mais alta, entao substitui
                                topNArray[i] = aux;
                            }
                        }
                    }
                }
                buss = (BUSSINES) avl_t_next(trav);
            }
        }
    }
    pagina = (TABLE) initPagResulatos(totalInseridos, 1);
    for (j = 0; j < totalInseridos; j++) {
        inserirDadosPagina(pagina, topNArray[j]);
    }
    return pagina;
}