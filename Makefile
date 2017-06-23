# Makfile for stringlist & tests
# Jim Mahoney |  cs.marlboro.edu | MIT License | summer 2017

CC=gcc -O2

all: test

test: test.o stringlist.o
	$(CC) test.o stringlist.o -o test

test.o: test.c stringlist.h
	$(CC) -c test.c

stringlist: stringlist.o
	$(CC) stringlist.o -o stringlist

stringlist.o: stringlist.c stringlist.h
	$(CC) -c stringlist.c

clean:
	rm -f *.o

