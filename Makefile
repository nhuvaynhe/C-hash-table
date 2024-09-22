CC = gcc
CFLAGS = -lm 
DEPS = hash_table.h prime.h test.h
MAIN_OBJ = hash_table.o main.o prime.o
TEST_OBJ = test_hash_table.o test.o prime.o
all: test ht

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ht: $(MAIN_OBJ)
	gcc -o $@ $^ $(CFLAGS)
	
test_hash_table.o: hash_table.c prime.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -DDEBUG=1

test: $(TEST_OBJ)
	gcc -o $@ $^ $(CFLAGS) -DDEBUG=1

clean:
	rm -f *.o ht
