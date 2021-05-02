//
// Created by Silvia Acosta on 12/04/2021.
//


#define ELEMS_PAG 15 //Numero de elementos a mostrra por página


typedef struct resultados *TABLE;

/** --------------------------------------- GETS ------------------------------------------------ **/
int getPosInicial(TABLE pagina);
int getPosFinal(TABLE pagina);
int getPosAtual(TABLE pagina);
int getTamanhoLista(TABLE pagina);
int getNrCampos(TABLE pagina);
int getIndiceAtual(TABLE pagina);
int getNrPagAtual(TABLE pagina);
int getNrPagTotal(TABLE pagina);
int getNrElemPag(TABLE pagina);
void** getResultados (TABLE pagina);
void* getElementoN(TABLE pagina, int n);
void* getElementoAtual(TABLE pagina);
/***************************************************************************************************/
void setPosInicial(TABLE pagina, int pos);
void setPosFinal(TABLE pagina, int pos);
void setPosAtual(TABLE pagina, int pos);
void setTamLista(TABLE pagina, int tam);
void setNrCampos(TABLE pagina, int campos);
void setIndAtual(TABLE pagina, int indice);
void setNrPagAtual(TABLE pagina, int pag);
void setNrPagTotal(TABLE pagina, int pag);
void setElementosPorPagina(TABLE pagina, int n);

/** -------------------------- INCREMENTAÇÕES/DECREMENTAÇÕES ------------------------------------- **/
int incPagAtualNvezes(TABLE pagina, int vezes);
int incPagIndiceAtual(TABLE pagina);
int incPaginaAtual(TABLE pagina);
int incNrPagAtual(TABLE pagina);
int decPaginaAtual(TABLE pagina);
/** ------------------------------------ FUNÇÕES-------------------------------------------------- **/
TABLE initPagResulatos(int tamanho, int nrCampos);
void posInit(TABLE pagina);
void* inserirDadosPagina(TABLE pagina, void* content);
/**---------------------------------- NAVEGAÇÃO PAGINA -------------------------------------------**/
/** Funções auxiliares **/
int calcularNrPaginasInteiras(int nrTotalElementos, int nrCamposElemento, int nrElementosPorPagina);
int calcularNrElementosUltimaPagina(int nrTotalElementos, int nrCamposElemento, int nrElementosPorPagina);
int calcularNrPaginasTotal(TABLE pagina);
void calcularUltimaPag(TABLE pagina);
int paginaParaFrente(TABLE pagina);
int paginaParaTras(TABLE  pagina);
void paginacaoStats(TABLE pagina);
/** ------------------------------------------- FREE---------------------------------------------- **/
void freePagina(TABLE pagina, void (*funcaofreeItem)());




