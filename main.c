#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include <ctype.h>

#include "catalogo_reviews.h"
#include "catalogo_bussines.h"
#include "catalogo_users.h"
#include "leitura.h"
#include "menu.h"

/*Declarar estruturas*/

int main(){
    //int countUsers, countBussines, countReviews;
    printf("--------------------------------------\n");
    lerFicheiroUsers("Users.csv");
    printf("--------------------------------------\n");
    lerFicheiroBussines("bussines.csv");
    printf("--------------------------------------\n");
    lerFicheiroReviews("reviews.csv");
    printf("--------------------------------------\n");
    //printf("Linhas lidas users: %d\n", countUsers);
    //printf("Linhas lidas bussiness: %d\n", countBussines);
    //printf("Linhas lidas reviews: %d\n", countReviews);
    //menu();
    return 0;
}
