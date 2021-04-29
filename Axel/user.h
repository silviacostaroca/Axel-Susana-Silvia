#ifndef GRUPO66_USER_H
#define GRUPO66_USER_H

#define TAM_IDS 22 //Tamanho de um Id
#define N_FRIENDS 1000 //Nº de amigos

/** ---------------- Estruturas ---------------**/
typedef struct user * USER;

/** ---------------- Funçoẽs -------------------**/
USER initUser(char* id, char* name, char **friends, int nFriends);
USER initU();
char* getUserId(USER u);
char* getUserName(USER u);
int getUserNumFriends(USER u);
char** getUserFriends(USER u);

USER setUserId(USER u, char* id);
USER setUserName(USER u, char* nome);
USER setUserNumFriends(USER u, int nFriends);
USER setUserFriends(USER u, char** friends, int nFriends);


#endif //GRUPO66_USER_H
