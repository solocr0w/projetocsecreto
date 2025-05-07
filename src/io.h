#ifndef IO_H
#define IO_H

#include "fases.h"

#define MAX_LINHA 200

void trim_string(char *str);
int ler_arquivo_entrada(const char *nome_arquivo, Fase fases[]);

#endif