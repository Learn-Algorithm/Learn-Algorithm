CC=gcc
CFLAGS=-Wall -I.
DEPS = splay_tree.h
OBJ = splay_tree.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

splaytree: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *o splaytree

run:
	./splaytree

all: clean splaytree run
