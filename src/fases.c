/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * MÓDULO: IMPLEMENTAÇÃO DAS FASES DO JOGO
 * DESCRIÇÃO: Contém a lógica central do jogo, implementando o algoritmo guloso
 *            para seleção de itens em cada fase, considerando as regras especiais.
 * 
 * PRINCIPAIS FUNCIONALIDADES:
 *  - Aplicação de regras especiais aos itens
 *  - Ordenação estratégica dos itens
 *  - Seleção gulosa considerando restrições
 *  - Cálculo do lucro obtido em cada fase
 */

#include "fases.h"
#include "regras.h"
#include "itens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * FUNÇÃO: executarFase
 * OBJETIVO: Implementa o núcleo do algoritmo guloso para uma fase do jogo
 * 
 * PARÂMETROS:
 *   @param fase: Ponteiro para a estrutura FaseJogo contendo todos os dados da fase
 * 
 * PROCESSAMENTO PRINCIPAL:
 *   1. PRÉ-PROCESSAMENTO:
 *      - Aplica regras especiais que modificam valores dos itens
 *      - Calcula a relação valor/peso para cada item
 *   
 *   2. ORDENAÇÃO:
 *      - Organiza os itens por valor/peso (decrescente)
 *      - Considera limitações de quantidade quando aplicável
 *   
 *   3. SELEÇÃO GULOSA:
 *      - Percorre itens ordenados selecionando os mais valiosos primeiro
 *      - Trata casos especiais (itens não-fracionáveis)
 *      - Calcula lucro obtido e capacidade restante
 * 
 *   4. SAÍDA:
 *      - Exibe os itens selecionados e o resultado da fase
 * 
 * REGRAS ESPECIAIS IMPLEMENTADAS:
 *   - MAGICOS_VALOR_DOBRADO: Dobra o valor de itens mágicos
 *   - SOBREVIVENCIA_DESVALORIZADA: Reduz 20% do valor de itens de sobrevivência
 *   - TECNOLOGICOS_INTEIROS: Itens tecnológicos não podem ser fracionados
 *   - TRES_MELHORES_VALOR_PESO: Limita seleção aos 3 itens mais eficientes
 */

void executarFase(FaseJogo *fase) {

    // =============================================
    // 1. APLICAÇÃO DAS REGRAS ESPECIAIS
    // =============================================

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

    // =============================================
    // 2. ORDENAÇÃO DOS ITENS
    // =============================================

    arrumarItens(fase->itensDisponiveis, fase->quantidadeItens);

    // Limita a 3 melhores itens se necessário
    int limiteItens = fase->quantidadeItens;

    if (strcmp(fase->regraEspecial, "TRES_MELHORES_VALOR_PESO") == 0) {

        limiteItens = (fase->quantidadeItens > 3) ? 3 : fase->quantidadeItens;
    }

    // =============================================
    // 3. SELEÇÃO GULOSA
    // =============================================

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
    
        // =============================================
        // 4. RESULTADO FINAL
        // =============================================
        
    printf("Lucro da fase: R$ %.2f\n", fase->lucroObtido);
}