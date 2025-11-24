



all:
	gcc -pthread task1.c -o task1
	gcc -pthread task2.c -o task2
	gcc -pthread task3.c -o task3
	gcc -pthread task4.c -o task4
	gcc -pthread task5.c -o task5

test:
	./task1 nosync
	./task1 mutex
	./task1 spin
	time ./task2 mutex short
	time ./task2 spin short
	time ./task2 mutex long
	time ./task2 spin long
	./task3
	./task4
	./task5
