#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "avl.h"
#include "catalogo_users.h"
#include "user.h"

/** ---------------- Estruturas de Dados ---------------**/
//estructura de array de AVL por ordem alfabético para el catalogo de usuarios
struct catalogoUser{
    int totalUsers;
    ARVORE avl_indice[37]; //26 letras + 10 algarismos, porque os ids podem começar por letra, numero ou outro caracter
};

/** ---------- Funções Sobre Estruturas de Dados ---------------**/

//Funçao auxiliar usada na função avl_create, que dado duas avl e um parâmetro faz o cast e compara
int avlCompara(const void *avlA, const void *avlB, void *avlParam){
    char *a = (char *) avlA;
    char *b = (char *) avlB;
    return strcmp(a,b);
}

//Función que inicia el cátologo de users
CATALOGO_USER initCatUser(){
    int i;
    CATALOGO_USER users=malloc(37*sizeof(struct catalogoUser));
    users->totalUsers=0;
    for(i=0;i<37;i++){
        users->avl_indice[i]= avl_create(avlCompara, NULL, NULL);
    }
    return users;
}

//Função que dado um caracter devolve o indice correspondente
int calculaIndiceUser(char l) {
    char letra = toupper(l);
    int i = 0;
    if (isalpha(letra)) {
        i = letra - 'A';
        return i;
    }
    if(isdigit(letra)){
        i = 26+(letra-48);
        return i;
    }
    else {
        i = 36;
        return i;
    }
}


void inserirUserCatalogo(CATALOGO_USER cataU, char* id, char* name, char **friends, int nFriends){
    char* idUser = strdup(id);
    char* nameUser = strdup(name);
    int indice = calculaIndiceUser(id[0]);
    USER user = initUser(idUser, nameUser, friends, nFriends);
    avl_insert(cataU->avl_indice[indice], getUserId(user), user);
    cataU->totalUsers++;
    free(user);
}


char * cloneId(char *idU){
    int tamanho = strlen(idU);
    char* novoId;

    novoId = (char*) malloc(tamanho + 1);
    strncpy(novoId, idU, tamanho + 1);

    return novoId;
}

void freeId(char * idU){
    free(idU);
}


//Funcion que calcula el numero total de users en un catálogo.
int getTotalUsers(CATALOGO_USER catU){
    return catU->totalUsers;
}

//Função que dado um catalogo e um caracter, devolve o indice correspondente a esse caracte
int getAVLIndice(CATALOGO_USER a, char c){
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

//Função que dado um id de user valida se ele existe

int existeUser(CATALOGO_USER catU, USER a){
    int lInicial = getAVLIndice(catU, getUserId(a)[0]);
    if(avl_find(catU->avl_indice[lInicial], getUserId(a))==NULL)return EXIT_FAILURE;
    else return EXIT_SUCCESS;
}


//Função que dado um id devolve a informação de um User

USER getUser(CATALOGO_USER catU, char * id){

    int i = getAVLIndice(catU, id[0]);
    USER res = (USER) malloc(sizeof (USER));
    USER u = (USER) malloc(sizeof (USER));


    res = (USER) avl_find(catU->avl_indice[i], id);
    if (res != NULL) {
        //O USER EXISTE
        char * test = strdup(getUserName(res));
        u = setUserId(u, getUserId(res));
        u = setUserName(u, getUserName(res));
        u = setUserNumFriends(u, getUserNumFriends(res));
        u = setUserFriends(u, getUserFriends(res), getUserNumFriends(res));
        return u;
    } else {
        printf("O id indicado nao tem correspondencia!\nPor favor inserir id valido\n");
        return NULL;
    }

}
ARVORE getCatalogoUsersPorLetra(CATALOGO_USER cat_u, char l) {
    return cat_u->avl_indice[calculaIndiceUser(l)];
}

ARVORE getCatalogoUserPorIndice(CATALOGO_USER cat_u, int i) {
    return cat_u->avl_indice[i];
}


void freeCatalogoUsers(CATALOGO_USER cat_U){
    int i;

    if(cat_U != NULL){
        for (i = 0; i <= 36; i++) {
            avl_destroy(cat_U->avl_indice[i], freeId);
        }
    }
    free(cat_U);
}
