CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.
SRCDIR = .
BINDIR = ../bin

SOURCES = main.c fases.c itens.c regras.c io.c
OBJECTS = $(SOURCES:%.c=$(BINDIR)/%.o)
EXECUTABLE = $(BINDIR)/jogo_aventura

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(BINDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINDIR)/*.o $(EXECUTABLE)

run: all
	$(EXECUTABLE) ../entrada/entrada.txt ../saida/saida.txt

.PHONY: all clean run