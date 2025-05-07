#ifndef ITENS_H
#define ITENS_H

#define MAX_NOME 50
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    float peso;
    float valor;
    char tipo[MAX_TIPO];
    float valor_por_peso;
} Item;

void calcular_valor_por_peso(Item *item);
int comparar_itens(const void *a, const void *b);

#endif