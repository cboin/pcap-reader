CC=clang
CFLAGS=-g -Wall -Werror -pedantic -lpcap
DEPS = *.h
OBJ = *.c 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
