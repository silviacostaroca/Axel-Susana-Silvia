#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "bussines.h"
#include "avl.h"


/** ---------------- Estruturas de Dados ---------------**/
struct bussines{
    char *idBussines;
    float* stars;
    char *nameBussines;
    char *cityBussines;
    char *stateBussines;
    ARVORE categorias;
    int totalCat;
    int totalStars;
};


int avlComparaCateg(const void *avlA, const void *avlB, void *avlParam){
    char *a = (char *) avlA;
    char *b = (char *) avlB;
    return strcmp(a,b);
}

BUSSINES initB(){
    int i=0;
    BUSSINES bussines = (BUSSINES)malloc(sizeof(struct bussines));
    bussines->idBussines= (char*)malloc(TAM_IDS* sizeof(char));
    bussines->nameBussines= (char*)malloc(MAXCAT*sizeof(char));
    bussines->cityBussines= (char*)malloc(MAXCAT*sizeof(char));
    bussines->stateBussines= (char*)malloc(MAXCAT*sizeof(char));
    bussines->stars=(float *) malloc(MAXCAT*sizeof (float));
    bussines->categorias= avl_create(avlComparaCateg, NULL, NULL);
    return bussines;
}


BUSSINES initBussines(char* id, char* name, char* city, char* state, char** categories, int numCategorias){
    int i=0;
    int tamName = strlen(name)+1;
    int tamCity = strlen(city)+1;
    int tamState = strlen(state)+1;
    int numCat= numCategorias;
    BUSSINES bussines = (BUSSINES)malloc(sizeof(struct bussines));
    bussines->idBussines= (char*)malloc(TAM_IDS* sizeof(char));
    bussines->nameBussines= (char*)malloc(tamName*sizeof(char));
    bussines->cityBussines= (char*)malloc(tamCity*sizeof(char));
    bussines->stateBussines= (char*)malloc(tamState*sizeof(char));
    bussines->stars=(float *) malloc(MAXCAT*sizeof (float));
    bussines->categorias= avl_create(avlComparaCateg, NULL, NULL);
    bussines->idBussines= strdup(id);
    bussines->nameBussines= strdup(name);
    bussines->cityBussines= strdup(city);
    bussines->stateBussines= strdup(state);
    bussines->totalCat= numCat;
    bussines->totalStars =0;
    for(i=0; i<numCat;i++){
        avl_insert(bussines->categorias, categories[i],categories[i]);
    }
    return bussines;
}

/** -------------------- GETS -----------------------**/
char* getBussinesId(BUSSINES b){
    return b->idBussines;
}

char* getBussinesName(BUSSINES b){
    return b->nameBussines;
}

char* getBussinesCity(BUSSINES b){
    return b->cityBussines;
}

char* getBussinesState(BUSSINES b){
    return b->stateBussines;
}

int getBussinesTotalCat(BUSSINES b){
    return b->totalCat;
}

ARVORE getBussinesCategorias(BUSSINES b){
    return b->categorias;
}

float* getBussinesStars (BUSSINES b){
    return b->stars;
}

int getBussinesTotalstars (BUSSINES b){
    return b->totalStars;
}

/** --------------- sets ------------------- **/

BUSSINES setBussinesId(BUSSINES b, char* id){
    char* idB= (char*) malloc(sizeof(char)*strlen(id));
    idB = strcpy(idB,id);
    b->idBussines = strdup(idB);
    return b;
}

BUSSINES setBussinesName(BUSSINES b, char* nome){
    char* name= (char*) malloc(sizeof(char)*strlen(nome));
    name = strcpy(name, nome);
    b->nameBussines = strdup(name);
    return b;
}

BUSSINES setBussinesCity(BUSSINES b, char* city){
    char* cidade=(char*) malloc(sizeof(char)*strlen(city));
    cidade = strcpy(cidade,city);
    b->cityBussines = strdup(cidade);
    return b;
}

BUSSINES setBussinesState(BUSSINES b, char* state){
    char* estado= (char*) malloc(sizeof(char)*strlen(state));
    estado = strcpy(estado,state);
    b->stateBussines = strdup(estado);
    return b;
}

BUSSINES setBussinesTotalCategorias(BUSSINES b, int numCat){
    b->totalCat = numCat;
    return b;
}

BUSSINES setBussinesCategorias(BUSSINES b, ARVORE categoria){
    b->categorias = categoria;
    return b;
}
BUSSINES setBussinesTotalStars(BUSSINES b, int numStars){
    b->totalStars = numStars;
    return b;
}
BUSSINES setBussinesStarsArray(BUSSINES b, float* stars , int totalStars){
    b->stars=(float*) malloc((totalStars)*sizeof (float));
    int i = 0;
    for(i=0; i<totalStars;i++){
        b->stars[i]=stars[i];
    }
    return b;
}

BUSSINES setBussinesStars (BUSSINES b, float star, int numStars){
    if(sizeof(b->stars) == numStars){
        b->stars = (float*)realloc(b->stars,sizeof (float)*2*sizeof(b->stars));
    }
    b->stars[numStars] = star;
    return b;
}