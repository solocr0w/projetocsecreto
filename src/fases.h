#ifndef FASES_H
#define FASES_H

#include "itens.h"

#define MAX_ITENS 20
#define MAX_FASES 4
#define MAX_REGRA 30

typedef struct {
    char nome[50];
    float capacidade;
    char regra[MAX_REGRA];
    Item itens[MAX_ITENS];
    int num_itens;
    float lucro;
} Fase;

void processar_fase(Fase *fase);

#endif