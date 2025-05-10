/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * PROGRAMA PRINCIPAL - JOGO DE AVENTURA
 * OBJETIVO: Implementar um jogo de escolha de itens usando estratégia gulosa
 * VERSÃO: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include "fases.h"
#include "io.h"

/**
 * Função principal
 * @param quantidadeArgumentos Número de argumentos da linha de comando
 * @param argumentos Vetor contendo os argumentos
 * @return Código de status (0 = sucesso)
 */
int main(int quantidadeArgumentos, char *argumentos[]) {
    
    /* Verificação inicial dos argumentos */
    
    if (quantidadeArgumentos != 3) {
        printf("\nUso correto:\n");
        printf("%s arquivo_entrada.txt arquivo_saida.txt\n\n", argumentos[0]);
        return 1;
    }

    FaseJogo listaDeFases[TOTAL_FASES];
    int totalDeFases = lerArquivoEntrada(argumentos[1], listaDeFases);
    
    /* Validação do arquivo de entrada */

    if (totalDeFases == 0) {
        printf("\nErro: Não foi possível ler nenhuma fase do arquivo!\n");
        return 2;
    }

    /* Preparação do arquivo de saída */

    FILE *arquivoSaida = freopen(argumentos[2], "w", stdout);
    
    if (arquivoSaida == NULL) {
        printf("\nErro: Não foi possível criar o arquivo de saída!\n");
        return 3;

    }

    float lucroTotalAcumulado = 0.0f;

    /* Processamento de cada fase */

    for (int i = 0; i < totalDeFases; i++) {
        
        executarFase(&listaDeFases[i]);

        lucroTotalAcumulado += listaDeFases[i].lucroObtido;
        
        /* Espaçamento entre fases na saída */

        if (i < totalDeFases - 1) {

            printf("\n");

        }
    }

    /* Resultado final */

    printf("\n\nLUCRO TOTAL DO JOGO: R$ %.2f\n", lucroTotalAcumulado);

    /* Finalização */

    fclose(arquivoSaida);
    
    /* Mensagem de confirmação no terminal */

    freopen("/dev/tty", "w", stdout);
    printf("\nProcesso concluído com sucesso!\n");
    printf("Verifique os resultados em: %s\n\n", argumentos[2]);
    
    return 0;
}