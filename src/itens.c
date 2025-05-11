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

// Função para trocar dois itens
void trocarItens(ItemJogo *a, ItemJogo *b) {
    ItemJogo temp = *a;
    *a = *b;
    *b = temp;
}

// Função de partição para o Quick Sort
int particionar(ItemJogo *itens, int baixo, int alto) {
    float pivo = itens[alto].relacaoValorPeso;
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (itens[j].relacaoValorPeso > pivo) {  // Ordem decrescente
            i++;
            trocarItens(&itens[i], &itens[j]);
        }
    }
    trocarItens(&itens[i + 1], &itens[alto]);
    return (i + 1);
}

// Função Quick Sort
void quickSortItens(ItemJogo *itens, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(itens, baixo, alto);
        quickSortItens(itens, baixo, pi - 1);
        quickSortItens(itens, pi + 1, alto);
    }
}

// Função wrapper para ordenação
void arrumarItens(ItemJogo *itens, int quantidade) {
    quickSortItens(itens, 0, quantidade - 1);
}