/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * REGRAS ESPECIAIS DO JOGO
 */

#ifndef REGRAS_ESPECIAIS_H

#define REGRAS_ESPECIAIS_H

#include "itens.h"

const char* obterDescricaoRegra(const char *codigoRegra);


float ajustarValorMagico(ItemJogo *item);

float ajustarValorSobrevivencia(ItemJogo *item);

#endif