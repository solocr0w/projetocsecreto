#include "regras.h"
#include <string.h>

float aplicar_regra_magicos(Item *item) {
    if (strcmp(item->tipo, "magico") == 0) {
        return item->valor * 2;
    }
    return item->valor;
}

float aplicar_regra_sobrevivencia(Item *item) {
    if (strcmp(item->tipo, "sobrevivencia") == 0) {
        return item->valor * 0.8;
    }
    return item->valor;
}

const char* traduzir_regra(const char *regra) {
    if (strcmp(regra, "MAGICOS_VALOR_DOBRADO") == 0) {
        return "Itens magicos com valor dobrado";
    } else if (strcmp(regra, "TECNOLOGICOS_INTEIROS") == 0) {
        return "Itens tecnologicos nao podem ser fracionados";
    } else if (strcmp(regra, "SOBREVIVENCIA_DESVALORIZADA") == 0) {
        return "Itens de sobrevivencia perdem 20%% do valor";
    } else if (strcmp(regra, "TRES_MELHORES_VALOR_PESO") == 0) {
        return "Apenas os tres itens com maior valor/peso podem ser escolhidos";
    }
    return "Nenhuma regra especial";
}