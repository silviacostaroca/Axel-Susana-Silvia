#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //functions that are useful for testing and mapping characteres
#include <time.h>

#include "leitura.h"
#include "catalogo_users.h"
#include "catalogo_bussines.h"
#include "catalogo_reviews.h"

//Este módulo vai tratar da leitura e carregamento em memória dos ficheiros



/** --------------------- Validações ------------------------------------**/
//a data vem no tipo: 2014-10-11 03:34:02
int isDate(char * token){
    char * parteData;
    char * data="";
    char * horas="";
    int args = 0;
    char * valH;
    int countH=0;
    char * valD;
    int countD=0;
    parteData = strtok(token, " ");
    while (parteData != NULL){
        if (args == 0)
            data = strdup(parteData);
        if (args == 1)
            horas = strdup(parteData);
        if(args >= 2)
            //se tiver mais argumentos do que data e hora
            return EXIT_FAILURE;
        args++;
        parteData = strtok(NULL, " ");
    }
    //valida se tem data e hora
    if(args < 2)
        return EXIT_FAILURE;

    //Valida a data - ano-mes-dia
    valD = strtok(data, "-");
    while(valD != NULL){
        if(countD==0){
            //ano
            if(atoi(valD)<=0 || atoi(valD) > ANOATUAL)
                return EXIT_FAILURE;
        }
        if (countD==1){
            //mes
            if(atoi(valD) < 1 || atoi(valD) > 12)
                return EXIT_FAILURE;
        }
        if(countD==2){
            //dia
            if(atoi(valD) <1  || atoi(valD) > 31)
                return EXIT_FAILURE;
        }
        countD++;
        valD = strtok(NULL, "-");
    }
    if(countD > 3)
        return EXIT_FAILURE;

    //Valida hora
    valH = strtok(horas, ":");
    while(valH != NULL){
        if(countH==0){
            //hora
            if(atoi(valH)<0 || atoi(valH) > 23)
                return EXIT_FAILURE;
        }
        if (countH==1){
            //minuto
            if(atoi(valH) <0  || atoi(valH) > 59)
                return EXIT_FAILURE;
        }
        if(countH==2){
            //segundos
            if(atoi(valH) < 0 || atoi(valH) > 59)
                return EXIT_FAILURE;
        }
        countH++;
        valH = strtok(NULL, ":");
    }
    if(countH > 3)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}


//Função que valida a linha lida do ficheiro Users.csv
//registos tem 3 campos e tamanho do id =22;
int validaUser (char * linha){
    char * token;
    int tokenReg= 0; //Para validar o nº de campos
    token = strtok(linha,";");
    while (token != NULL){
        if(tokenReg == 0){ //id tem tamanho 22
            if(strlen(token)!=22)
                return EXIT_FAILURE;
        }
        tokenReg ++;
        token = strtok(NULL, ";");
    }
    //só pode ter 3 argumentos
    if(tokenReg !=3 ){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


//Função que valida a linha lida do ficheiro bussines.csv
//registos tem 5 campos e tamanho do id =22;
int validaBussines (char * linha){
    char * token;
    int tokenReg= 0; //Para validar o nº de campos
    token = strtok(linha,";");
    while (token != NULL){
        if(tokenReg == 0){ //id tem tamanho 22
            if(strlen(token)!=22)
                return EXIT_FAILURE;
        }
        tokenReg ++;
        token = strtok(NULL, ";");
    }
    //só pode ter 5 argumentos
    if(tokenReg != 5){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

//Função que valida a linha lida do ficheiro reviews_1M.csv
//registos tem 9 campos, tamanho do id = 22, stars [0,5], usefu, funny , coll >=0 e date no formate certo
int validaReviews (char * linha){
    char * token;
    int tokenReg= 0; //Para validar o nº de campos
    token = strtok(linha,";");
    while (token != NULL){
        int cool, useful, funny;
        float stars;
        switch (tokenReg) {
            case 0: //id review
                if(strlen(token)!=22)
                    return EXIT_FAILURE;
                break;
            case 1: //id user
                if(strlen(token)!=22)
                    return EXIT_FAILURE;
                break;
            case 2: //id bussines
                if(strlen(token)!=22)
                    return EXIT_FAILURE;
                break;
            case 3: //stars
                stars = atof(token);
                if(stars< 0 || stars >= 6)
                    return EXIT_FAILURE;
                break;
            case 4: //useful
                useful = atoi(token);
                if(useful < 0)
                    return EXIT_FAILURE;
                break;
            case 5: //funny
                funny = atoi(token);
                if(funny < 0)
                    return EXIT_FAILURE;
                break;
            case 6: //cool
                cool = atoi(token);
                if(cool < 0)
                    return EXIT_FAILURE;
                break;
            case 7: //date
                if (isDate(token)==1)
                    return EXIT_FAILURE;
                break;
        }
        tokenReg ++;
        token = strtok(NULL, ";");
    }
    //só pode ter 9 argumentos
    if(tokenReg+1 != 9){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/** ----------------------- Colocar em estrutura ------------------------ **/
void fillCatalogoUsers (CATALOGO_USER catUsers, char * linha){
    char id[TAM_IDS+1], name[50];
    int tokenArg = 1; //identifica qual a variàvel que está a guarda
    int mem = MAXFRIENDS, i=0, j=0, k=0;
    char * token = strtok(linha, ";");
    char * friend;
    char **friendsUser = (char**)malloc(MAXFRIENDS*(TAM_IDS+1)*sizeof (char));
    for(j=0; j<MAXFRIENDS; j++){
        friendsUser[j]=(char*)malloc(TAM_IDS+1);
    }
    while (token != NULL) {
        /** ----- copia ID ---- **/
        if(tokenArg == 1){
            strcpy(id, token);
        }
        /** ----- copia NOME ---- **/
        if(tokenArg == 2){
            strcpy(name, token);
        }
        /** ----- copia FRIENDS ---- **/
        if(tokenArg == 3){
            friend = strtok(token, ",");
            i=0;
            while(friend != NULL){
                //ID do amigo valido?
                if(strlen(friend)==TAM_IDS){
                    //valida se e necessario fazer o realloc
                    if(i == mem-1){
                        mem = mem+MAXFRIENDS;
                        friendsUser = (char**)realloc(friendsUser, mem * (TAM_IDS+1)*sizeof(char));
                        for(k=i; k<mem; k++){
                            friendsUser[k]=(char* )malloc(sizeof(char)*TAM_IDS+1);
                        }
                        if(friendsUser == NULL){
                            printf("Memória insuficiente!\n");
                        }
                    }
                    strcpy(friendsUser[i],friend);
                    i++;
                }
                friend = strtok(NULL, ",");
            }
        }
        tokenArg ++;
        token = strtok(NULL, ";");
    }
    inserirUserCatalogo (catUsers, id, name, friendsUser, i);
  //  printf (" O id e o nome son %s\n", getUserName ((USER) avl_find(getAVLIndice(catUsers,id[0]),id)));
    //free(friendsUser);
}

void fillCatalogoBussines (CATALOGO_BUSSINES catB, char * linha) {
    char id[TAM_IDS + 1], name[TAM_NAME], city[TAM_NAME], state[TAM_NAME];
    int tokenArg = 1; //identifica qual a variàvel que está a guarda
    int mem = MAXCATEGORIAS, i = 0, j = 0, k = 0;
    char *token = strtok(linha, ";");
    char *categorias;
    char **bussCategorias = (char **) malloc(MAXCATEGORIAS * (TAM_NAME) * sizeof(char));
    for (j = 0; j < MAXCATEGORIAS; j++) {
        bussCategorias[j] = (char *) malloc(TAM_NAME);
    }
    while (token != NULL) {
        /* ----- copia ID ---- */
        if (tokenArg == 1) {
            strcpy(id, token);
        }
        /* ----- copia NOME ---- */
        if (tokenArg == 2) {
            strcpy(name, token);
        }
        /* ----- copia CITY ---- */
        if (tokenArg == 3) {
            strcpy(city, token);
        }
        /* ----- copia STATE ---- */
        if (tokenArg == 4) {
            strcpy(state, token);
        }
        /* ----- copia CATEGORIAS ---- */
        if (tokenArg == 5) {
            categorias = strtok(token, ",");
            i = 0;
            while (categorias != NULL) {
                //valida se e necessario fazer o realloc
                if (i == mem - 1) {
                    mem = mem + MAXCATEGORIAS;
                    bussCategorias = (char **) realloc(bussCategorias, mem * (TAM_NAME + 1) * sizeof(char));
                    for (k = i; k < mem; k++) {
                        bussCategorias[k] = (char *) malloc(sizeof(char) * TAM_NAME + 1);
                    }
                    if (bussCategorias == NULL) {
                        printf("Memória insuficiente!\n");
                    }
                }
                strcpy(bussCategorias[i], categorias);
                i++;
                categorias = strtok(NULL, ",");
            }
        }
        tokenArg++;
        token = strtok(NULL, ";");
    }
    inserirBussinesCatalogo(catB, id, name, city, state, bussCategorias, i);
}


void fillCatalogoReviews (CATALOGO_REVIEWS  catR, char * linha){
    char idR[TAM_IDS+1];
    char idU[TAM_IDS+1];
    char idB[TAM_IDS+1];
    char date[TAM_NAME];
    char text[MAXBUFBUSSINES];
    float stars;
    int useful, funny, cool;
    int tokenArg = 1; //identifica qual a variàvel que está a guarda
    char * token = strtok(linha, ";");
    while (token != NULL) {
        //----- copia ID REVIEW ----
        if(tokenArg == 1){
            strcpy(idR, token);
        }
        //----- copia ID USERS ----
        if(tokenArg == 2){
            strcpy(idU, token);
        }
        //----- copia ID BUSSINES ----
        if(tokenArg == 3){
            strcpy(idB, token);
        }
        //----- copia STARS ----
        if(tokenArg == 4){
            stars = atof(token);
        }
        //----- copia USEFUL ----
        if(tokenArg == 5){
            useful = atoi(token);
        }
        //----- copia FUNNY ----
        if(tokenArg == 6){
            funny = atoi(token);
        }
        // ----- copia COOL ----
        if(tokenArg == 7){
            cool = atoi(token);
        }
        //----- copia DATE----
        if(tokenArg == 8){
            strcpy(date, token);
        }
        //---- copia TEXT----
        if(tokenArg == 9){
            strcpy(text, token);
        }
        tokenArg ++;
        token = strtok(NULL, ";");
    }
    inserirReviewCatalogo(catR, idR, idB, idU, stars, useful, funny,cool, date, text);
}

/*--------------------------------- Ler ficheiros -------------------------------------------*/
//Lê o ficheiro users.csv
CATALOGO_USER lerFicheiroUsers(char * nomeFicheiro, CATALOGO_USER cat_users){
    int linhasLidas = 0;
    int linhasValidas = 0;
    char linha[MAXBUFUSERS];
    clock_t tempIni, tempFim;
    float tempoLeitura;
    char copia[MAXBUFUSERS];
    cat_users = initCatUser();
    FILE * fp = fopen(nomeFicheiro, "r");
    if(fp==NULL) {
        perror("Erro ao abrir o ficheiro");
        return EXIT_FAILURE;
    }
    //printf("Ficheiro: %s\n", nomeFicheiro);
    tempIni = clock();
    while(fgets(linha, MAXBUFUSERS, fp)){
        linhasLidas++;
        strcpy(copia, linha);
        if (validaUser(linha) == EXIT_SUCCESS){
            linhasValidas ++;
            fillCatalogoUsers(cat_users, copia);

        }
    }
    fclose(fp);
    tempFim = clock();
    tempoLeitura = (double) (tempFim-tempIni)/CLOCKS_PER_SEC;
    printf("===============USERS===============\n");
    printf("Total de Linhas Lidas: %d\n",linhasLidas-1);
    printf("Total de Linhas Válidas: %d\n", linhasValidas);
    printf("Tempo de Leitura: %.3f segundos\n", tempoLeitura);
    return cat_users;
}

//Lê o ficheiro bussines.csv
CATALOGO_BUSSINES lerFicheiroBussines(char * nomeFicheiro, CATALOGO_BUSSINES cat_bussines){
    char copylinha [MAXBUFUSERS];
    int linhasLidas = 0;
    int linhasValidas = 0;
    char linha[MAXBUFFER];
    clock_t tempIni, tempFim;
    float tempoLeitura;
    cat_bussines=initCatBussines();
    FILE * fp = fopen(nomeFicheiro, "r");
    if(fp==NULL) {
        perror("Erro ao abrir o ficheiro");
        return EXIT_FAILURE;
    }
    //printf("Ficheiro: %s\n", nomeFicheiro);
    tempIni = clock();

    while(fgets(linha, MAXBUFFER, fp)){
        linhasLidas++;
        strcpy(copylinha, linha);
        if (validaBussines(linha) == EXIT_SUCCESS){
            linhasValidas ++;
            fillCatalogoBussines(cat_bussines,copylinha);
        }
    }
    fclose(fp);
    tempFim = clock();
    tempoLeitura = (double) (tempFim-tempIni)/CLOCKS_PER_SEC;
    printf("===============BUSSINES===============\n");
    printf("Total de Linhas Lidas: %d\n",linhasLidas-1);
    printf("Total de Linhas Válidas: %d\n", linhasValidas-1);
    printf("Tempo de Leitura: %.3f segundos\n", tempoLeitura);
    return cat_bussines;
}

//Lê o ficheiro reviews.csv
CATALOGO_REVIEWS lerFicheiroReviews(char * nomeFicheiro, CATALOGO_REVIEWS cat_reviews){
    char copylinha [MAXBUFFER];
    int linhasLidas = 0;
    int linhasValidas = 0;
    char linha[MAXBUFFER];
    clock_t tempIni, tempFim;
    float tempoLeitura;
    cat_reviews = initCatReviews();
    FILE * fp = fopen(nomeFicheiro, "r");
    if(fp==NULL) {
        perror("Erro ao abrir o ficheiro");
        return EXIT_FAILURE;
    }
    //printf("Ficheiro: %s\n", nomeFicheiro);
    tempIni = clock();
    while(fgets(linha, MAXBUFFER, fp)){
        strcpy(copylinha, linha);
        linhasLidas++;
        if (validaReviews (linha) == EXIT_SUCCESS){
            linhasValidas ++;
            fillCatalogoReviews(cat_reviews,copylinha);
        }
    }
    fclose(fp);
    tempFim = clock();
    tempoLeitura = (double) (tempFim-tempIni)/CLOCKS_PER_SEC;
    printf("===============REVIEWS===============\n");
    printf("Total de Linhas Lidas: %d\n",linhasLidas-1);
    printf("Total de Linhas Válidas: %d\n", linhasValidas-1);
    printf("Tempo de Leitura: %.3f segundos\n", tempoLeitura);
    return cat_reviews;
}

