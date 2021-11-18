CC=g++
CFLAGS= -std=c++17 -O2 -fopenmp

all: serial parallel parallel_all

serial:
		$(CC) $(CFLAGS) -o bin/serial.out src/serial.cpp

parallel:
		$(CC) $(CFLAGS) -o bin/parallel.out src/parallel.cpp

parallel_all:
		$(CC) $(CFLAGS) -o bin/parallel_all.out src/parallel_all.cpp
