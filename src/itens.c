/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * MÓDULO: IMPLEMENTAÇÃO DOS ITENS
 * DESCRIÇÃO: Implementa as operações fundamentais para manipulação dos itens do jogo,
 *            incluindo cálculo de eficiência (valor/peso) e comparação para ordenação.
 * 
 * PRINCIPAIS FUNCIONALIDADES:
 *  - Cálculo da relação valor/peso para avaliação de eficiência
 *  - Função de comparação para ordenação decrescente por valor/peso
 *  - Tratamento seguro para itens com peso mínimo
 */

#include "itens.h"
#include <string.h>

/**
 * FUNÇÃO: comparadorItens
 * OBJETIVO: Servir como função de comparação para qsort, ordenando itens por valor/peso
 *           em ordem decrescente (do mais valioso para o menos valioso por kg)
 * 
 * PARÂMETROS:
 *   @param itemA: Ponteiro para o primeiro item a ser comparado
 *   @param itemB: Ponteiro para o segundo item a ser comparado
 * 
 * RETORNO:
 *   - -1 se itemA tem maior valor/peso que itemB
 *   -  1 se itemA tem menor valor/peso que itemB
 *   -  0 se os itens tem igual valor/peso
 * 
 * COMPORTAMENTO:
 *   - Implementa a lógica inversa para ordenação decrescente
 *   - Compatível com a função qsort da biblioteca padrão
 *   - Considera a precisão de ponto flutuante nas comparações
 */

int comparadorItens(const void *itemA, const void *itemB) {
    
    const ItemJogo *primeiro = (const ItemJogo *)itemA;
    const ItemJogo *segundo = (const ItemJogo *)itemB;
    
    if (primeiro->relacaoValorPeso > segundo->relacaoValorPeso) return -1;
    if (primeiro->relacaoValorPeso < segundo->relacaoValorPeso) return 1;
    
    return 0;
}

/**
 * FUNÇÃO: calcularRelacaoValorPeso
 * OBJETIVO: Calcula a eficiência de um item (valor por unidade de peso) e armazena
 *           no campo relacaoValorPeso da estrutura ItemJogo
 * 
 * PARÂMETROS:
 *   @param item: Ponteiro para o item a ser calculado (modificado in-place)
 * 
 * LÓGICA DE OPERAÇÃO:
 *   1. Verifica se o peso é maior que um limite mínimo (0.01kg para evitar divisão por zero)
 *   2. Calcula a razão valorReal/pesoKg
 *   3. Armazena o resultado no campo relacaoValorPeso
 *   4. Caso o peso seja inválido, define eficiência como zero
 * 
 * OBSERVAÇÕES:
 *   - Fundamental para a estratégia gulosa de seleção de itens
 *   - Garante estabilidade numérica com o limite mínimo de peso
 */

void calcularRelacaoValorPeso(ItemJogo *item) {
    
    if (item->pesoKg > 0.01f) {
        item->relacaoValorPeso = item->valorReal / item->pesoKg;
    } else {
        item->relacaoValorPeso = 0.0f;
    }
}
