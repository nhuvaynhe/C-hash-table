CC = gcc
CFLAGS = -lm
DEPS = hash_table.h prime.h test.h
MAIN_OBJ = hash_table.o main.o prime.o
TEST_OBJ = test_hash_table.o test.o prime.o

# Detect the platform
ifeq ($(OS),Windows_NT)
    RM = del /f /q  # Use Windows delete command
    EXE = .exe      # Executable extension for Windows
else
    RM = rm -f      # Use Unix/Linux delete command
    EXE =           # No extension for Unix/Linux executables
endif

all: test$(EXE) ht$(EXE)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

ht$(EXE): $(MAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
test_hash_table.o: hash_table.c prime.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -DDEBUG=1

test$(EXE): $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -DDEBUG=1

clean:
	$(RM) *.o ht$(EXE) test$(EXE)
