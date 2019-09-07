
cc=gcc -std=gnu99 -Wall
cflags=-O3 -march=native 
ldflags=-lm -flto

ops:
	$(cc) ops.c $(cflags) $(ldflags) -o ops 
	$(cc) ops.c $(cflags) -funsafe-math-optimizations $(ldflags) -o ops_unsafe
