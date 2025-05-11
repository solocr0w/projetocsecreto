/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * IMPLEMENTAÇÃO DA MANIPULAÇÃO DE ARQUIVOS
 */

#include "entradasaida.h"
#include "fases.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * FUNÇÃO: removerEspacosExcedentes
 * OBJETIVO: Remove espaços em branco, tabs e quebras de linha do final de uma string
 * 
 * PARÂMETROS:
 *   @param texto: Ponteiro para a string a ser processada (modificada in-place)
 * 
 * OPERAÇÃO:
 *   1. Localiza o final da string através de strlen()
 *   2. Percorre a string de trás para frente enquanto encontra caracteres brancos
 *   3. Substitui cada caractere branco por '\0' até encontrar um caractere visível
 * 
 * OBSERVAÇÕES:
 *   - Modifica a string original diretamente
 *   - Considera todos os tipos de espaços definidos por isspace()
 *   - Fundamental para o correto parsing das linhas do arquivo
 */

void removerEspacosExcedentes(char *texto) {
    
    int posicao = strlen(texto) - 1;
    
    while (posicao >= 0 && isspace(texto[posicao])) {
        texto[posicao] = '\0';
        posicao--;
    }
}

/**
 * FUNÇÃO: lerArquivoEntrada
 * OBJETIVO: Carrega e interpreta o arquivo de configuração das fases do jogo
 * 
 * PARÂMETROS:
 *   @param nomeArquivo: Caminho do arquivo a ser lido
 *   @param listaFases: Array de estruturas FaseJogo para armazenar os dados
 * 
 * RETORNO:
 *   - Número de fases carregadas com sucesso
 *   - 0 em caso de falha na leitura
 * 
 * LÓGICA DE OPERAÇÃO:
 *   1. Abertura do arquivo em modo leitura com tratamento de erros
 *   2. Leitura linha por linha do arquivo:
 *      a) Identificação de marcadores (FASE:, CAPACIDADE:, etc.)
 *      b) Extração dos dados usando sscanf() com padrões específicos
 *      c) Armazenamento na estrutura correspondente
 *   3. Processamento de itens com divisão por tokens
 *   4. Fechamento seguro do arquivo
 * 
 * ESTRUTURA DO ARQUIVO ESPERADO:
 *   FASE: <nome>
 *   CAPACIDADE: <float>
 *   REGRA: <string>
 *   ITEM: <nome>, <peso>, <valor>, <tipo>
 * 
 */

int lerArquivoEntrada(const char *nomeArquivo, FaseJogo listaFases[]) {
    
    FILE *arquivoEntrada = fopen(nomeArquivo, "r");
    
    if (arquivoEntrada == NULL) {

        perror("Erro tentando abrir o arquivo, verifique a entrada");
        
        return 0;
    }

    char linha[TAMANHO_MAXIMO_LINHA];

    int indiceFase = -1;
    int contadorFases = 0;

    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
        
        removerEspacosExcedentes(linha);
        
        if (strstr(linha, "FASE:") == linha) {

            indiceFase++;
            contadorFases++;
            sscanf(linha, "FASE: %[^\n]", listaFases[indiceFase].titulo);
            listaFases[indiceFase].quantidadeItens = 0;
        
        } else if (strstr(linha, "CAPACIDADE:") == linha) {
            sscanf(linha, "CAPACIDADE: %f", &listaFases[indiceFase].capacidadeMochila);
        
        } else if (strstr(linha, "REGRA:") == linha) {

            sscanf(linha, "REGRA: %s", listaFases[indiceFase].regraEspecial);
        
        } else if (strstr(linha, "ITEM:") == linha) {
            
            ItemJogo novoItem;

            char *pedaco = strtok(linha, ",");
            
            sscanf(pedaco, "ITEM: %[^\n]", novoItem.identificacao);
            
            pedaco = strtok(NULL, ",");

            sscanf(pedaco, "%f", &novoItem.pesoKg);
            
            pedaco = strtok(NULL, ",");

            sscanf(pedaco, "%f", &novoItem.valorReal);
            
            pedaco = strtok(NULL, ",");

            sscanf(pedaco, "%s", novoItem.categoria);
            removerEspacosExcedentes(novoItem.categoria);
            
            listaFases[indiceFase].itensDisponiveis[listaFases[indiceFase].quantidadeItens] = novoItem;

            listaFases[indiceFase].quantidadeItens++;
        }
    }

    fclose(arquivoEntrada);
    return contadorFases;
}