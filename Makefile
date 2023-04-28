CC = gcc
CFLAGS0 = -g
CFLAGS1 = -g -fsanitize=address,leak,undefined
CFLAGS2 = -g -fsanitize=memory,undefined

COMMON = Pokedex.c

.PHONY: all
all: main

main: runPokedex.c Pokedex.c
	$(CC) $(CFLAGS0) -o main runPokedex.c Pokedex.c

.PHONY: clean
clean:
	rm -rf main *.dSYM
