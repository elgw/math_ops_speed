
cc=gcc

ops:
	$(cc) ops.c -O3 -lm -march=native -o ops 
