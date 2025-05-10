/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * DEFINIÇÃO DOS ITENS DO JOGO
 */

#ifndef ITENS_JOGO_H

#define ITENS_JOGO_H

#define TAM_MAX_NOME 50

#define TAM_MAX_TIPO 20

typedef struct {

    char identificacao[TAM_MAX_NOME];
    float pesoKg;
    float valorReal;
    char categoria[TAM_MAX_TIPO];
    float relacaoValorPeso;
} ItemJogo;

void calcularRelacaoValorPeso(ItemJogo *item);

int comparadorItens(const void *itemA, const void *itemB);

#endif