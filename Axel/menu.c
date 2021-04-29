#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SGR.h"
#include "leitura.h"



int menu() {
    int op;
    int sair=0;
    while (!sair) {
        printf("\n******************************************************************************************\n");
        printf("*                                          MENU                                            *\n");
        printf("********************************************************************************************\n");
        printf("* 1) Leitura de um ficheiro e apresentação das suas informações                            *\n\n");
        printf("* 2) Determinar a lista de nomes de negócios e o número total de negócios                   \n"
               "     cujo nome inicia por uma dada letra.                                                  *\n\n");
        printf("* 3) Dado um id de negócio, determinar a sua informação: nome, cidade, estado, stars, e     \n"
               "     número total reviews.                                                                 *\n\n");
        printf("* 4) Dado um id de utilizador, determinar a lista de negócios aos quais fez review.        *\n\n");
        printf("* 5) Dado um número n de stars e uma cidade, determinar a lista de negócios com n ou mais   \n"
               "     stars na dada cidade.                                                                 *\n\n");
        printf("* 6) Dado um número inteiro n, determinar a lista dos top n negócios (tendo em conta o      \n"
               "     número médio de stars) em cada cidade.                                                *\n\n");
        printf("* 0) Sair                                                                                  *\n\n");
        printf("******************************************************************************************\n\n");
        printf("Seleccione a opção que pretende realizar: ");

        if(scanf(" %d",&op)>0)printf("Escolheu a opcao : %d\n",op);
        switch (op) {
            case 1:query1();
                break;
            case 2: query2();
                break;
            case 3: query3();
                break;
            case 5: query5();
                break;
            //case 6: query6();
                break;

            case 0:
                sair=1;
                break;
            default: printf("\nOpcao inválida\n");
        }
    }
    return 0;
}
