/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * MÓDULO: PROGRAMA PRINCIPAL
 * DESCRIÇÃO: Coordena a execução do jogo de aventura baseado em estratégia gulosa
 *            para seleção de itens, com gerenciamento completo do fluxo de processamento
 * 
 * ARQUITETURA:
 *  - Entrada: Leitura de arquivo com configurações das fases
 *  - Processamento: Execução sequencial das fases com algoritmo guloso
 *  - Saída: Geração de relatório detalhado em arquivo
 * 
 * DEPENDÊNCIAS:
 *  - fases.h: Implementação das regras de cada fase
 *  - entradasaida.h: Manipulação de arquivos e dados de entrada/saída
 */

#include <stdio.h>
#include <stdlib.h>
#include "fases.h"
#include "entradasaida.h"

/**
 * FUNÇÃO PRINCIPAL
 * OBJETIVO: Orquestrar a execução completa do jogo, desde a leitura dos dados
 *           até a geração dos resultados finais
 * 
 * PARÂMETROS:
 *   @param quantidadeArgumentos: Contagem de argumentos da linha de comando
 *   @param argumentos: Vetor contendo os argumentos (entrada/saída)
 * 
 * FLUXO DE EXECUÇÃO:
 *   1. VALIDAÇÃO:
 *      - Verifica a quantidade e validade dos argumentos
 *      - Exibe mensagens de erro específicas quando necessário
 * 
 *   2. INICIALIZAÇÃO:
 *      - Carrega os dados das fases do arquivo de entrada
 *      - Prepara o arquivo de saída para redirecionamento
 * 
 *   3. PROCESSAMENTO:
 *      - Executa sequencialmente cada fase do jogo
 *      - Acumula os resultados parciais
 * 
 *   4. FINALIZAÇÃO:
 *      - Exibe o resultado consolidado
 *      - Libera recursos e restaura a saída padrão
 * 
 * CÓDIGOS DE RETORNO:
 *   - 0: Execução bem-sucedida
 *   - 1: Erro nos argumentos de linha de comando
 *   - 2: Falha na leitura do arquivo de entrada
 *   - 3: Falha na criação do arquivo de saída
 */

int main(int quantidadeArgumentos, char *argumentos[]) {
    
    // =============================================
    // 1. VALIDAÇÃO DOS ARGUMENTOS
    // =============================================
    
    if (quantidadeArgumentos != 3) {
        printf("\nUso correto:\n");
        printf("%s arquivo_entrada.txt arquivo_saida.txt\n\n", argumentos[0]);
        return 1;
    }

    // =============================================
    // 2. INICIALIZAÇÃO DO SISTEMA
    // =============================================

    FaseJogo listaDeFases[TOTAL_FASES];
    int totalDeFases = lerArquivoEntrada(argumentos[1], listaDeFases);
    

    if (totalDeFases == 0) {
        printf("\nErro: Nenhuma fase foi lida por estar fora do modelo!\n");
        return 2;
    }

    /* Preparação do arquivo de saída */

    FILE *arquivoSaida = freopen(argumentos[2], "w", stdout);
    
    if (arquivoSaida == NULL) {
        printf("\nErro: Não deu pra gerar um arquivo de saída\n");
        return 3;

    }

    // =============================================
    // 3. PROCESSAMENTO DAS FASES
    // =============================================


    /* Processamento de cada fase */

    for (int i = 0; i < totalDeFases; i++) {
        
        executarFase(&listaDeFases[i]);

        /* Espaçamento entre fases na saída */

        if (i < totalDeFases - 1) {

            printf("\n");

        }
    }


    // =============================================
    // 4. RESULTADOS FINAIS
    // =============================================

    fclose(arquivoSaida);
    
    /* Mensagem de confirmação no terminal */

    freopen("/dev/tty", "w", stdout);
    printf("\nProcesso completado!\n");
    printf("Resultados disponíveis em: %s\n\n", argumentos[2]);
    
    return 0;
}