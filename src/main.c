#include <stdio.h>
#include <stdlib.h>
#include "fases.h"
#include "io.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <arquivo_entrada> <arquivo_saida>\n", argv[0]);
        return 1;
    }

    Fase fases[MAX_FASES];
    int num_fases = ler_arquivo_entrada(argv[1], fases);
    
    if (num_fases == 0) {
        printf("Nenhuma fase encontrada no arquivo de entrada.\n");
        return 1;
    }

    // Redireciona a saída para o arquivo
    freopen(argv[2], "w", stdout);

    float lucro_total = 0;
    for (int i = 0; i < num_fases; i++) {
        processar_fase(&fases[i]);
        lucro_total += fases[i].lucro;
    }

    printf("\nLucro total: R$ %.2f\n", lucro_total);

    // Restaura a saída padrão
    fclose(stdout);
    freopen("/dev/tty", "w", stdout); // Linux
    // freopen("CON", "w", stdout); // Windows

    printf("Processamento concluido. Resultados salvos em %s\n", argv[2]);
    return 0;
}