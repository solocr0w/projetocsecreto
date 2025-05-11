/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * MÓDULO: IMPLEMENTAÇÃO DAS REGRAS ESPECIAIS
 * DESCRIÇÃO: Implementa as regras especiais que modificam o comportamento
 *            dos itens em cada fase do jogo, afetando sua seleção e valor
 * 
 * REGRAS IMPLEMENTADAS:
 *  - Valor dobrado para itens mágicos
 *  - Itens tecnológicos não-fracionáveis
 *  - Desvalorização de itens de sobrevivência
 *  - Limitação aos 3 melhores itens por valor/peso
 * 
 * DEPENDÊNCIAS:
 *  - ItemJogo: Estrutura de dados dos itens (definida em itens.h)
 */

#include "regras.h"

#include <string.h>

/**
 * FUNÇÃO: obterDescricaoRegra
 * OBJETIVO: Traduz códigos internos de regras para descrições amigáveis
 *           que serão exibidas ao jogador
 * 
 * PARÂMETROS:
 *   @param codigoRegra: String com o código da regra (ex: "MAGICOS_VALOR_DOBRADO")
 * 
 * RETORNO:
 *   - Ponteiro para string constante com a descrição humanizada
 *   - "Sem regras aplicadas" para códigos desconhecidos
 * 
 * TABELA DE TRADUÇÃO:
 *   - MAGICOS_VALOR_DOBRADO → "Itens mágicos valem duas vezes mais"
 *   - TECNOLOGICOS_INTEIROS → "Itens tecnológicos não podem ser fracionados"
 *   - SOBREVIVENCIA_DESVALORIZADA → "Itens de sobrevivência valem 20% menos"
 *   - TRES_MELHORES_VALOR_PESO → "Os 3 melhores itens por valor/peso"
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
 * FUNÇÃO: ajustarValorMagico
 * OBJETIVO: Aplica modificador de valor para itens mágicos (dobro do valor)
 * 
 * PARÂMETROS:
 *   @param item: Ponteiro para o item a ser avaliado
 * 
 * RETORNO:
 *   - Valor original multiplicado por 2 se o item for mágico
 *   - Valor original inalterado para outros tipos
 * 
 * LÓGICA:
 *   - Verifica se a categoria do item é "magico"
 *   - Aplica fator de multiplicação 2 quando verdadeiro
 *   - Mantém valor original caso contrário
 */

float ajustarValorMagico(ItemJogo *item) {
    
    if (strcmp(item->categoria, "magico") == 0) {

        return item->valorReal * 2.0f;
    }
    
    return item->valorReal;
}

/**
 * FUNÇÃO: ajustarValorSobrevivencia
 * OBJETIVO: Aplica penalidade de valor para itens de sobrevivência (80% do valor)
 * 
 * PARÂMETROS:
 *   @param item: Ponteiro para o item a ser avaliado
 * 
 * RETORNO:
 *   - Valor original multiplicado por 0.8 se o item for de sobrevivência
 *   - Valor original inalterado para outros tipos
 * 
 * OBSERVAÇÕES:
 *   - Redução de 20% simulando desgaste/desvalorização
 *   - Fator 0.8f garante precisão em cálculos float
 */

float ajustarValorSobrevivencia(ItemJogo *item) {

    if (strcmp(item->categoria, "sobrevivencia") == 0) {


        return item->valorReal * 0.8f;

    }
    
    return item->valorReal;
}