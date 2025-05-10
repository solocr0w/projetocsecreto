/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * IMPLEMENTAÇÃO DAS REGRAS
 */

#include "regras.h"

#include <string.h>

/**
 * Traduz códigos de regra para texto
 */

const char* obterDescricaoRegra(const char *codigoRegra) {

    if (strcmp(codigoRegra, "MAGICOS_VALOR_DOBRADO") == 0) {

        return "Itens mágicos valem duas vezes mais";
    
    } else if (strcmp(codigoRegra, "TECNOLOGICOS_INTEIROS") == 0) {

        return "Itens tecnológicos não podem ser fracionados";
    
    } else if (strcmp(codigoRegra, "SOBREVIVENCIA_DESVALORIZADA") == 0) {

        return "Itens de sobrevivência valem 20pc menos";
    
    } else if (strcmp(codigoRegra, "TRES_MELHORES_VALOR_PESO") == 0) {

        return "Os 3 melhores itens por valor/peso";
    }
    
    return "Sem regras aplicadas";
}

/**
 * Aplica modificador para itens mágicos
 */
float ajustarValorMagico(ItemJogo *item) {
    
    if (strcmp(item->categoria, "magico") == 0) {

        return item->valorReal * 2.0f;
    }
    
    return item->valorReal;
}

/**
 * Aplica modificador para itens de sobrevivência
 */

float ajustarValorSobrevivencia(ItemJogo *item) {

    if (strcmp(item->categoria, "sobrevivencia") == 0) {


        return item->valorReal * 0.8f;

    }
    
    return item->valorReal;
}