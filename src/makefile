# =============================================
# UNIVERSIDADE PRESBITERIANA MACKENZIE 
# GRUPO: BRUNO GERMANETTI RAMALHO - 10426491
#        MIGUEL PINEIRO CORATOLO SIMOES - 10427085
#
# CONFIGURAÇÃO DE COMPILAÇÃO
# =============================================

COMPILADOR = gcc
OPCOES = -Wall -Wextra -std=c99 -I.
DIR_FONTES = src
DIR_BIN = bin
DIR_ENTRADA = entrada
DIR_SAIDA = saida

ARQUIVOS_FONTE = $(wildcard $(DIR_FONTES)/*.c)
OBJETOS = $(patsubst $(DIR_FONTES)/%.c,$(DIR_BIN)/%.o,$(ARQUIVOS_FONTE))
EXECUTAVEL = $(DIR_BIN)/jogo_aventura

# =============================================
# REGRAS DE COMPILAÇÃO
# =============================================

.PHONY: tudo limpar executar

tudo: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(COMPILADOR) $(OPCOES) $(OBJETOS) -o $@

$(DIR_BIN)/%.o: $(DIR_FONTES)/%.c | $(DIR_BIN)
	$(COMPILADOR) $(OPCOES) -c $< -o $@

$(DIR_BIN):
	mkdir -p $(DIR_BIN)

limpar:
	rm -rf $(DIR_BIN)/*.o $(EXECUTAVEL)

executar: tudo
	@mkdir -p $(DIR_SAIDA)
	./$(EXECUTAVEL) $(DIR_ENTRADA)/entrada.txt $(DIR_SAIDA)/saida.txt

# =============================================
# COMANDOS ÚTEIS
# =============================================

ajuda:
	@echo "Comandos disponíveis:"
	@echo "  make tudo     - Compila o programa"
	@echo "  make limpar   - Remove arquivos gerados"
	@echo "  make executar - Executa o programa"
	@echo "  make ajuda    - Mostra esta mensagem"