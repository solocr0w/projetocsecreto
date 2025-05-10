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
 * Remove espaços e quebras de linha do final
 */

void removerEspacosExcedentes(char *texto) {
    
    int posicao = strlen(texto) - 1;
    
    while (posicao >= 0 && isspace(texto[posicao])) {
        texto[posicao] = '\0';
        posicao--;
    }
}

/**
 * Processa arquivo de entrada linha por linha
 */

int lerArquivoEntrada(const char *nomeArquivo, FaseJogo listaFases[]) {
    
    FILE *arquivoEntrada = fopen(nomeArquivo, "r");
    
    if (arquivoEntrada == NULL) {
        perror("Erro ao abrir arquivo");
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