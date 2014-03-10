CC=gcc
CFLAGS=-Wall -I.
DEPS = avl.h
OBJ = avl.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

avl: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *o avl
