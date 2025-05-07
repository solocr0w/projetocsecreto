#include "fases.h"
#include "regras.h"
#include "itens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void processar_fase(Fase *fase) {
    // Aplica regras especiais e calcula valor por peso
    for (int i = 0; i < fase->num_itens; i++) {
        if (strcmp(fase->regra, "MAGICOS_VALOR_DOBRADO") == 0) {
            fase->itens[i].valor = aplicar_regra_magicos(&fase->itens[i]);
        } else if (strcmp(fase->regra, "SOBREVIVENCIA_DESVALORIZADA") == 0) {
            fase->itens[i].valor = aplicar_regra_sobrevivencia(&fase->itens[i]);
        }
        calcular_valor_por_peso(&fase->itens[i]);
    }

    // Ordena itens por valor/peso
    qsort(fase->itens, fase->num_itens, sizeof(Item), comparar_itens);

    // Limita a 3 melhores itens se necessário
    int limite_itens = fase->num_itens;
    if (strcmp(fase->regra, "TRES_MELHORES_VALOR_PESO") == 0) {
        limite_itens = (fase->num_itens > 3) ? 3 : fase->num_itens;
    }

    // Seleciona itens usando estratégia gulosa
    float capacidade_restante = fase->capacidade;
    fase->lucro = 0;

    printf("\n--- FASE: %s ---\n", fase->nome);
    printf("Capacidade da mochila: %.2f kg\n", fase->capacidade);
    printf("Regra aplicada: %s\n", traduzir_regra(fase->regra));

    for (int i = 0; i < limite_itens && capacidade_restante > 0; i++) {
        int tecnologico = (strcmp(fase->regra, "TECNOLOGICOS_INTEIROS") == 0) && 
                         (strcmp(fase->itens[i].tipo, "tecnologico") == 0);
        
        if (tecnologico) {
            if (fase->itens[i].peso <= capacidade_restante) {
                printf("Pegou (inteiro) %s (%.2fkg, R$ %.2f)\n", 
                       fase->itens[i].nome, fase->itens[i].peso, fase->itens[i].valor);
                fase->lucro += fase->itens[i].valor;
                capacidade_restante -= fase->itens[i].peso;
            }
        } else {
            if (fase->itens[i].peso <= capacidade_restante) {
                printf("Pegou (inteiro) %s (%.2fkg, R$ %.2f)\n", 
                       fase->itens[i].nome, fase->itens[i].peso, fase->itens[i].valor);
                fase->lucro += fase->itens[i].valor;
                capacidade_restante -= fase->itens[i].peso;
            } else {
                float fracao = capacidade_restante / fase->itens[i].peso;
                float valor_fracao = fracao * fase->itens[i].valor;
                printf("Pegou (fracionado) %s (%.2fkg, R$ %.2f)\n", 
                       fase->itens[i].nome, capacidade_restante, valor_fracao);
                fase->lucro += valor_fracao;
                capacidade_restante = 0;
            }
        }
    }
    printf("Lucro da fase: R$ %.2f\n", fase->lucro);
}