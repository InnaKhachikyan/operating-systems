#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SIZE 16

int* alloc0;
double* alloc1;
char* alloc2;

void cleanup_for_0(void) {
	free(alloc0);
	alloc0 = NULL;
	printf("Alloc 0 cleanup done\n");
}

void cleanup_for_1(void) {
	free(alloc1);
	alloc1 = NULL;
	printf("Alloc 1 cleanup done\n");
}

void cleanup_for_2(void) {
	free(alloc2);
	alloc2 = NULL;
	printf("Alloc 2 cleanup done\n");
}

int main(void) {

	printf("***** ASSIGNMENT 3 *****\n");

	alloc0 = (int*)malloc(sizeof(int)*SIZE);
	if(!alloc0) {
		perror("Malloc failed");
		exit(1);
	}
	atexit(cleanup_for_0);

	alloc1 = (double*)malloc(sizeof(double)*SIZE);
	if(!alloc1) {
		perror("Malloc failed");
		exit(1);
	}
	atexit(cleanup_for_1);

	alloc2 = (char*)malloc(sizeof(char)*SIZE);
	if(!alloc2) {
		perror("Malloc failed");
		exit(1);
	}
	atexit(cleanup_for_2);

	pid_t fork_pid = fork();
	if(fork_pid == -1) {
		perror("Fork failed");
		exit(1);
	}
	else if(fork_pid == 0) {
		printf("Child process exits without atexit\n");
		_exit(0);
	}
	else {
		printf("Parent process exits, expected output: functions registered with atexit\n");
		exit(0);
	}
	return 0;
}
