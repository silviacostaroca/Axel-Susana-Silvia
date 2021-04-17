#ifndef GRUPO66_CATALOGO_USERS_H
#define GRUPO66_CATALOGO_USERS_H

#include <stdbool.h>
#include "avl.h"
#include "user.h"

#define MAXFRIENDS 1000
#define TAM_IDS 22

/** ---------------- Estruturas ---------------**/
typedef struct catalogoUser *CATALOGO_USER;

/** ---------------- Funçẽs -------------------**/
int avlCompara(const void *avlA, const void *avlB, void *avlParam);
CATALOGO_USER initCatUser();
int calculaIndiceUser(char l);
void inserirUserCatalogo(CATALOGO_USER cataU, char* id, char* name, char **friends, int nFriends);
TABLE getAVLUser(CATALOGO_USER a,int x);
char * cloneId(char *idU);
void freeId(char * idU);
int existeUser(CATALOGO_USER catU, USER a);
int totalUsers(CATALOGO_USER catU);


#endif //GRUPO66_CATALOGO_USERS_H