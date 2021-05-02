

#include <stdbool.h>
#include "avl.h"
#include "user.h"


#define TAM_IDS 22
//#define MAXFRIENDS 1000

/* ---------------- Estruturas ---------------*/
typedef struct catalogoUser *CATALOGO_USER;

/* ---------------- Funçẽs -------------------*/
int avlCompara(const void *avlA, const void *avlB, void *avlParam);
CATALOGO_USER initCatUser();
int calculaIndiceUser(char l);
void inserirUserCatalogo(CATALOGO_USER cataU, char* id, char* name, char **friends, int nFriends);
char * cloneId(char *idU);
void freeId(char * idU);


int getTotalUsers(CATALOGO_USER catU);
int getAVLIndice(CATALOGO_USER a, char c);
int existeUser(CATALOGO_USER catU, USER a);
USER getUser(CATALOGO_USER catU, char * id);
ARVORE getCatalogoUsersPorLetra(CATALOGO_USER cat_u, char l);
ARVORE getCatalogoUserPorIndice(CATALOGO_USER cat_u, int i);
//void freeCatalogoUsers(CATALOGO_USER cat_U);

