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
    TABLE avl_indice[37]; //27 letras + 9 algarismos, porque os ids podem começar por letra, numero ou outro caracter
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
    } else {
        i = 36;
    }
    return i;
}


void inserirUserCatalogo(CATALOGO_USER cataU, char* id, char* name, char **friends, int nFriends){
    //primeiro cria USER
    char* idUser = strdup(id);
    char* nameUser = strdup(name);
    int indice = calculaIndiceUser(id[0]);
    for(int k=0; k<nFriends; k++){
    }
    USER user = initUser(idUser, nameUser, friends, nFriends);
    if(avl_insert(cataU->avl_indice[indice], getUserId(user), user)!= NULL)
        cataU->totalUsers++;
}

/** -------------------------- GETS -------------------------**/

//Funcion que calcula el numero total de users en un catálogo.
int getTotalUsers(CATALOGO_USER catU){
    return catU->totalUsers;
}

//Função que dado um catalogo e um caracter, devolve o indice correspondente a esse caracte
int getAVLIndice(CATALOGO_USER a, char c){
    int i = toupper(c)-A;
    return i;
}

//Função que dado um id de user valida se ele existe
int existeUser ()


//Função que dado um id devolve a informação de um User
USER getUser(CATALOGO_USER catU, char * id){
    int i = getAVLIndice(catU, id[0]);
    USER res = (USER)malloc(sizeof(struct user));
    USER u = (USER)malloc(sizeof(struct user));
    u->idUser= (char*)malloc(TAM_IDS*sizeof(char));
    u->nameUser = (char*)malloc(tamanho*sizeof(char));
    u->friendsUser= (char**)malloc(sizeof(char)*nFriends);
    res = (USER)avl_find(catU->avl_indice[i], id);
    if( res != NULL){
        //O USER EXISTE
        u= setUserId(u, getUserId(res));
        u= setUserName(u, getUserName(res));
        u= setUserNumFriends(u, getUserNumFriends(res));
        u= setUserFriends(u, getUserFriends(res), getUserNumFriends(res));
        return u;
    }
    else{
        printf("O id indicado nao tem correspondencia!\nPor favor inserir id valido\n");
        return EXIT_FAILURE
    }
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


// Función que verifica si un user ya existe.
//Retorna 0 caso no exista y 1 si existe.
int existeUser(CATALOGO_USER catU, USER a){
    int lInicial = getUserId(a)[0]-65;
    if(avl_find(catU->avl_indice[lInicial], getUserId(a))==NULL) return 0;
    else return 1;
}



