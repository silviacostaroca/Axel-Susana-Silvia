//
// Created by Silvia Acosta on 12/04/2021.
//

#ifndef SGR_PAGINACAO_H
#define SGR_PAGINACAO_H
typedef void** Lista;
typedef struct resultados *RESULTADOS;



void ElemePag(RESULTADOS pagina, int n);
void PagTotal(RESULTADOS pagina, int p);
int incPAtualNvezes(RESULTADOS pagina, int veces);
int IndInsercao(RESULTADOS pagina);
RESULTADOS inicPagRtdos(int tamanhoL, int nrCampos);
void paginacao(RESULTADOS pagina);


#endif //SGR_PAGINACAO_H



