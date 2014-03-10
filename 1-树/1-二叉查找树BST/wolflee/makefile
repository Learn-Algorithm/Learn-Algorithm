CC=gcc
CFLAGS=-Wall -I.
DEPS = binary_search_tree.h
OBJ = binary_search_tree.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bst: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *o bst
