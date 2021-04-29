#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

USER initU() {
    int i=0;
    USER user = (USER) malloc(sizeof(struct user));
    user->idUser = (char *) malloc(TAM_IDS * sizeof(char));
    user->nameUser = (char *) malloc(200* sizeof(char));
    user->friendsUser = (char **) malloc(sizeof(char) * N_FRIENDS);
    for (i = 0; i < N_FRIENDS; i++) {
        user->friendsUser[i] = (char *)malloc(sizeof(char)*TAM_IDS);
    }
    return user;
}

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
    user->friendsUser= (char**)malloc(sizeof(char)*nFriends*TAM_IDS);
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
    int i;
    char**copyfriends=(char**) malloc(u->numFriends*(TAM_IDS+1)*sizeof (char));
    for(i=0; i<(u->numFriends);i++){
        copyfriends[i]=strcpy(copyfriends[i],u->friendsUser[i]);
    }
    printf("sai do ciclo\n");
    return copyfriends;
}


/** --------------- sets ------------------- **/
USER setUserId(USER u, char* id){
    char* idU = strdup(id);
    u->idUser = strdup(idU);
    return u;
}

USER setUserName(USER u, char* nome){
    char* name = strdup(nome);
    u->nameUser = strdup(name);
    return u;
}

USER setUserNumFriends(USER u, int nFriends){
    u->numFriends = nFriends;
    return u;
}

USER setUserFriends(USER u, char** friends, int nFriends){

    u->friendsUser=(char**) malloc((nFriends)*(TAM_IDS+1)*sizeof (char));
    if(u->friendsUser==NULL) printf("El malloc correu mal\n");
    int i = 0;
    for(i=0; i<nFriends;i++){
        printf("friends %d %s\n",i,friends[i]);
        (u->friendsUser[i])=strdup(friends[i]);
    }
    printf("sai friends %d %s\n",i,friends[i]);
    return u;
}
