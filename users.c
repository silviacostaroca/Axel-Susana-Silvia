//
// Created by Silvia Acosta on 17/04/2021.
//

#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/** ---------------- Estruturas de Dados ---------------**/
struct user{
    char* idUser;
    char* nameUser;
    char** friendsUser;
    int numFriends;
};

USER initUser(char* id, char* name, char **friends, int nFriends){
    int tamanho = strlen(name)+1, i=0, j=0;
    //USER user = (USER)malloc((sizeof(char)*TAM_IDS+1)*
    //(sizeof(char)*tamanho)*(nFriends*sizeof (char*))*(nFriends+1)); //sizeof id * sizeof nome * sizeof friends[] * nº de amigos
    USER user = malloc(sizeof(struct user)*nFriends*sizeof(int ));
    user->idUser = (char*)malloc(sizeof(char)*TAM_IDS);
    user->nameUser = (char*)malloc(sizeof(char)*tamanho);
    //user->numFriends = malloc(sizeof(int));
    //printf("Id: %s\nNome: %s", user->idUser, user->nameUser);
    for(j=0; j<nFriends; j++){
        user->friendsUser[j] =(char* )malloc(sizeof(char)*TAM_IDS+1);
    }
    printf("passa aqui\n");
    user->idUser = strdup(id);
    user->nameUser = strdup(name);
    user->numFriends = nFriends;
    printf("Id: %s\n", user->idUser);
    for(i=0; i<nFriends;i++){
        user->friendsUser[i]=strdup(friends[i]);
    }
    return user;
}

/** -------------------- GETS -----------------------**/
char* getUserId(USER u){
    return u->idUser;
}

char* getUserName(USER u){
    return u->nameUser;
}

int getUserNumFriends(USER u){
    return u->numFriends;
}

char** getUserFriends(USER u){
    return u->friendsUser;
}



