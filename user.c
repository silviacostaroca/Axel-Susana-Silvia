#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#include "user.h"

/** ---------------- Estruturas de Dados ---------------**/
struct user{
    char* idUser;
    char* nameUser;
    char** friendsUser;
    int numFriends;
};

USER initUser(char* id, char* name, char **friends, int nFriends){
    int i=0;
    int tamanho = strlen(name)+1;
    int numAmigos = nFriends;
    USER user = (USER)malloc(sizeof(struct user));
    user->idUser= (char*)malloc(TAM_IDS*sizeof(char));
    user->nameUser = (char*)malloc(tamanho*sizeof(char));
    user->idUser = strdup(id);
    user->nameUser = strdup(name);
    user->numFriends = numAmigos;
    user->friendsUser= (char**)malloc(sizeof(char)*nFriends);
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



