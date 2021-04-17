//
// Created by Silvia Acosta on 12/04/2021.
//

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

void ElemePag(RESULTADOS pagina, int n){
    int max = 0;
    if((pagina->nrCampos) != 0)
        max = (pagina->indAtual) / (pagina->nrCampos);
    else
        max = pagina->indAtual;

    if(n > max) pagina->nrElemPag = max;
    else pagina->nrElemPag = n;
}

void PagTotal(RESULTADOS pagina, int p){
    if(p == 0) pagina->nrPagTotal = 1;
    else pagina->nrPagTotal = p;
}

int incPAtualNvezes(RESULTADOS pagina, int veces){
    while(veces > 0){
        pagina->pAtual++;
       veces--;
    }
    return pagina->pAtual;
}

int IndInsercao(RESULTADOS pagina){
    return pagina->indAtual * pagina->tamElem;
}

RESULTADOS inicPagRtdos(int tamanhoL, int nrCampos){
    RESULTADOS pagina = (RESULTADOS) malloc(sizeof(struct resultados));
    pagina->resultados = (Lista) malloc(tamanhoL*nrCampos*sizeof( void* ));

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

void paginacao(RESULTADOS pagina){
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
