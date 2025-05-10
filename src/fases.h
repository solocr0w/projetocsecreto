/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * DEFINIÇÃO DAS FASES
 */

#ifndef FASES_JOGO_H

#define FASES_JOGO_H

#include "itens.h"

#define MAX_ITENS_FASE 20

#define TOTAL_FASES 4

#define TAM_MAX_REGRA 30

typedef struct {

    char titulo[50];
    float capacidadeMochila;
    char regraEspecial[TAM_MAX_REGRA];
    ItemJogo itensDisponiveis[MAX_ITENS_FASE];
    int quantidadeItens;
    float lucroObtido;
    
} FaseJogo;

void executarFase(FaseJogo *fase);

#endif