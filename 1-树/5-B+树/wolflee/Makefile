CC=gcc
CFLAGS=-Wall -I.
DEPS = b_plus_tree.h
OBJ = b_plus_tree.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bptree: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *o bptree

run:
	./bptree

all: clean bptree run
