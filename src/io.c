#include "io.h"
#include "fases.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void trim_string(char *str) {
    int i = strlen(str) - 1;
    while (i >= 0 && isspace(str[i])) {
        str[i] = '\0';
        i--;
    }
}

int ler_arquivo_entrada(const char *nome_arquivo, Fase fases[]) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo de entrada");
        return 0;
    }

    char linha[MAX_LINHA];
    int fase_atual = -1;
    int num_fases = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        trim_string(linha);
        
        if (strstr(linha, "FASE:") == linha) {
            fase_atual++;
            num_fases++;
            sscanf(linha, "FASE: %[^\n]", fases[fase_atual].nome);
            fases[fase_atual].num_itens = 0;
        } 
        else if (strstr(linha, "CAPACIDADE:") == linha) {
            sscanf(linha, "CAPACIDADE: %f", &fases[fase_atual].capacidade);
        } 
        else if (strstr(linha, "REGRA:") == linha) {
            sscanf(linha, "REGRA: %s", fases[fase_atual].regra);
        } 
        else if (strstr(linha, "ITEM:") == linha) {
            Item item;
            char *token = strtok(linha, ",");
            sscanf(token, "ITEM: %[^\n]", item.nome);
            
            token = strtok(NULL, ",");
            sscanf(token, "%f", &item.peso);
            
            token = strtok(NULL, ",");
            sscanf(token, "%f", &item.valor);
            
            token = strtok(NULL, ",");
            sscanf(token, "%s", item.tipo);
            trim_string(item.tipo);
            
            fases[fase_atual].itens[fases[fase_atual].num_itens] = item;
            fases[fase_atual].num_itens++;
        }
    }

    fclose(arquivo);
    return num_fases;
}