//
// Created by Silvia Acosta on 17/04/2021.
//

#include <stdio.h>
#include <ctype.h>

#include "catalogo_users.h"
#include "catalogo_bussines.h"
#include "catalogo_reviews.h"
#include "leitura.h"
#include "menu.h"
/**
int menu()
{
    char opcao[1], op[1], l[1];
    int sair=0, flag=0, pm; //m,sm,x
    char* p, f; //g,
    USER u;
    BUSSINES b;
    REVIEW r;
    printf("\n***********************************************************************************************\n");
    printf("                                           MENU                                                  \n");
    printf("*********************************************************************************+******+********\n");
    printf("*************************************************************************************************\n");
    printf(" 1)                                                                                            \n\n");
    printf("*************************************************************************************************\n");
    printf(" 2) Determinar a lista de nomes de negócios e o número total de negócios cujo nome inicia        \n"
               " por uma dada letra. Note que a procura não deverá ser case sensitive                      \n\n");
    printf("*************************************************************************************************\n");
    printf(" 3) Dado um id de negócio, determinar a sua informação: nome, cidade, estado, stars,             \n"
           "     e número total reviews.                                                                   \n\n");
    printf("*************************************************************************************************\n");
    printf(" 4) Dado um id de utilizador, determinar a lista de negócios aos quais fez review.               \n  "
           "     A informação associada a cada negócio deve ser o id e o nome.                             \n\n");
    printf("*************************************************************************************************\n");
    printf(" 5) Dado um número n de stars e uma cidade, determinar a lista de negócios com n ou mais         \n"
           "     stars na dada cidade. A informação associada a cada negócio deve ser o seu id e nome.     \n\n");
    printf("*************************************************************************************************\n");
    printf(" 6) Dado um número inteiro n, determinar a lista dos top n negócios associada a cada             \n"
           "     (tendo em conta o número médio de stars) em cada cidade. A informação  negócio              \n"
           "     deve ser o seu id, nome, e número de estrelas.                                            \n\n");
    printf("*************************************************************************************************\n");
    printf(" 7) Determinar a lista de ids de utilizadores e o número total de utilizadores que tenham        \n"
           "     visitado mais de um estado, i.e. que tenham feito reviews em negócios de diferentes estado.\n\n");
    printf("*************************************************************************************************\n");
    printf(" 8) Dado um número inteiro n e uma categoria, determinar a lista dos top n negócios              \n"
           "         (tendo em conta o número médio de stars) que pertencem a uma determinada categoria.     \n"
           "         A informação associada a cada negócio deve ser o seu id, nome, e número de estrelas.    \n\n");
    printf("*************************************************************************************************\n");
    printf(" 9) Dada uma palavra, determinar a lista de ids de reviews que a referem no campo text.          \n"
           "    Note que deverá ter em conta os vários possíveis símbolos de pontuação para delimitar        \n"
           "    cada palavra que aparece no texto. Nota: função ispunct da biblioteca ctype.h.               \n\n");
    printf("*************************************************************************************************\n");
    printf(" 0) Sair                                                                                          \n");
    printf("*************************************************************************************************\n\n");
    printf("Seleccione a opção que pretende realizar: ");
    scanf("%s", opcao);
    printf("\n");
    while(sair!=1)
    {
        if (strcmp(opcao, "1")==0)
        {
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //query1();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    //query1();
                    printf("\nDeseja executar esta query novamente?(S/N): ");
                    scanf("%s", op);
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(opcao, "2")==0)
        {
            printf("Qual a letra inicial a escolher? (A, B, ..., Z) ");
            scanf("%s",l);
            //query2(l);
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    printf("Qual a letra inicial a escolher? (A, B, ..., Z)  ");
                    scanf("%s",l);
                    //query2(l);
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
     ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if(strcmp(opcao, "3")==0)
        {
            printf("Introduza o código do negocio: ");
            scanf("%s",(char *)b);
            //query3(m,p);
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", (char *)op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    printf("Introduza o código do negocio: ");
                    scanf("%s", (char *)b);
                    //query3(m,p);
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(opcao, "4")==0)
        {
            //query4();
            printf("Introduza o id do user: ");
            scanf("%s",(char *)u);
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    //query4();
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(opcao, "5")==0)
        {
            //query5();
            printf("Introduza o numero de estrelas: ");
            scanf("%f",(float *)r);
            printf("Introduza a cidade: ");
            scanf("%s",(char *)r);
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    //query5();
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(opcao, "6")==0)
        {
            printf("Introduza um numero: ");
            scanf("%d",&pm);
            //query 6();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    printf("Introduza um numero: ");
                    scanf("%d",&pm);
                    //query7;
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(opcao, "7")==0)
        {
            //query7();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    //query7();
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(opcao, "8")==0)
        {
            printf("Introduza um mumero: ");
            scanf("%d",&pm);
            printf("Introduza uma categoria: ");
            scanf("%f", (char *)f);
            //query8(p, f);
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    printf("Introduza um numero: ");
                    scanf("%d", (char *)p);
                    printf("Introduza uma categoria: ");
                    scanf("%f",&f);
                    //query8(p, f);
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        else if (strcmp(opcao, "9")==0)
        {
            printf("Introduza uma palavrar: ");
            scanf("%s", (char *)u);
            //query9(c,m);
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    printf("Introduza uma palabra: ");
                    scanf("%s", (char *)u);
                    //query9;
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
        else if(strcmp(opcao, "10")==0)
        {
            //query10();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    //query10();
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
        else if(strcmp(opcao, "11")==0)
        {
            printf("Introduza o código do user: ");
            scanf("%s", (char *)u);
            //query11();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    printf("Introduza o código do user: ");
                    scanf("%s", (char *)u);
                    //query11();
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
        else if (strcmp(opcao, "12")==0)
        {
            //query12();
            printf("\nDeseja executar esta query novamente?(S/N): ");
            scanf("%s", op);
            printf("\n");
            while (flag!=1)
            {
                if ((strcmp(op,"S")==0)||(strcmp(op,"s")==0))
                {
                    //query12();
                    flag=0;
                    sair=0;
                }
                else if ((strcmp(op,"N")==0)||(strcmp(op,"n")==0))
                {
                    flag=1;
                    sair=1;
                    fflush(stdin);
                    menu();
                }
                else if ((strcmp(op,"S")!=0)||(strcmp(op,"N")!=0)||(strcmp(op,"s")!=0)||(strcmp(op,"n")!=0))
                {
                    printf("\nOpção inexistente! Deverá seleccionar 'S' ou 'N'! ");
                    scanf("%s",op);
                    flag=0;
                }
            }
        }
        else if (strcmp(opcao, "0")==0)
            sair=1;
        else
        {
            printf("Opção inexistente! Deverá seleccionar um valor entre 0 e 12.\n");
            printf("Seleccione a opção que pretende realizar: ");
            scanf("%s", opcao);
            printf("\n");
        }
    }
    return 0;
}
**/