#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "bussines.h"


/** ---------------- Estruturas de Dados ---------------**/
struct bussines{
    char *idBussines;
    char *nameBussines;
    char *cityBussines;
    char *stateBussines;
    char **categorias;
    int totalCat;

};


BUSSINES initB(){
    int i=0;
    BUSSINES bussines = (BUSSINES)malloc(sizeof(struct bussines));
    bussines->idBussines= (char*)malloc(TAM_IDS* sizeof(char));
    bussines->nameBussines= (char*)malloc(MAXCAT*sizeof(char));
    bussines->cityBussines= (char*)malloc(MAXCAT*sizeof(char));
    bussines->stateBussines= (char*)malloc(MAXCAT*sizeof(char));
    bussines->categorias= (char**)malloc(sizeof(char)*MAXCAT);
    for(i=0; i<MAXCAT;i++){
        bussines->categorias[i]=(char*)malloc(TAM_CATEG*sizeof(char));
    }
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
    bussines->idBussines= strdup(id);
    bussines->nameBussines= strdup(name);
    bussines->cityBussines= strdup(city);
    bussines->stateBussines= strdup(state);
    bussines->totalCat= numCat;
    bussines->categorias= (char**)malloc(sizeof(char)*numCat*TAM_CATEG);
    for(i=0; i<numCat;i++){
        bussines->categorias[i]=strdup(categories[i]);
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

char** getBussinesCategorias(BUSSINES b){
    return b->categorias;
}
char** getBussinesCateg(BUSSINES b){
    int i;
    char**copycateg=(char**) malloc(b->totalCat*(TAM_CATEG)*sizeof (char));
    for(i=0; i<(b->totalCat);i++){
        copycateg[i]=strcpy(copycateg[i],b->categorias[i]);
    }
    //  printf("sai do ciclo\n");
    return copycateg;
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

BUSSINES setBussinesCategorias(BUSSINES b, char** categories, int totalCat){
    b->categorias=(char**) malloc((totalCat)*(TAM_CATEG+1)*sizeof (char));
    int i = 0;
    for(i=0; i<totalCat;i++){
        b->categorias[i]=strdup(categories[i]);
    }
    return b;
}
