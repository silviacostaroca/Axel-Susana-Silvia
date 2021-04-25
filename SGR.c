#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "SGR.h"
#include "catalogo_users.h"
#include "catalogo_bussines.h"
#include "catalogo_reviews.h"

#include "leitura.h"
#include "time.h"


/**---------------- Estruturas de Dados ---------------**/
struct sgr{
    CATALOGO_USER cat_u;
    CATALOGO_BUSSINES cat_b;
    CATALOGO_REVIEWS cat_r;
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
    estruturaSGR = init_SGR();
    int flag = 0;
    char tFicheiro;
    char nomeFicheiro[MAXBUFFER];
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
            }
            else {
                printf("\nFicheiro inexistente\n");
            }
            break;
        case 'B':
            printf("Indique o nome do ficheiro a abrir: \n");
            if (scanf("%s", nomeFicheiro) > 0) {
                printf("Escolheu o ficheiro de nome : %s\n", nomeFicheiro);
                estruturaSGR->cat_b = load_sgr(NULL, "bussines.csv", NULL)->cat_b;
            }
            else {
                printf("\nFicheiro inexistente\n");
            }
            break;
        case 'R':
            printf("Indique o nome do ficheiro a abrir: \n");
            if (scanf(" %s", nomeFicheiro) > 0) {
                printf("Escolheu o ficheiro de nome : %s\n", nomeFicheiro);
                estruturaSGR->cat_r = load_sgr(NULL, NULL, "reviews.csv")->cat_r;
            } else {
                printf("\nFicheiro inexistente\n");
            }
            break;
        case 'T':
            free_sgr(estruturaSGR);
            estruturaSGR =init_SGR();
            estruturaSGR = load_sgr("users.csv", "bussines.csv", "reviews.csv");
            //    printf("NAME BUSSINES: %d\n", getBussinesName(getBussines(estruturaSGR->cat_b, "bvN78flM8NLprQ1a1y5dRg")));
            break;
        default: {
            printf("Tipo de ficheiro inválido");
            printf("\nIndique o tipo de ficheiro que deseja abrir (U-users B-bussines R-reviews): \n");
            if (scanf(" %c", &tFicheiro) > 0)printf("Escolheuo tipo : %c\n", tFicheiro);
        }
    }
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

            // if(scanf(" %c",&letra)>0)
        }
    printf("Vão ser listados todos os negócios cujo nome inicia por: %c\n",letra);
    letra= toupper(letra);
    resultados = businesses_started_by_letter(estruturaSGR,letra);
    return EXIT_SUCCESS;
}

TABLE businesses_started_by_letter(SGR sgr, char letter){
    int flag = 0;
    int nrResultados = 0;
    char letra = letter;
    clock_t tempIni, tempFim;
    TABLE resultados;
    tempIni = clock();
    printf("ID user: %s\n", getBussinesId(getBussines(sgr->cat_b, "bvN78flM8NLprQ1a1y5dRg")));
    resultados = travessiaBussinesPorLetra (sgr->cat_b, letra);
    tempFim = clock();
    nrResultados = getTamanhoLista(resultados);
    setElementosPorPagina(resultados, ELEMS_PAG);
    while(flag==0){
        if(nrResultados == 0){
            printf("Não foram encontrados resultados para essa letra\n");
            printf("Indique a letra que quer listar ou 0-Sair\n");
            if(scanf(" %c",&letra)>0)
                if(letra - 48 == 0) {
                    flag = 1;
                    break;
                }
        }
        printf("Listar negócios começados pela letra %c (em %ldseg)\n", letra, tempFim-tempIni);
    }
    return resultados;
}



//Query 3. Dado um id de negócio, determinar a sua informação: nome, cidade, estado, stars,
//e número total reviews.

//      TABLE business_info(SGR sgr, char *business_id);

//Dado um id de negócio, determinar a sua informação: nome, cidade, estado, stars, e número total reviews.

int query3(char* idB){

    printf("**********************Query 3********************\n");
    printf("Indique o id de un negocio\n");
    BUSSINES b;
   // REVIEW r;
    //float rs;
    char *n, *c, *e, **categ;


    if(scanf("%s",idB)>0){

        b = getBussines(estruturaSGR->cat_b,idB);
        n = getBussinesName(b);
        c = getBussinesCity(b);
        e = getBussinesState(b);
        categ= getBussinesCategorias(b);
        // r = getReview(sgr->cat_r, idB);
        // rs = getReviewStars(r);

    }

    printf("El nombre del negocio es %s y esta en la ciudad %s perteneciente al estado %s\n ", n, c, e);
    for (int i=0;i< getBussinesTotalCat(b);i++){
        printf("Las categorias de este negocio son %s\n", categ[i]);
    }
    return 0;

}

/**
Query 4. Dado um id de utilizador, determinar a lista de negócios aos quais fez review.
        A informação associada a cada negócio deve ser o id e o nome.

        TABLE businesses_reviewed(SGR sgr, char *user_id);

Query 5. Dado um número n de stars e uma cidade, determinar a lista de negócios com n ou mais stars na dada cidade.
        A informação associada a cada negócio deve ser o seu id e nome.

        TABLE businesses_with_stars_and_city(SGR sgr, float stars, char *city);

Query 6. Dado um número inteiro n, determinar a lista dos top n negócios
        (tendo em conta o número médio de stars) em cada cidade. A informação
        associada a cada negócio deve ser o seu id, nome, e número de estrelas.

        TABLE top_businesses_by_city(SGR sgr, int top);

Query 7. Determinar a lista de ids de utilizadores e o número total de utilizadores que tenham visitado
        mais de um estado, i.e. que tenham feito reviews em negócios de diferentes estados.

        TABLE international_users(SGR sgr);

Query 8. Dado um número inteiro n e uma categoria, determinar a lista dos top n negócios
        (tendo em conta o número médio de stars) que pertencem a uma determinada categoria.
        A informação associada a cada negócio deve ser o seu id, nome, e número de estrelas.

        TABLE top_businesses_with_category(SGR sgr, int top, char *category);


Query 9. Dada uma palavra, determinar a lista de ids de reviews que a referem no campo text.
        Note que deverá ter em conta os vários possíveis símbolos de pontuação para delimitar
        cada palavra que aparece no texto. Nota: função ispunct da biblioteca ctype.h.

        int findPalavra(char* text, char * word){
            if(strstr(text, word)!=NULL)
                return EXIT_SUCCESS;
            else return EXIT_FAILURE;
        }

        TABLE reviews_with_word(SGR sgr, int top, char *word){
           TABLE res = (TABLE)malloc(sizeof(struct table));
        }

        */
