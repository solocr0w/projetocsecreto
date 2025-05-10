/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * IMPLEMENTAÇÃO DOS ITENS
 */
#include "itens.h"
#include <string.h>

int comparadorItens(const void *itemA, const void *itemB) {
    
    const ItemJogo *primeiro = (const ItemJogo *)itemA;
    const ItemJogo *segundo = (const ItemJogo *)itemB;
    
    if (primeiro->relacaoValorPeso > segundo->relacaoValorPeso) return -1;
    if (primeiro->relacaoValorPeso < segundo->relacaoValorPeso) return 1;
    
    return 0;
}

void calcularRelacaoValorPeso(ItemJogo *item) {
    
    if (item->pesoKg > 0.01f) {
        item->relacaoValorPeso = item->valorReal / item->pesoKg;
    } else {
        item->relacaoValorPeso = 0.0f;
    }
}
