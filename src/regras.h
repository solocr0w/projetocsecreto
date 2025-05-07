#ifndef REGRAS_H
#define REGRAS_H

#include "itens.h"

float aplicar_regra_magicos(Item *item);
float aplicar_regra_sobrevivencia(Item *item);
const char* traduzir_regra(const char *regra);

#endif