//
// Created by Silvia Acosta on 12/04/2021.
//

#ifndef GRUPO66_PAGINACAO_H
#define GRUPO66_PAGINACAO_H

#define ELEMS_PAG 15 //Numero de elementos a mostrra por página


typedef struct resultados *TABLE;

//Gets e SEts
int getPosInicial(TABLE pagina);
int getPosFinal(TABLE pagina);
int getPosAtual(TABLE pagina);
int getTamanhoLista(TABLE pagina);
int getTamanhoElementos(TABLE pagina);
int getNrCampos(TABLE pagina);
int getIndiceAtual(TABLE pagina);
int getNrPagAtual(TABLE pagina);
int getNrPagTotal(TABLE pagina);
int getNrElemPag(TABLE pagina);
void** getResultados (TABLE pagina);
void setPosInicial(TABLE pagina, int pos);
void setPosFinal(TABLE pagina, int pos);
void setPosAtual(TABLE pagina, int pos);
void setNrCampos(TABLE pagina, int campos);
void setNrPagAtual(TABLE pagina, int pag);
void setNrPagTotal(TABLE pagina, int pag);
void setElementosPorPagina(TABLE pagina, int n);
/** -------------------------- INCREMENTAÇÕES/DECREMENTAÇÕES ------------------------------------- **/
int incPagAtualNvezes(TABLE pagina, int veces);
int incPagIndiceAtual(TABLE pagina);
int incPaginaAtual(TABLE pagina);
void PagTotal(TABLE pagina, int p);
int decPaginaAtual(TABLE pagina);
TABLE inicPagRtdos(int tamanhoL, int nrCampos);
void* inserirDadosPagina(TABLE pagina, void* content);
void paginacao(TABLE pagina);



#endif //GRUPO66_PAGINACAO_H



