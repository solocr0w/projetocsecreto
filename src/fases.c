/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * IMPLEMENTAÇÃO DAS FASES DO JOGO
 * OBJETIVO: Processar cada fase usando estratégia gulosa
 */
#include "fases.h"
#include "regras.h"
#include "itens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Executa uma fase completa do jogo
 * @param fase Ponteiro para a estrutura contendo os dados da fase
 */
void executarFase(FaseJogo *fase) {

    // Aplica regras especiais e calcula relação valor/peso
    for (int indiceItem = 0; indiceItem < fase->quantidadeItens; indiceItem++) {

        if (strcmp(fase->regraEspecial, "MAGICOS_VALOR_DOBRADO") == 0) {

            fase->itensDisponiveis[indiceItem].valorReal = 
                ajustarValorMagico(&fase->itensDisponiveis[indiceItem]);

        } else if (strcmp(fase->regraEspecial, "SOBREVIVENCIA_DESVALORIZADA") == 0) {

            fase->itensDisponiveis[indiceItem].valorReal = 
                ajustarValorSobrevivencia(&fase->itensDisponiveis[indiceItem]);

        }

        calcularRelacaoValorPeso(&fase->itensDisponiveis[indiceItem]);
    }

    // Ordena itens por valor/peso (ordem decrescente)
    qsort(fase->itensDisponiveis, fase->quantidadeItens, sizeof(ItemJogo), comparadorItens);

    // Limita a 3 melhores itens se necessário
    int limiteItens = fase->quantidadeItens;

    if (strcmp(fase->regraEspecial, "TRES_MELHORES_VALOR_PESO") == 0) {

        limiteItens = (fase->quantidadeItens > 3) ? 3 : fase->quantidadeItens;
    }

    // Processa seleção de itens
    float capacidadeRestante = fase->capacidadeMochila;

    fase->lucroObtido = 0.0f;

    // Cabeçalho da fase
    printf("\n--- FASE: %s ---\n", fase->titulo);

    printf("Capacidade da mochila: %.2f kg\n", fase->capacidadeMochila);

    printf("Regra aplicada: %s\n", obterDescricaoRegra(fase->regraEspecial));


    // Seleção gulosa de itens
    for (int indiceItem = 0; indiceItem < limiteItens && capacidadeRestante > 0; indiceItem++) {

        int ehTecnologico = (strcmp(fase->regraEspecial, "TECNOLOGICOS_INTEIROS") == 0) && 
                          (strcmp(fase->itensDisponiveis[indiceItem].categoria, "tecnologico") == 0);
        
        if (ehTecnologico) {

            if (fase->itensDisponiveis[indiceItem].pesoKg <= capacidadeRestante) {

                printf("Pegou (inteiro) %s (%.2fkg, R$ %.2f)\n", 

                       fase->itensDisponiveis[indiceItem].identificacao,

                       fase->itensDisponiveis[indiceItem].pesoKg,

                       fase->itensDisponiveis[indiceItem].valorReal);
                
                fase->lucroObtido += fase->itensDisponiveis[indiceItem].valorReal;

                capacidadeRestante -= fase->itensDisponiveis[indiceItem].pesoKg;
            }
        } else {

            if (fase->itensDisponiveis[indiceItem].pesoKg <= capacidadeRestante) {

                printf("Pegou (inteiro) %s (%.2fkg, R$ %.2f)\n", 
                       fase->itensDisponiveis[indiceItem].identificacao,
                       fase->itensDisponiveis[indiceItem].pesoKg,
                       fase->itensDisponiveis[indiceItem].valorReal);
                
                fase->lucroObtido += fase->itensDisponiveis[indiceItem].valorReal;

                capacidadeRestante -= fase->itensDisponiveis[indiceItem].pesoKg;
            } else {

                float fracao = capacidadeRestante / fase->itensDisponiveis[indiceItem].pesoKg;

                float valorFracionado = fracao * fase->itensDisponiveis[indiceItem].valorReal;
                
                printf("Pegou (fracionado) %s (%.2fkg, R$ %.2f)\n", 
                       fase->itensDisponiveis[indiceItem].identificacao,
                       capacidadeRestante,
                       valorFracionado);
                
                fase->lucroObtido += valorFracionado;

                capacidadeRestante = 0.0f;
            }
        }
    }
    
    printf("Lucro da fase: R$ %.2f\n", fase->lucroObtido);
}