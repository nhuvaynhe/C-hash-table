CC = gcc
CFLAGS = -lm
DEPS = hash_table.h
OBJ = hash_table.o main.o prime.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ht: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o ht
