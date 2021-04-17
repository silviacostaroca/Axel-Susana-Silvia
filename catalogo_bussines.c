//
// Created by Silvia Acosta on 31/03/2021.
//

#include "catalogo_bussines.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "avl.h"


struct bussines{
    char *idBussines;
    char *nameBussines;
    char *cityBussines;
    char *stateBussines;
    char *categorias[MAXBUSSINES];

};

struct catalogoBussines{
    int totalBussines;
    TABLE avl_indiceB [36]; //27 letras + 9 algarismos, porque os ids podem começar por letra ou numero
};

/**
// Função que inicializa o BUSSINES

BUSSINES initBussines(){
    BUSSINES b = malloc(sizeof(struct bussines));
    b->categorias = malloc(MAXBUSSINES*sizeof(char)*22);
    int i =0;
    b->idBussiness = "";
    b->nameBussines = "";
    b->cityBussines = "";
    b->stateBussines = "";
    for(i=0; i<MAXBUSSINES; i++){
        b->categorias[i]="";
    }
    return b;
}


 * Funciono que crea un nuevo bussines.

BUSSINES creaBussines(char *id, char *name, char *city,char *state,char **categ){
    BUSSINES b = initBussines(); //malloc(sizeof(struct user));
    int i = 0;
    strcpy(b->idBussiness, id);
    strcpy(b->nameBussines, name);
    strcpy(b->cityBussines, id);
    strcpy(b->stateBussines, name);
    for(i=0; i<MAXFRIENDS; i++){
        strcpy(b->categoriasr[i], categ[i]);
    }
    return b;
}


 * Función que crea e inicia el cátologo de bussines.

CATALOGO_BUSSINES initCatBussines(){
    int i;
    CATALOGO_BUSSINES bussines=malloc(37*sizeof(struct catalogoBussines));
    bussines->totalBussines=0;
    for(i=0;i<37;i++){
        bussines->avl_indiceB[i]= avl_create(bussines, NULL, NULL);
    }
    return bussines;
}

int calculaIndiceBussines(char l) {
    char letra = toupper(l);
    int i = 0;
    if (isalpha(letra)) {
        i = letra - 'A';
    } else {
        i = 36;
    }
    return i;
}

//Função que dado um user e uma variàvel do tipo BUSSINES, copia a informação
static BUSSINES copyBussines(BUSSINES b, BUSSINES copia){
    int i;
    strcpy(copia->idBussiness, b->idBussiness);
    strcpy(copia->nameBussines, b->nameBussines);
    strcpy(copia->cityBussines, b->cityBussines);
    strcpy(copia->stateBussines, b->stateBussines);
    for(i=0; i<MAXBUSSINES; i++){
        strcpy(copia->categorias[i], b->categorias[i]);
    }
    return copia;
}

//Función que insere un bussines en un catalogo de bussiness.
void inserirBussinesCatalogo(CATALOGO_BUSSINES cataB, BUSSINES b){
    int i = calculaIndiceBussines(b->idBussiness[0]); //calcula o indice onde vai ser inserido o user
    void * res;
  BUSSINES copia_bussines = malloc(sizeof(struct bussines));
    copia_bussines->categorias = malloc(MAXBUSSINES*sizeof(char)*22);
    copia_bussines = copyBussines(b, copia_bussines);
    res = avl_insert(cataB->avl_indice[i], copia_bussines);
    if(res != NULL)
        cataB->totalBussines++;
}


 * Función que dado un bussines retorna su id.


char * getCodBussines(BUSSINES b){
    return b->idBussines;
}


 * Dado un cátologo de bussines y una letra inicial la função devuelve el avl de bussines que comienzan por esa letra.


TABLE getAVLBussines(CATALOGO_BUSSINES b,int x){
    return b[x].avl_indice;
}

char * cloneId(char *idB){
    int tamanho = strlen(idB);
    char* novoId;

    novoId = (char*) malloc(tamanho + 1);
    strncpy(novoId, idB, tamanho + 1);

    return novoId;
}

void freeId(char * idB){
    free(idB);
}


// Función que verifica si un bussines ya existe.
//Retorna 0 caso no exista y 1 si existe.



int existeUser(CATALOGO_USER catU, USER a){
    int lInicial = a->idUser[0]-65;
    if(avl_find(catU[lInicial].avl_indice,a->idUser)==NULL) return 0;
    else return 1;
}

int existeBussines(CATALOGO_BUSSINES catB, BUSSINES b){
    int lInicial = b->idBussiness[0]-65;
    if(avl_find(catB[lInicial].avl_indice,b->idBussiness)==NULL) return 0;
    else return 1;
}


//Funcion que calcula el numero total de bussines  en un catálogo.

int totalBussines(CATALOGO_BUSSINES catB){
    int i,total=0;
    for(i=0;i<36;i++){
        total+=catB[i].totalBussines;
    }
    return total;
}

*/
