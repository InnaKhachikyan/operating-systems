#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define SIZE 16

int* alloc_child1;
double* alloc_child2;
char* alloc_parent;

void cleanup_for_child1(void) {
	free(alloc_child1);
	alloc_child1 = NULL;
	printf("Child 1 cleanup done\n");
}

void cleanup_for_child2(void) {
	free(alloc_child2);
	alloc_child2 = NULL;
	printf("Child 2 cleanup done\n");
}

void cleanup_for_parent(void) {
	free(alloc_parent);
	alloc_parent = NULL;
	printf("Parent cleanup done\n");
}

int main(void) {

	printf("***** ASSIGNMENT 3 *****\n");
	pid_t fork_pid = fork();

	if(fork_pid == -1) {
		perror("Fork failed");
		return 1;
	}

	else if(fork_pid == 0) {
		atexit(cleanup_for_child1);
		alloc_child1 = (int*)malloc(sizeof(int)*SIZE);
		if(!alloc_child1) {
			perror("Malloc failed");
			return 1;
		}
		printf("In child process 1 calling exit\n");
		exit(0);
	}

	else {
		pid_t fork_pid2 = fork();
		if(fork_pid2 == -1) {
			perror("Second fork failed");
			return 1;
		}

		else if(fork_pid2 == 0) {
			atexit(cleanup_for_child2);
			alloc_child2 = (double*)malloc(sizeof(double)*SIZE);
			if(!alloc_child2) {
				perror("Malloc failed");
				return 1;
			}
			printf("In child process 2 calling exit\n");
			exit(0);
		}

		else {
			atexit(cleanup_for_parent);
			alloc_parent = (char*)malloc(sizeof(char)*SIZE);
			if(!alloc_parent) {
				perror("Malloc failed");
				return 1;
			}
			printf("In parent process calling exit\n");
			exit(0);
		}
	}

	return 0;
}
