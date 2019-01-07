but : snake

CC = gcc

CFLAGS = -Wall -ansi -pedantic -g -std=c99

OFILES = main.o \
	game.o \
    functions.o \
	menu.o

functions.o : functions.h

game.o : game.h main.h

main.o : functions.h main.h game.h

menu.o : menu.h functions.h main.h game.h

snake : $(OFILES)
		$(CC) $(CFLAGS) -o snake $(OFILES) -lgraph -lm

clean :
		-rm -f $(OFILES) snake

.PHONY : but clean
