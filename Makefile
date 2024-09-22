CC = gcc
CFLAGS = 
DEPS = hash_table.h
OBJ = hash_table.o main.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

ht: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -f *.o ht
