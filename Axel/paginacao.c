#include "paginacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct resultados{
    int posInicial; //Posição inicial da lista de resultos
    int posFinal; //Posição final da lista de resultos
    int posAtual; //Posição atual da lista de resultos
    int tamLista; //Nº de elementos a mostrar x nº campos do resultado
    int nrCampos; //nº campos do resultado
    int indAtual; //Indice atual
    int nrPagAtual; // Nº da pagina atual
    int nrPagTotal; //Nº da pagina final
    int nrElemPag; //Nº de elemtos por pagina
    void ** resultados; //Resultados a apresentar
};

/** --------------------------------------- GETS ------------------------------------------------ **/
int getPosInicial(TABLE pagina){
    return pagina->posInicial;
}

int getPosFinal(TABLE pagina){
    return pagina->posFinal;
}

int getPosAtual(TABLE pagina){
    return pagina->posAtual;
}

int getTamanhoLista(TABLE pagina){
    return pagina->tamLista;
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

void* getElementoN(TABLE pagina, int n){
    return (void*)(pagina->resultados[n]);
}

void* getElementoAtual(TABLE pagina){
    int atual = getPosAtual(pagina);
    int fim = getPosFinal(pagina);
    int nrCampos = getNrCampos(pagina);
    if( atual  <= fim ){
        void* resposta = getElementoN(pagina, atual);
        incPagAtualNvezes(pagina,nrCampos);
        return resposta;
    }else{
        return NULL;
    }
}

/***************************************************************************************************/
void setPosInicial(TABLE pagina, int pos){
    pagina->posInicial = pos;
}

void setPosFinal(TABLE pagina, int pos){
    pagina->posFinal = pos;
}

void setPosAtual(TABLE pagina, int pos){
    pagina->posAtual = pos;
}

void setTamLista(TABLE pagina, int tam){
    pagina->tamLista = tam;
}

void setNrCampos(TABLE pagina, int campos){
    pagina->nrCampos = campos;
}

void setIndAtual(TABLE pagina, int indice){
    pagina->indAtual = indice;
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
        max = getIndiceAtual(pagina)/getNrCampos(pagina);
    }
    else{
        max = getIndiceAtual(pagina);
    }

    if(n > max) {
        if (max == 0)
            pagina->nrElemPag = 1;
        pagina->nrElemPag = max;
    }
    else
        pagina->nrElemPag = n;
}

/** -------------------------- INCREMENTAÇÕES/DECREMENTAÇÕES ------------------------------------- **/
int incPagAtualNvezes(TABLE pagina, int vezes){
    while(vezes > 0){
        pagina->posAtual++;
        vezes--;
    }
    return pagina->posAtual;
}

int incPagIndiceAtual(TABLE pagina){
    return pagina->indAtual++;
}

int incPaginaAtual(TABLE pagina){
    return pagina->posAtual++;
}

int incNrPagAtual(TABLE pagina){
    return pagina->nrPagAtual++;
}

int decPaginaAtual(TABLE pagina){
    return pagina->nrPagAtual--;
}

/** ------------------------------------ FUNÇÕES--------------------------------------- **/

//Inicialização
TABLE initPagResulatos(int tamanho, int nrCampos){
    TABLE pagina = (TABLE) malloc(sizeof(struct resultados));
    pagina->resultados = (void**) malloc(tamanho*nrCampos*sizeof( void* ));
    pagina->tamLista = tamanho*nrCampos;
    pagina->nrCampos = nrCampos;
    pagina->nrPagTotal = 0;
    pagina->indAtual = 0;
    pagina->nrPagAtual = 0;
    pagina->nrElemPag = 0;
    pagina->posInicial = 0;
    pagina->posFinal = 0;
    pagina->posAtual = 0;
    return pagina;
}

//Inicialização das posições
void posInit(TABLE pagina){
    int nrPagina = getNrPagAtual(pagina);
    int elemPrPagina = getNrElemPag(pagina);
    int nrCampos = getNrCampos(pagina);
    setPosAtual(pagina, nrPagina * elemPrPagina * nrCampos);
    setPosFinal(pagina, getPosInicial(pagina) + elemPrPagina * nrCampos - 1 * nrCampos);
    setNrPagTotal(pagina, calcularNrPaginasTotal(pagina));
}

//Inserir conteudo na página a apresentar
void* inserirDadosPagina(TABLE pagina, void* content){
    pagina->resultados[getIndiceAtual(pagina)] = content;
    incPagIndiceAtual(pagina);
    return content;
}

/**--------------------------------------------- NAVEGAÇÃO PAGINA -------------------------------------------**/
/** Funções auxiliares **/
int calcularNrPaginasInteiras(int nrTotalElementos, int nrCamposElemento, int nrElementosPorPagina){
    if (nrElementosPorPagina == 0)
        return 0;
    else
        return nrTotalElementos/ (nrElementosPorPagina* nrCamposElemento);
}

int calcularNrElementosUltimaPagina(int nrTotalElementos, int nrCamposElemento, int nrElementosPorPagina){
    if (nrElementosPorPagina == 0)
        return 0;
    else
        return nrTotalElementos % (nrElementosPorPagina* nrCamposElemento);
}

int calcularNrPaginasTotal(TABLE pagina){
    int nrPaginas = calcularNrPaginasInteiras(getIndiceAtual(pagina), getNrCampos(pagina), getNrElemPag(pagina));
    int nrElemsUltimaPag = calcularNrElementosUltimaPagina(getIndiceAtual(pagina), getNrCampos(pagina), getNrElemPag(pagina));
    return nrElemsUltimaPag > 0 ? nrPaginas + 1 : nrPaginas;
}

void calcularUltimaPag(TABLE pagina){
    int nrPagina = calcularNrPaginasInteiras(getIndiceAtual(pagina), getNrCampos(pagina), getNrElemPag(pagina));
    int nrElementosUltimaPag = calcularNrElementosUltimaPagina(getIndiceAtual(pagina), getNrCampos(pagina),
                                                               getNrElemPag(pagina));
    if(nrElementosUltimaPag == 0){
        if(nrPagina) nrPagina--;
        setNrPagAtual(pagina, nrPagina);
        setPosInicial(pagina, nrPagina * getNrElemPag(pagina) * getNrCampos(pagina));
        setPosFinal(pagina, getPosInicial(pagina) +  getNrElemPag(pagina) * getNrCampos(pagina) - 1);
        setPosAtual(pagina, nrPagina * getNrElemPag(pagina) * getNrCampos(pagina));
    }
    else{
        setNrPagAtual(pagina, nrPagina);
        setPosInicial(pagina, nrPagina * getNrElemPag(pagina) * getNrCampos(pagina));
        setPosFinal(pagina, getPosInicial(pagina) +  nrElementosUltimaPag * getNrCampos(pagina) - 1);
        setPosAtual(pagina, nrPagina * getNrElemPag(pagina) * getNrCampos(pagina));
    }
}

int paginaParaFrente(TABLE pagina){
    int max = getIndiceAtual(pagina);
    int nrElemPorPag = getNrElemPag(pagina);
    int nrCampos = getNrCampos(pagina);
    int posicaoInicial = getPosInicial(pagina);
    int posicaoFinal = getPosAtual(pagina);
    if(getNrPagAtual(pagina) >= getNrPagTotal(pagina)-1){
        setPosAtual(pagina, posicaoInicial);
        return 0;
    }
    if (posicaoFinal + nrElemPorPag * nrCampos >= max){
        int nrElementosUltimaPag = calcularNrElementosUltimaPagina(getIndiceAtual(pagina), nrCampos, getNrElemPag(pagina));
        if(nrElementosUltimaPag > 0) calcularUltimaPag(pagina);
        return 0;
    }else{
        incPaginaAtual(pagina);
        setPosInicial(pagina, posicaoFinal + 1 * nrCampos);
        setPosFinal(pagina, posicaoFinal + nrElemPorPag * nrCampos);
        setPosAtual(pagina, posicaoFinal + 1 * nrCampos);
        return getPosInicial(pagina);
    }
}

int paginaParaTras(TABLE  pagina){
    int nrElemPorPag = getNrElemPag(pagina);
    int nrCampos = getNrCampos(pagina);
    int posicaoInic = getPosInicial(pagina);
    if(getNrPagAtual(pagina) == 0){
        setPosAtual(pagina, 0);
        return 0;
    }else{
        decPaginaAtual(pagina);
        setPosInicial(pagina, posicaoInic - nrElemPorPag * nrCampos);
        setPosFinal(pagina, posicaoInic - 1 * nrCampos);
        setPosAtual(pagina, posicaoInic - nrElemPorPag * nrCampos);
        return getPosInicial(pagina);
    }
}

//FUNÇÃO PARA VALIDAR AS INFORMAÇÕES DA PAGINAÇÃO
void paginacaoStats(TABLE pagina){
    int tamanhoLista = getTamanhoLista(pagina);
    int indiceAtual = getIndiceAtual(pagina);
    int nrPaginaAtual = getNrPagAtual(pagina);
    int nrElementosPorPagina = getNrElemPag(pagina);
    int posicaoInicial = getPosInicial(pagina);
    int posicaoAtual = getPosAtual(pagina);
    int posicaoFinal = getPosFinal(pagina);
    int nrCampos = getNrCampos(pagina);
    int nrPaginasTotal = getNrPagTotal(pagina);
    printf("Tamanho da Pagina %d || Índice Atual %d -\n", tamanhoLista, indiceAtual);
    printf("Nr Total de Paginas: %d\n", nrPaginasTotal);
    printf("Nr de Campos: %d\n", nrCampos);
    printf("Nr da Pagina Atual: %d\n", nrPaginaAtual);
    printf("Nr de Elementos por Pagina: %d\n", nrElementosPorPagina);
    printf("Pagina Inicial: %d\n", posicaoInicial);
    printf("Pagina Atual: %d\n", posicaoAtual);
    printf("Pagina Final  %d\n", posicaoFinal);
}


/** ------------------------------------------- FREE-------------------------------------------- **/
void freePagina(TABLE pagina, void (*funcaofreeItem)()){
    int i, tamanho = getTamanhoLista(pagina);
    for(i = 0; i < tamanho; i++){
        funcaofreeItem(getElementoN(pagina,i));
    }
    free(getResultados(pagina));
    free(pagina);
}