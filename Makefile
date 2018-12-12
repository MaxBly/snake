but : snake

CC = gcc

CFLAGS = -Wall -ansi -pedantic -g -std=c99

OFILES = main.o \
		game.o \
		functions.o

functions.o : functions.h

game.o : game.h main.h

main.o : functions.h main.h

snake : $(OFILES)
		$(CC) $(CFLAGS) -o snake $(OFILES) -lgraph

clean :
		-rm -f $(OFILES) snake

.PHONY : but clean