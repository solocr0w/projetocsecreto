#include "itens.h"
#include <string.h>

void calcular_valor_por_peso(Item *item) {
    if (item->peso > 0) {
        item->valor_por_peso = item->valor / item->peso;
    } else {
        item->valor_por_peso = 0;
    }
}

int comparar_itens(const void *a, const void *b) {
    const Item *item1 = (const Item *)a;
    const Item *item2 = (const Item *)b;
    
    if (item1->valor_por_peso > item2->valor_por_peso) return -1;
    if (item1->valor_por_peso < item2->valor_por_peso) return 1;
    return 0;
}