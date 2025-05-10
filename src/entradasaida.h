/**
 * UNIVERSIDADE PRESBITERIANA MACKENZIE 
 * GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
 *        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
 *
 * MANIPULAÇÃO DE ARQUIVOS
 */

#ifndef MANIPULACAO_ARQUIVOS_H

#define MANIPULACAO_ARQUIVOS_H

#include "fases.h"

#define TAMANHO_MAXIMO_LINHA 350

void removerEspacosExcedentes(char *texto);


int lerArquivoEntrada(const char *nomeArquivo, FaseJogo listaFases[]);

#endif