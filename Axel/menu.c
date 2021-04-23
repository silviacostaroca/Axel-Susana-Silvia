#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SGR.h"
#include "leitura.h"


//Variável global
SGR sgr;

int menu() {
    int op;
    int sair=0;
    while (!sair) {
        printf("\n******************************************************************************************\n");
        printf("*                                          MENU                                            *\n");
        printf("********************************************************************************************\n");
        printf("* 1) Leitura de um ficheiro e apresentação das suas informações                            *\n");
        printf("* 2) Determinar a lista de nomes de negócios e o número total de negócios                   \n"
               "     cujo nome inicia por uma dada letra.                                                  *\n");
        printf("* 3)                                                                                       *\n");
        printf("* 0) Sair                                                                                  *\n");
        printf("******************************************************************************************\n\n");
        printf("Seleccione a opção que pretende realizar: ");

        if(scanf(" %d",&op)>0)printf("Escolheu a opcao : %d\n",op);
        switch (op) {
            case 1:query1();
                break;
            case 2: query2();
                break;

            case 0:
                sair=1;
                break;
            default: printf("\nOpcao inválida\n");
        }
    }
    return 0;
}
