output: 2.c master.c
	mpicc -o output 2.c master.c xor.c

run: output
	mpirun -np 21 output