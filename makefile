CC = gcc

EXECUTABLES = main

FLAGS        = # -std=gnu99 -Iinclude
CFLAGS       = -fPIC -shared -g #-pedantic -Wall -Wextra -ggdb3
LDFLAGS      = -shared


all: $(EXECUTABLES)

main: idDb.o avl.o trie.o minHeap.o

minHeap.o: minHeap.h
avl.o: avl.h
trie.o: trie.h
idDb.o: idDb.h
main.o: avl.h trie.h minHeap.h idDb.h

clean:
	rm -f core *.o $(EXECUTABLES) a.out

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

main: main.o
	$(CC) $(CFLAGS) -o main main.o idDb.o avl.o trie.o minHeap.o

main.so: main.o 
	gcc -o main.so main.o idDb.o avl.o trie.o minHeap.o -shared


