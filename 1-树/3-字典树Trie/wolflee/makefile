CC=gcc
CFLAGS=-Wall -I.
DEPS = trie.h
OBJ = trie.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

trie: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *o trie

run:
	./trie

all: clean trie run
