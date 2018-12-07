but : snake

CC = gcc

CFLAGS = -Wall -ansi -pedantic -g

OFILES = main.o \
		functions.o

functions.o : functions.h

main.o : functions.h

snake : $(OFILES)
		$(CC) $(CFLAGS) -o snake $(OFILES) -lgraph

clean :
		-rm -f $(OFILES) snake

.PHONY : but clean