



all:
	gcc -pthread task1.c -o task1
	gcc -pthread task2.c -o task2


test:
	./task1 nosync
	./task1 mutex
	./task1 spin
	time ./task2 mutex short
	time ./task2 spin short
	time ./task2 mutex long
	time ./task2 spin long

