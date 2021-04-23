#include "paginacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



struct resultados{
    int pInicial;
    int pFinal;
    int pAtual;
    int tamLista;
    int tamElem;
    int nrCampos;
    int indAtual;
    int nrPagAtual;
    int nrPagTotal;
    int nrElemPag;
    void ** resultados;
};


/** --------------------------------------- GETS ------------------------------------------------ **/
int getPosInicial(TABLE pagina){
    return pagina->pInicial;
}

int getPosFinal(TABLE pagina){
    return pagina->pFinal;
}

int getPosAtual(TABLE pagina){
    return pagina->pAtual;
}

int getTamanhoLista(TABLE pagina){
    return pagina->tamLista;
}

int getTamanhoElementos(TABLE pagina){
    return pagina->tamElem;
}

int getNrCampos(TABLE pagina){
    return pagina->nrCampos;
}

int getIndiceAtual(TABLE pagina){
    return pagina->indAtual;
}

int getNrPagAtual(TABLE pagina){
    return pagina->nrPagAtual;
}

int getNrPagTotal(TABLE pagina){
    return pagina->nrPagTotal;
}

int getNrElemPag(TABLE pagina){
    return pagina->nrElemPag;
}

void** getResultados (TABLE pagina){
    return pagina->resultados;
}


void setPosInicial(TABLE pagina, int pos){
    pagina->pInicial = pos;
}

void setPosFinal(TABLE pagina, int pos){
    pagina->pFinal = pos;
}

void setPosAtual(TABLE pagina, int pos){
    pagina->pAtual = pos;
}

void setNrCampos(TABLE pagina, int campos){
    pagina->nrCampos = campos;
}

void setNrPagAtual(TABLE pagina, int pag){
    pagina->nrPagAtual = pag;
}

void setNrPagTotal(TABLE pagina, int pag){
    pagina->nrPagTotal = pag;
}

void setElementosPorPagina(TABLE pagina, int n){
    int max = 0;
    if(getNrCampos(pagina) != 0){
        max = getIndiceAtual(pagina)/ getNrCampos(pagina);
    }
    else{
        max = getIndiceAtual(pagina);
    }

    if(n > max)
        pagina->nrElemPag = max;
    else
        pagina->nrElemPag = n;
}


/** -------------------------- INCREMENTAÇÕES/DECREMENTAÇÕES ------------------------------------- **/
int incPagAtualNvezes(TABLE pagina, int veces){
    while(veces > 0){
        pagina->pAtual++;
        veces--;
    }
    return pagina->pAtual;
}

int incPagIndiceAtual(TABLE pagina){
    return pagina->indAtual++;
}

int incPaginaAtual(TABLE pagina){
    return pagina->pAtual++;
}

void PagTotal(TABLE pagina, int p){
    if(p == 0) pagina->nrPagTotal = 1;
    else pagina->nrPagTotal = p;
}

int decPaginaAtual(TABLE pagina){
    return pagina->nrPagAtual--;
}

//Inicialização
TABLE inicPagRtdos(int tamanhoL, int nrCampos){
    TABLE pagina = (TABLE) malloc(sizeof(struct resultados));
    pagina->resultados = (void**) malloc(tamanhoL*nrCampos*sizeof( void* ));

    pagina->tamLista = tamanhoL*nrCampos;
    pagina->nrCampos = nrCampos;

    pagina->tamElem = 0;
    pagina->indAtual = 0;
    pagina->nrPagAtual = 0;
    pagina->nrElemPag = 0;
    pagina->pInicial = 0;
    pagina->pFinal = 0;
    pagina->pAtual = 0;

    return pagina;
}

//Inserir conteudo na página a apresentar
void* inserirDadosPagina(TABLE pagina, void* content){
    pagina->resultados[getIndiceAtual(pagina)] = content;
    incPagIndiceAtual(pagina);
    return content;
}

void paginacao(TABLE pagina){
    int tamanhoLista = pagina->tamLista;
    int tamanhoCadaElemento = pagina->tamElem;
    int indiceAtual = pagina->indAtual;

    int nrPaginaAtual = pagina->pAtual;
    int nrElementosPorPagina = pagina->nrElemPag;
    int posicaoInicial = pagina->pInicial;
    int posicaoAtual = pagina->pAtual;
    int posicaoFinal = pagina->pFinal;
    int nrCampos = pagina->nrCampos;
    int nrPaginasTotal = pagina->nrPagTotal;

    printf("- tamanhoLista %d - tamanhoCadaElemento %d - indiceAtual %d -\n", tamanhoLista, tamanhoCadaElemento, indiceAtual);

    printf("nrPaginasTotal %d\n", nrPaginasTotal);
    printf("nrCampos %d\n", nrCampos);
    printf("nrPaginaAtual %d\n", nrPaginaAtual);
    printf("nrElementosPorPagina %d\n", nrElementosPorPagina);
    printf("posicaoInicial %d\n", posicaoInicial);
    printf("posicaoAtual %d\n", posicaoAtual);
    printf("posicaoFinal %d\n", posicaoFinal);
}

