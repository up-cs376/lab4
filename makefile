test1: test1.o
	gcc -o test1 test1.o

test1.o: test1.c
	gcc -c test1.c
