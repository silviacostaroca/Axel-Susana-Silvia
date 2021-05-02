#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "SGR.h"
#include "catalogo_users.h"
#include "catalogo_bussines.h"
#include "catalogo_reviews.h"
#include "paginacao.h"
#include "leitura.h"
#include "time.h"


/**---------------- Estruturas de Dados ---------------**/
struct sgr{
    CATALOGO_USER cat_u;
    CATALOGO_BUSSINES cat_b;
    CATALOGO_REVIEWS cat_r;
};

struct arrayVoid{
    float valor;
};

//variável Global
SGR estruturaSGR;

//Inicializar a struct SGR
SGR init_SGR(){
    SGR iniSGR = (SGR)malloc(sizeof(struct sgr));
    iniSGR->cat_u = (CATALOGO_USER)malloc(sizeof(CATALOGO_USER));
    iniSGR->cat_b = (CATALOGO_BUSSINES)malloc(sizeof(CATALOGO_BUSSINES));
    iniSGR->cat_r = (CATALOGO_REVIEWS)malloc(sizeof(CATALOGO_REVIEWS));
    return iniSGR;
}

void free_sgr(SGR sgr){
    if(sgr != NULL){
        if(sgr->cat_r != NULL)
            free(sgr->cat_r);
        if(sgr->cat_b != NULL)
            free(sgr->cat_b );
        if(sgr->cat_u != NULL)
            free(sgr->cat_u);
        free(sgr);
    }
}

/**-----------------------------------------------------QUERIES------------------------------------------------------------**/
/**query 1. Dado o caminho para os 3 ficheiros (Users, Businesses, e Reviews), ler o seu conteúdo e carregar as
            struturas de dados correspondentes.**/
int query1() {
    // estruturaSGR = init_SGR();
    char tFicheiro;
    char nomeFicheiro[MAXBUFFER];
    int totalFcheirosLidos = 0;
    printf("**********************Query 1********************\n");
    printf("Indique o ficheiro a ler U-users B-bussines R-reviews T-todos\n");
    if (scanf(" %c", &tFicheiro) > 0)printf("Escolheu o tipo de ficheiro : %c\n", tFicheiro);
    tFicheiro = toupper(tFicheiro);
    switch (tFicheiro) {
        case 'U':
            printf("Indique o nome do ficheiro a abrir: \n");
            if (scanf("%s", nomeFicheiro) > 0) {
                printf("Escolheu o ficheiro de nome : %s\n", nomeFicheiro);
                estruturaSGR->cat_u = load_sgr("users.csv", NULL, NULL)->cat_u;
                totalFcheirosLidos++;
            } else {
                printf("\nFicheiro inexistente\n");
            }
            break;
        case 'B':
            printf("Indique o nome do ficheiro a abrir: \n");
            if (scanf("%s", nomeFicheiro) > 0) {
                printf("Escolheu o ficheiro de nome : %s\n", nomeFicheiro);
                estruturaSGR->cat_b = load_sgr(NULL, "bussines.csv", NULL)->cat_b;
                totalFcheirosLidos++;
            } else {
                printf("\nFicheiro inexistente\n");
            }
            break;
        case 'R':
            printf("Indique o nome do ficheiro a abrir: \n");
            if (scanf(" %s", nomeFicheiro) > 0) {
                printf("Escolheu o ficheiro de nome : %s\n", nomeFicheiro);
                estruturaSGR->cat_r = load_sgr(NULL, NULL, "reviews.csv")->cat_r;
                totalFcheirosLidos++;
            } else {
                printf("\nFicheiro inexistente\n");
            }
            break;
        case 'T':
            free_sgr(estruturaSGR);
            estruturaSGR = init_SGR();
            estruturaSGR = load_sgr("users.csv", "bussines.csv", "reviews.csv");
            estruturaSGR->cat_b = estruturaConStars(estruturaSGR->cat_r, estruturaSGR->cat_b);
            break;
        default: {
            printf("Tipo de ficheiro inválido");
            printf("\nIndique o tipo de ficheiro que deseja abrir (U-users B-bussines R-reviews): \n");
            if (scanf(" %c", &tFicheiro) > 0)printf("Escolheuo tipo : %c\n", tFicheiro);
        }
    }
    //if (totalFcheirosLidos == 3) {
    //    estruturaSGR->cat_b = estruturaConStars(estruturaSGR->cat_r, estruturaSGR->cat_b);
    //}
    return EXIT_SUCCESS;
}

SGR load_sgr(char *users, char *businesses, char *reviews) {
    if (users!=NULL && businesses==NULL && reviews==NULL)
        estruturaSGR->cat_u = lerFicheiroUsers("users.csv", estruturaSGR->cat_u);
    if (users==NULL && businesses!=NULL && reviews==NULL)
        estruturaSGR->cat_b = lerFicheiroBussines("bussines.csv", estruturaSGR->cat_b);
    if (users==NULL && businesses==NULL && reviews!=NULL)
        estruturaSGR->cat_r = lerFicheiroReviews("reviews.csv", estruturaSGR->cat_r);
    if (users!=NULL && businesses!=NULL && reviews!=NULL){
        estruturaSGR->cat_u = lerFicheiroUsers("users.csv", estruturaSGR->cat_u);
        estruturaSGR->cat_b = lerFicheiroBussines("bussines.csv", estruturaSGR->cat_b);
        estruturaSGR->cat_r = lerFicheiroReviews("reviews.csv", estruturaSGR->cat_r);
    }
    return estruturaSGR;
}


/** Query 2. Determinar a lista de nomes de negócios e o número total de negócios
        cujo nome inicia por uma dada letra. Note que a procura não deverá ser case sensitive.**/

int query2(){
    char letra;
    TABLE resultados;
    printf("**********************Query 2********************\n");
    printf("Indique a letra que quer listar:\n");
    if(scanf(" %c",&letra)>0)
        //enquanto não for inserida uma letra válida
        while(!isalpha(letra)){
            printf("Não foi inserida uma letra\n\n");
            printf("**********************Query 2********************\n");
            printf("Indique a letra que quer listar:\n");
            if(scanf(" %c",&letra)>0);
        }
    printf("Vão ser listados todos os negócios cujo nome inicia por: %c\n",letra);
    letra= toupper(letra);
    resultados = businesses_started_by_letter(estruturaSGR,letra);
    return EXIT_SUCCESS;
}

TABLE businesses_started_by_letter(SGR sgr, char letter){
    int nrResultados = 0;
    char letra = letter;
    char * nome = (char*)malloc(sizeof(char)*TAM_NAME);
    char* id = (char*)malloc(sizeof(char)*TAM_IDS);
    BUSSINES buss;
    clock_t tempIni, tempFim;
    TABLE resultados;
    tempIni = clock();
    resultados = travessiaBussinesPorLetra (sgr->cat_b, letra);
    tempFim = clock();
    int opt;
    int flag = 0;
    nrResultados = getTamanhoLista(resultados);
    setElementosPorPagina(resultados, ELEMS_PAG);
    posInit(resultados);

    if(nrResultados == 0){
        printf("Não foram encontrados resultados para essa letra\n");

    }
    else{
        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
        printf("* ID NEGÓCIO || NOME *\n\n");

        buss = (BUSSINES) getElementoAtual(resultados);
        if(buss != NULL){
            nome = getBussinesName(buss);
            id = getBussinesId(buss);
        }
        while (buss != NULL){
            printf("* ID: %s || Nome: %s  *\n", id, nome);
            buss = (BUSSINES) getElementoAtual(resultados);
            if(buss != NULL){
                nome = getBussinesName(buss);
                id = getBussinesId(buss);
            }
        }
        if(getIndiceAtual(resultados) > getNrElemPag(resultados)){
            while(flag == 0){
                printf("\n* < 1 (Página Anterior) || 0 - Sair || (Página seguinte) 2 >*\n");
                if(scanf("%d", &opt)>0);
                switch (opt) {
                    case 1:
                        if(getNrPagAtual(resultados) == 0){
                            printf("Não há páginas anteriores a mostrar.\n");
                            break;
                        }
                        paginaParaTras(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        printf("* ID NEGÓCIO || NOME *\n\n");

                        buss = (BUSSINES) getElementoAtual(resultados);
                        if(buss != NULL){
                            nome = getBussinesName(buss);
                            id = getBussinesId(buss);
                        }
                        while (buss != NULL){
                            printf("* ID: %s || Nome: %s  *\n", id, nome);
                            buss = (BUSSINES) getElementoAtual(resultados);
                            if(buss != NULL){
                                nome = getBussinesName(buss);
                                id = getBussinesId(buss);
                            }
                        }
                        break;
                    case 2:
                        paginaParaFrente(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        printf("* ID NEGÓCIO || NOME *\n\n");

                        buss = (BUSSINES) getElementoAtual(resultados);
                        if(buss != NULL){
                            nome = getBussinesName(buss);
                            id = getBussinesId(buss);
                        }
                        while (buss != NULL){
                            printf("* ID: %s || Nome: %s  *\n", id, nome);
                            buss = (BUSSINES) getElementoAtual(resultados);
                            if(buss != NULL){
                                nome = getBussinesName(buss);
                                id = getBussinesId(buss);
                            }
                        }
                        break;
                    case 0:
                        flag = 1;
                        break;
                    default: break;
                }
            }
        }
    }
    return resultados;
}

/**
Query 3. Dado um id de negócio, determinar a sua informação: nome, cidade, estado, stars,
e número total reviews. **/

int query3(){
    char* idB = (char*)malloc(sizeof(char)*TAM_IDS);
    printf("**********************Query 3********************\n");
    printf("Indique o id de um negocio\n");
    if(scanf("%s",idB)>0)
        business_info(estruturaSGR, idB);
    return EXIT_SUCCESS;
}


TABLE business_info(SGR sgr, char* business_id){
    int nrResultados = 0;
    int opt, i,j=0;
    int flag = 0;
    BUSSINES buss;
    VALOR aux = (VALOR)malloc(sizeof(VALOR));
    clock_t tempIni, tempFim;
    TABLE resultados;
    tempIni = clock();
    buss = getBussines(estruturaSGR->cat_b, business_id);
    tempFim = clock();
    if(buss == NULL){
        printf("Não existe nenhum negócio com esse id.\n");
        return NULL;
    }
    float* starsArray = (float*)malloc(sizeof(float)* getBussinesTotalstars(buss));
    starsArray = getBussinesStars(buss);
    if(buss != NULL){

        printf("*************************************************\n");
        printf("* NOME: %s *\n", getBussinesName(buss));
        printf("* CIDADE: %s *\n", getBussinesCity(buss));
        printf("* ESTADO: %s *\n", getBussinesName(buss));
        printf("* TOTAL DE REVIEWS: %d *\n", getBussinesTotalstars(buss));
        printf("* STARS: *\n");
    }
    for(int i=0; i< getBussinesTotalstars(buss); i++){
        printf("> %.1f\n",starsArray[i]);
    }
    return resultados;
}
/**
    starsArray = getBussinesStars(buss);
    resultados = (TABLE) initPagResulatos(getBussinesTotalstars(buss), 1);
    for(i=0; i<getBussinesTotalstars(buss); i++){
        aux->valor = starsArray[i];
        inserirDadosPagina(resultados, aux);
    }

    nrResultados = getTamanhoLista(resultados);
    setElementosPorPagina(resultados, ELEMS_PAG);
    posInit(resultados);
    tempFim = clock();
    if(nrResultados == 0){
       printf("Não foram encontrados resultados para essa letra\n");
    }
    else{
    printf("* Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
            printf("* STARS: *\n");
            aux = (VALOR) getElementoAtual(resultados);
            while (aux != NULL){
                printf("* > %.1f  *\n", aux->valor);
                aux = (VALOR) getElementoAtual(resultados);
            }
            if(getIndiceAtual(resultados) > getNrElemPag(resultados)){
                while(flag == 0){
                    printf("\n* < 1 (Página Anterior) || 0 - Sair || (Página seguinte) 2 >*\n");
                    if(scanf("%d", &opt)>0);
                    switch (opt) {
                        case 1:
                            if(getNrPagAtual(resultados) == 0){
                                printf("Não há páginas anteriores a mostrar.\n");
                                break;
                            }
                            paginaParaTras(resultados);
                            printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                            printf("* STARS: *\n");
                            aux = (VALOR) getElementoAtual(resultados);
                            while (aux != NULL){
                                printf("* > %.1f  *\n", aux->valor);
                                aux = (VALOR) getElementoAtual(resultados);
                            }
                            break;
                        case 2:
                            paginaParaFrente(resultados);
                            printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                            printf("* STARS: *\n");
                            aux = (VALOR) getElementoAtual(resultados);
                            while (aux != NULL){
                                printf("* > %.1f  *\n", aux->valor);
                                aux = (VALOR) getElementoAtual(resultados);
                            }
                            break;
                        case 0:
                            flag = 1;
                            break;
                        default: break;
                    }
                }
            }
        }
    return resultados;
}
**/

/**
Query 4. Dado um id de utilizador, determinar a lista de negócios aos quais fez review.
        A informação associada a cada negócio deve ser o id e o nome.
**/

int query4(){
    char* idU = (char*)malloc(sizeof(char)*TAM_IDS);
    printf("**********************Query 4********************\n");
    printf("Indique o id de utilizador\n");
    if(scanf("%s",idU)>0)
        businesses_reviewed(estruturaSGR, idU);
    return EXIT_SUCCESS;
}

TABLE businesses_reviewed(SGR sgr, char *user_id){
    int nrResultados = 0;
    char * nome = (char*)malloc(sizeof(char)*TAM_NAME);
    char* id = (char*)malloc(sizeof(char)*TAM_IDS);
    BUSSINES buss;
    clock_t tempIni, tempFim;
    TABLE resultados;
    tempIni = clock();
    resultados = travessiaReviewPorIdU(sgr->cat_r, sgr->cat_b, user_id);
    tempFim = clock();
    int opt;
    int flag = 0;
    nrResultados = getTamanhoLista(resultados);
    setElementosPorPagina(resultados, ELEMS_PAG);
    posInit(resultados);

    if(nrResultados == 0){
        printf("Não foram encontrados resultados para esse Id\n");

    }
    else{
        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), (long)nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
        printf("* ID NEGÓCIO || NOME *\n\n");

        buss = (BUSSINES) getElementoAtual(resultados);
        if(buss != NULL){
            nome = getBussinesName(buss);
            id = getBussinesId(buss);
        }
        while (buss != NULL){
            printf("* ID: %s || Nome: %s  *\n", id, nome);
            buss = (BUSSINES) getElementoAtual(resultados);
            if(buss != NULL){
                nome = getBussinesName(buss);
                id = getBussinesId(buss);
            }
        }
        if(getIndiceAtual(resultados) > getNrElemPag(resultados)){
            while(flag == 0){
                printf("\n* < 1 (Página Anterior) || 0 - Sair || (Página seguinte) 2 >*\n");
                if(scanf("%d", &opt)>0);
                switch (opt) {
                    case 1:
                        if(getNrPagAtual(resultados) == 0){
                            printf("Não há páginas anteriores a mostrar.\n");
                            break;
                        }
                        paginaParaTras(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        printf("* ID NEGÓCIO || NOME *\n\n");

                        buss = (BUSSINES) getElementoAtual(resultados);
                        if(buss != NULL){
                            nome = getBussinesName(buss);
                            id = getBussinesId(buss);
                        }
                        while (buss != NULL){
                            printf("* ID: %s || Nome: %s  *\n", id, nome);
                            buss = (BUSSINES) getElementoAtual(resultados);
                            if(buss != NULL){
                                nome = getBussinesName(buss);
                                id = getBussinesId(buss);
                            }
                        }
                        break;
                    case 2:
                        paginaParaFrente(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        printf("* ID NEGÓCIO || NOME *\n\n");

                        buss = (BUSSINES) getElementoAtual(resultados);
                        if(buss != NULL){
                            nome = getBussinesName(buss);
                            id = getBussinesId(buss);
                        }
                        while (buss != NULL){
                            printf("* ID: %s || Nome: %s  *\n", id, nome);
                            buss = (BUSSINES) getElementoAtual(resultados);
                            if(buss != NULL){
                                nome = getBussinesName(buss);
                                id = getBussinesId(buss);
                            }
                        }
                        break;
                    case 0:
                        flag = 1;
                        break;
                    default: break;
                }
            }
        }
    }
    return resultados;
}


/**
Query 5. Dado um número n de stars e uma cidade, determinar a lista de negócios com n ou mais stars na dada cidade.
        A informação associada a cada negócio deve ser o seu id e nome.
**/

char* strUpper(char* str){
    char* str2 = (char*)malloc(sizeof (char)*TAM_NAME);
    int i=0;
    for(i=0; i<strlen(str); i++){
        str2[i]=toupper(str[i]);
    }
    return str2;
}


int query5(){
    char* cidade = (char*)malloc(sizeof(char)*50);
    float estrela;
    printf("**********************Query 5********************\n");
    printf("Indique o numero de estrelas\n");
    if(scanf("%f",&estrela)>0);
    printf("Indique a cidade\n");
    if(scanf("%s",cidade)>0);
    printf("Vão ser listados todos os negócios da cidade de %s com %.1f ou mais estrelas\n",cidade, estrela);
    businesses_with_stars_and_city(estruturaSGR, estrela, strUpper(cidade));
    return EXIT_SUCCESS;
}

TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city){
    int nrResultados = 0;
    char * nome = (char*)malloc(sizeof(char)*TAM_NAME);
    char* id = (char*)malloc(sizeof(char)*TAM_IDS);
    BUSSINES buss;
    clock_t tempIni, tempFim;
    TABLE resultados;
    tempIni = clock();
    resultados = travessiaBussinesPorCidadeEstrela (sgr->cat_b, city, stars);
    tempFim = clock();
    int opt;
    int flag = 0;
    nrResultados = getTamanhoLista(resultados);
    setElementosPorPagina(resultados, ELEMS_PAG);
    posInit(resultados);

    if(nrResultados == 0){
        printf("Não foram encontrados negócios com %.1f mais estrelas para a cidade %s\n", stars, city);

    }
    else{
        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
        printf("* ID NEGÓCIO || NOME *\n\n");

        buss = (BUSSINES) getElementoAtual(resultados);
        if(buss != NULL){
            nome = getBussinesName(buss);
            id = getBussinesId(buss);
        }
        while (buss != NULL){
            printf("* ID: %s || Nome: %s  *\n", id, nome);
            buss = (BUSSINES) getElementoAtual(resultados);
            if(buss != NULL){
                nome = getBussinesName(buss);
                id = getBussinesId(buss);
            }
        }
        if(getIndiceAtual(resultados) > getNrElemPag(resultados)){
            while(flag == 0){
                printf("\n* < 1 (Página Anterior) || 0 - Sair || (Página seguinte) 2 >*\n");
                if(scanf("%d", &opt)>0);
                switch (opt) {
                    case 1:
                        if(getNrPagAtual(resultados) == 0){
                            printf("Não há páginas anteriores a mostrar.\n");
                            break;
                        }
                        paginaParaTras(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        printf("* ID NEGÓCIO || NOME *\n\n");

                        buss = (BUSSINES) getElementoAtual(resultados);
                        if(buss != NULL){
                            nome = getBussinesName(buss);
                            id = getBussinesId(buss);
                        }
                        while (buss != NULL){
                            printf("* ID: %s || Nome: %s  *\n", id, nome);
                            buss = (BUSSINES) getElementoAtual(resultados);
                            if(buss != NULL){
                                nome = getBussinesName(buss);
                                id = getBussinesId(buss);
                            }
                        }
                        break;
                    case 2:
                        paginaParaFrente(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        printf("* ID NEGÓCIO || NOME *\n\n");

                        buss = (BUSSINES) getElementoAtual(resultados);
                        if(buss != NULL){
                            nome = getBussinesName(buss);
                            id = getBussinesId(buss);
                        }
                        while (buss != NULL){
                            printf("* ID: %s || Nome: %s  *\n", id, nome);
                            buss = (BUSSINES) getElementoAtual(resultados);
                            if(buss != NULL){
                                nome = getBussinesName(buss);
                                id = getBussinesId(buss);
                            }
                        }
                        break;
                    case 0:
                        flag = 1;
                        break;
                    default: break;
                }
            }
        }
    }
    return resultados;
}


/**
Query 6. Dado um número inteiro n, determinar a lista dos top n negócios
        (tendo em conta o número médio de stars) em cada cidade. A informação
        associada a cada negócio deve ser o seu id, nome, e número de estrelas.

int query6(){
    int n;
    TABLE resultados;
    printf("**********************Query 6********************\n");
    printf("Indique um número:\n");
    if(scanf(" %d",&n)>0)
    printf("Vão ser listados os top %d negocios por cidade\n",n);
    top_businesses_by_city(estruturaSGR, n);
    return EXIT_SUCCESS;
}


TABLE top_businesses_by_city(SGR sgr, int top){
    int nrResultados = 0;
    char * nome = (char*)malloc(sizeof(char)*TAM_NAME);
    char* id = (char*)malloc(sizeof(char)*TAM_IDS);
    char* city = (char*)malloc(sizeof(char)*TAM_NAME);
    int totalStars = 0;
    QUERY6 buss;
    clock_t tempIni, tempFim;
    TABLE resultados;
    tempIni = clock();
    resultados = travessiaTopNegociosPorCidade(sgr->cat_b, top);
    tempFim = clock();
    int opt;
    int flag = 0;
    nrResultados = getTamanhoLista(resultados);
    setElementosPorPagina(resultados, ELEMS_PAG);
    posInit(resultados);

    if(nrResultados == 0){
        printf("Não foram encontrados resultados para essa letra\n");

    }
    else{
        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);

        buss = (QUERY6) getElementoAtual(resultados);
        if(buss != NULL){
            city = getQUERY6City(buss);
            nome = getBussinesName(getQUERY6Buss(buss));
            id = getBussinesId(getQUERY6Buss(buss));
            totalStars = getBussinesTotalstars(getQUERY6Buss(buss));
        }
        while (buss != NULL){
            printf("* Cidade: %s  *\n", city);
            printf("* ID: %s || Nome: %s  || Total Estrelas: %d *\n", id, nome, totalStars);
            buss = (BUSSINES) getElementoAtual(resultados);
            if(buss != NULL){
                city = getQUERY6City(buss);
                nome = getBussinesName(getQUERY6Buss(buss));
                id = getBussinesId(getQUERY6Buss(buss));
                totalStars = getBussinesTotalstars(getQUERY6Buss(buss));
            }
        }
        if(getIndiceAtual(resultados) > getNrElemPag(resultados)){
            while(flag == 0){
                printf("\n* < 1 (Página Anterior) || 0 - Sair || (Página seguinte) 2 >*\n");
                if(scanf("%d", &opt)>0);
                switch (opt) {
                    case 1:
                        if(getNrPagAtual(resultados) == 0){
                            printf("Não há páginas anteriores a mostrar.\n");
                            break;
                        }
                        paginaParaTras(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        buss = (QUERY6) getElementoAtual(resultados);
                        if(buss != NULL){
                            city = getQUERY6City(buss);
                            nome = getBussinesName(getQUERY6Buss(buss));
                            id = getBussinesId(getQUERY6Buss(buss));
                            totalStars = getBussinesTotalstars(getQUERY6Buss(buss));
                        }
                        while (buss != NULL){
                            printf("* Cidade: %s  *\n", city);
                            printf("* ID: %s || Nome: %s  || Total Estrelas: %d *\n", id, nome, totalStars);
                            buss = (BUSSINES) getElementoAtual(resultados);
                            if(buss != NULL){
                                city = getQUERY6City(buss);
                                nome = getBussinesName(getQUERY6Buss(buss));
                                id = getBussinesId(getQUERY6Buss(buss));
                                totalStars = getBussinesTotalstars(getQUERY6Buss(buss));
                            }
                        }
                        break;
                    case 2:
                        paginaParaFrente(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        buss = (QUERY6) getElementoAtual(resultados);
                        if(buss != NULL){
                            city = getQUERY6City(buss);
                            nome = getBussinesName(getQUERY6Buss(buss));
                            id = getBussinesId(getQUERY6Buss(buss));
                            totalStars = getBussinesTotalstars(getQUERY6Buss(buss));
                        }
                        while (buss != NULL){
                            printf("* Cidade: %s  *\n", city);
                            printf("* ID: %s || Nome: %s  || Total Estrelas: %d *\n", id, nome, totalStars);
                            buss = (BUSSINES) getElementoAtual(resultados);
                            if(buss != NULL){
                                city = getQUERY6City(buss);
                                nome = getBussinesName(getQUERY6Buss(buss));
                                id = getBussinesId(getQUERY6Buss(buss));
                                totalStars = getBussinesTotalstars(getQUERY6Buss(buss));
                            }
                        }
                        break;
                    case 0:
                        flag = 1;
                        break;
                    default: break;
                }
            }
        }
    }
    return resultados;
}

**/
/**
Query 7. Determinar a lista de ids de utilizadores e o número total de utilizadores que tenham visitado
        mais de um estado, i.e. que tenham feito reviews em negócios de diferentes estados.
**/
int query7(){
    printf("**********************Query 7********************\n");
    printf("Vão ser listados todos os utilizadores que visitaram mais do que um estado\n");
    international_users(estruturaSGR);
    return EXIT_SUCCESS;
}

TABLE international_users(SGR sgr){
    int nrResultados = 0;
    char* id = (char*)malloc(sizeof(char)*TAM_IDS);
    QUERY7 res;
    clock_t tempIni, tempFim;
    TABLE resultados;
    tempIni = clock();
    resultados = travessiaRevUsersEstados(sgr->cat_r, sgr->cat_b);
    tempFim = clock();
    int opt;
    int flag = 0;
    nrResultados = getTamanhoLista(resultados);
    setElementosPorPagina(resultados, ELEMS_PAG);
    posInit(resultados);

    if(nrResultados == 0){
        printf("Não foram encontrados utilizadores que visitaram mais do que um estado\n");

    }
    else{
        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", (long)getNrPagAtual(resultados)+1, (long)getNrPagTotal(resultados), (long)nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
        printf("* ID UTILIZADOR *\n\n");

        res = (QUERY7) getElementoAtual(resultados);
        if(res != NULL){
            id = getIdU(res);
        }
        while (res != NULL){
            printf("* ID: %s *\n", id);
            res = (QUERY7) getElementoAtual(resultados);
            if(res != NULL){
                id = getIdU(res);
            }
        }
        if(getIndiceAtual(resultados) > getNrElemPag(resultados)){
            while(flag == 0){
                printf("\n* < 1 (Página Anterior) || 0 - Sair || (Página seguinte) 2 >*\n");
                if(scanf("%d", &opt)>0);
                switch (opt) {
                    case 1:
                        if(getNrPagAtual(resultados) == 0){
                            printf("Não há páginas anteriores a mostrar.\n");
                            break;
                        }
                        paginaParaTras(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        printf("* ID UTILIZADOR *\n\n");

                        res = (QUERY7) getElementoAtual(resultados);
                        if(res != NULL){
                            id = getIdU(res);
                        }
                        while (res != NULL){
                            printf("* ID: %s *\n", id);
                            res = (QUERY7) getElementoAtual(resultados);
                            if(res != NULL){
                                id = getIdU(res);
                            }
                        }
                        break;
                    case 2:
                        paginaParaFrente(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        printf("* ID UTILIZADOR*\n\n");

                        res = (QUERY7) getElementoAtual(resultados);
                        if(res != NULL){
                            id = getIdU(res);
                        }
                        while (res != NULL){
                            printf("* ID: %s *\n", id);
                            res = (QUERY7) getElementoAtual(resultados);
                            if(res != NULL){
                                id = getIdU(res);
                            }
                        }
                        break;
                    case 0:
                        flag = 1;
                        break;
                    default: break;
                }
            }
        }
    }
    return resultados;
}

/**
Query 8. Dado um número inteiro n e uma categoria, determinar a lista dos top n negócios
        (tendo em conta o número médio de stars) que pertencem a uma determinada categoria.
        A informação associada a cada negócio deve ser o seu id, nome, e número de estrelas.
**/

int query8(){
    int n;
    char* categoria = (char*)malloc(sizeof(char)*TAM_CATEG);
    printf("**********************Query 8********************\n");
    printf("Indique o número do top\n");
    if(scanf("%d",&n)>0);
    printf("Indique a categoria\n");
    if(scanf("%s",categoria)>0);
    printf("Vão ser listados os top %d negócios da categoria %s\n",n, categoria);
    top_businesses_with_category(estruturaSGR, n, categoria);
    return EXIT_SUCCESS;
}

TABLE top_businesses_with_category(SGR sgr, int top, char *category){
    int nrResultados = 0;
    char* id = (char*)malloc(sizeof(char)*TAM_IDS);
    char* nome = (char*)malloc(sizeof(char)*TAM_NAME);
    int totalS;
    QUERY8 res;
    BUSSINES buss;
    clock_t tempIni, tempFim;
    TABLE resultados;
    tempIni = clock();
    resultados = travessiaBussinesPorCategoria(sgr->cat_b, top, category);
    tempFim = clock();
    int opt;
    int flag = 0;
    nrResultados = getTamanhoLista(resultados);
    setElementosPorPagina(resultados, ELEMS_PAG);
    posInit(resultados);

    if(nrResultados == 0){
        printf("Não foram encontrados negócios com a categoria indicada\n");

    }
    else{
        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", (long)getNrPagAtual(resultados)+1, (long)getNrPagTotal(resultados), (long)nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
        printf("* ID NEGÓCIO || NOME || TOTAL DE ESTRELAS *\n\n");

        res = (QUERY8) getElementoAtual(resultados);
        if(res != NULL){
            buss = getBussinesQuery8(res);
            if(buss != NULL){
                id = getBussinesId(buss);
                nome = getBussinesName(buss);
                totalS = getBussinesTotalstars(buss);
            }
        }
        while (res != NULL){
            printf("* ID: %s || NOME: %s || Total Estrelas: %d *\n", id, nome, totalS);
            res = (QUERY8) getElementoAtual(resultados);
            if(res != NULL){
                id = getBussinesId(buss);
                nome = getBussinesName(buss);
                totalS = getBussinesTotalstars(buss);
            }
        }
        if(getIndiceAtual(resultados) > getNrElemPag(resultados)){
            while(flag == 0){
                printf("\n* < 1 (Página Anterior) || 0 - Sair || (Página seguinte) 2 >*\n");
                if(scanf("%d", &opt)>0);
                switch (opt) {
                    case 1:
                        if(getNrPagAtual(resultados) == 0){
                            printf("Não há páginas anteriores a mostrar.\n");
                            break;
                        }
                        paginaParaTras(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        printf("* ID NEGÓCIO || NOME || TOTAL DE ESTRELAS *\n\n");

                        res = (QUERY8) getElementoAtual(resultados);
                        if(res != NULL){
                            buss = getBussinesQuery8(res);
                            if(buss != NULL){
                                id = getBussinesId(buss);
                                nome = getBussinesName(buss);
                                totalS = getBussinesTotalstars(buss);
                            }
                        }
                        while (res != NULL){
                            printf("* ID: %s || NOME: %s || Total Estrelas: %d *\n", id, nome, totalS);
                            res = (QUERY8) getElementoAtual(resultados);
                            if(res != NULL){
                                id = getBussinesId(buss);
                                nome = getBussinesName(buss);
                                totalS = getBussinesTotalstars(buss);
                            }
                        }
                        break;
                    case 2:
                        paginaParaFrente(resultados);
                        printf("Pagina: %ld de %ld || Total de resultados: %ld  em %.3f segundos\n", getNrPagAtual(resultados)+1, getNrPagTotal(resultados), nrResultados, (double) (tempFim-tempIni)/CLOCKS_PER_SEC);
                        printf("* ID NEGÓCIO || NOME || TOTAL DE ESTRELAS *\n\n");

                        res = (QUERY8) getElementoAtual(resultados);
                        if(res != NULL){
                            buss = getBussinesQuery8(res);
                            if(buss != NULL){
                                id = getBussinesId(buss);
                                nome = getBussinesName(buss);
                                totalS = getBussinesTotalstars(buss);
                            }
                        }
                        while (res != NULL){
                            printf("* ID: %s || NOME: %s || Total Estrelas: %d *\n", id, nome, totalS);
                            res = (QUERY8) getElementoAtual(resultados);
                            if(res != NULL){
                                id = getBussinesId(buss);
                                nome = getBussinesName(buss);
                                totalS = getBussinesTotalstars(buss);
                            }
                        }
                        break;
                    case 0:
                        flag = 1;
                        break;
                    default: break;
                }
            }
        }
    }
    return resultados;
}



//Query 9. Dada uma palavra, determinar a lista de ids de reviews que a referem no campo text.
//        Note que deverá ter em conta os vários possíveis símbolos de pontuação para delimitar
//        cada palavra que aparece no texto. Nota: função ispunct da biblioteca ctype.h.



int query9(char*palabra){

    printf("**********************Query 9********************\n");
    printf("Escriba una palabra \n");

    char **idReview=malloc(sizeof(char*) * MAXTEXT * 1000000);
    int i;

    if(scanf("%s",palabra)>0) {
        *palabra= toupper(*palabra);


        idReview = travessiaReviewsPorPalabra((estruturaSGR->cat_r), palabra);
    }

    printf("Los id's de review que incluyen la palabra %s en su texto son:\n",palabra);
    for(i=1;i<idReview[0];i++){
        printf("%s\n", idReview[i]);

    }
    return 0;

}