# =============================================
# CONFIGURAÇÃO PARA CODESPACES
# =============================================
COMPILADOR = gcc
OPCOES = -Wall -Wextra -std=c99 -I.
PASTA_OBJ = ../bin
EXECUTAVEL = $(PASTA_OBJ)/jogo_aventura

# Lista todos os .c na pasta atual
ARQUIVOS_C = $(wildcard *.c)
OBJETOS = $(patsubst %.c,$(PASTA_OBJ)/%.o,$(ARQUIVOS_C))

# =============================================
# REGRAS PRINCIPAIS
# =============================================
.PHONY: tudo limpar executar

tudo: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(COMPILADOR) $(OPCOES) $(OBJETOS) -o $@

$(PASTA_OBJ)/%.o: %.c | $(PASTA_OBJ)
	$(COMPILADOR) $(OPCOES) -c $< -o $@

$(PASTA_OBJ):
	mkdir -p $(PASTA_OBJ)

limpar:
	rm -rf $(PASTA_OBJ)/*.o $(EXECUTAVEL)

executar: tudo
	@mkdir -p ../saida
	./$(EXECUTAVEL) ../entrada/entrada.txt ../saida/saida.txt

# =============================================
# REGRA DE AJUDA
# =============================================
ajuda:
	@echo "Comandos disponíveis:"
	@echo "  make tudo     - Compila o programa"
	@echo "  make limpar   - Remove arquivos gerados"
	@echo "  make executar - Executa o programa"
	@echo "  make ajuda    - Mostra esta mensagem"