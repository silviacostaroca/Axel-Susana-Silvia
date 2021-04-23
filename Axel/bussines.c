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
    bussines->categorias= (char**)malloc(sizeof(char)*numCat);
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
    char**copycateg=(char**) malloc(b->totalCat*(TAM_CATEG+1)*sizeof (char));
    for(i=0; i<(b->totalCat);i++){
        copycateg[i]=strcpy(copycateg[i],b->categorias[i]);
    }
    //  printf("sai do ciclo\n");
    return copycateg;
}


/** --------------- sets ------------------- **/

BUSSINES setBussinesId(BUSSINES b, char* id){
    char* idB = strdup(id);
    b->idBussines = strdup(idB);
    return b;
}

BUSSINES setBussinesName(BUSSINES b, char* nome){
    char* name = strdup(nome);
    b->nameBussines = strdup(name);
    return b;
}

BUSSINES setBussinesCity(BUSSINES b, char* city){
    char* cidade = strdup(cidade);
    b->cityBussines = strdup(cidade);
    return b;
}

BUSSINES setBussinesState(BUSSINES b, char* state){
    char* estado = strdup(state);
    b->stateBussines = strdup(estado);
    return b;
}

BUSSINES setBussinesTotalCategorias(BUSSINES b, int numCat){
    b->totalCat = numCat;
    return b;
}

BUSSINES setBussinesCategorias(BUSSINES b, char** categories, int totalCat){
    int i = 0;
    for(i=0; i<totalCat;i++){
        b->categorias[i]=strdup(categories[i]);
    }
    return b;
}

BUSSINES setUserCategorias(BUSSINES b, char** categorias, int totalCat){

    b->categorias=(char**) malloc((totalCat)*(TAM_CATEG+1)*sizeof (char));
    if(b->categorias==NULL) printf("El malloc correu mal\n");
    int i = 0;
    for(i=0; i<totalCat;i++){
        printf("friends %d %s\n",i,categorias[i]);
        (b->categorias[i])=strdup(categorias[i]);
    }
    printf("sai friends %d %s\n",i,categorias[i]);
    return b;
}
