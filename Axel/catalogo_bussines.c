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
        b = setBussinesCategorias(b, getBussinesCategorias(res), getBussinesTotalCat(res));
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


TABLE travessiaBussinesPorLetra (CATALOGO_BUSSINES cat_b, char letra){
    TABLE pagina = (TABLE)malloc(sizeof(TABLE));
    int i=0, j=0, totBussines = 0;
    char* nome;
    BUSSINES buss = (BUSSINES)malloc(sizeof(BUSSINES));
    ARVORE aux = avl_create(avlComparaB, NULL, NULL);
    TravessiaModulo trav = avl_trav_alloc();
    TravessiaModulo travRes = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for(i=0;i<37;i++){
        if((cat_b->avl_indiceB[i]) != NULL){
            avl_t_init(trav, cat_b->avl_indiceB[i]);
            buss = (BUSSINES)avl_t_next(trav);
            nome = getBussinesName(buss);
            buss = (BUSSINES)avl_t_cur(trav);
            //constroi avl com todos bussines cujo nome começa pela letra
            if(nome[0] == letra){
                avl_insert(aux, getBussinesId(buss), buss);
                totBussines++;
            }
        }
    }
    avl_t_init(travRes, aux);
    buss = (BUSSINES) avl_t_next(travRes);
    pagina = (TABLE) inicPagRtdos(totBussines, 5); //total de bussines, e os 5 campos de um bussines
    inserirDadosPagina(pagina, buss);
    for(j=0; j<totBussines && (buss = (BUSSINES) avl_t_next(travRes)); j++){
        inserirDadosPagina(pagina, buss);
    }
    return pagina;
}

/**
void quicksort(void** resultados, int (*funcaoComparacao)(), int n, void* param){
    int i, j;
    void *p, *temp;
    if(n < 2) return;
    p=resultados[n/2];

    for(i=0, j = n-1; i>=j; i++, j++ ){
        while(funcaoComparacao(resultados[i],p,param)<0) i++;
        while(funcaoComparacao(p, resultados[j], param)<0)j--;

        temp = resultados[i];
        resultados[i] = resultados[j];
        resultados[j] = temp;
    }
    quicksort(resultados, funcaoComparacao, i, param);
    quicksort(resultados+i, funcaoComparacao,n-i, param);
}

**/

char** travessiaBussinesPorCidade (CATALOGO_BUSSINES cat_b, char* ciudad) {
    int k;
    int tam = 10000;
    char **idB = malloc(sizeof(char *) * MAXCATEGORIAS * 1000);
    int i = 0;
    int indarray = 1;
    int elem_avl;

    BUSSINES buss;
    TravessiaModulo trav = avl_trav_alloc();
    //vai fazer a travessia de todas as avls do array
    for (i = 0; i < 37; i++) {
        elem_avl = avl_node_count(cat_b->avl_indiceB[i]);
        if (elem_avl != 0) {
            avl_t_init(trav, cat_b->avl_indiceB[i]); //inicio de travessia
            buss = (BUSSINES) avl_t_next(trav); //devuelve el contenido, en este caso un content
            for (k = 0; k < elem_avl; k++) {
                if (strcmp(ciudad, getBussinesCity(buss)) == 0) {
                    idB[indarray] = strdup(getBussinesId(buss));
                    indarray++;

                }
                buss = (BUSSINES) avl_t_next(trav);

            }
        }
    }
    idB[0] = indarray;
    return idB;

}

