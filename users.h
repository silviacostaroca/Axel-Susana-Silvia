//
// Created by Silvia Acosta on 17/04/2021.
//

#ifndef AXEL_USERS_H
#define AXEL_USERS_H

#define TAM_IDS 22 //Tamanho de um Id
#define N_FRIENDS 1000 //Nº de amigos

/** ---------------- Estruturas ---------------**/
typedef struct user * USER;

/** ---------------- Funçoẽs -------------------**/
USER initUser(char* id, char* name, char **friends, int nFriends);

char* getUserId(USER u);
char* getUserName(USER u);
int getUserNumFriends(USER u);
char** getUserFriends(USER u);

#endif //AXEL_USERS_H
