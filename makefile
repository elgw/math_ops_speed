CC=gcc -std=gnu99 -Wall -Wextra
CFLAGS=-O3 -march=native
LDFLAGS=-lm -flto

ops: ops.c makefile
	$(CC) ops.c $(CFLAGS) $(LDFLAGS) -o ops
	$(CC) ops.c $(CFLAGS) -funsafe-math-optimizations $(LDFLAGS) -o ops_unsafe
