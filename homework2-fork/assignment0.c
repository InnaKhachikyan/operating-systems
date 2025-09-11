#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {

	printf("***** ASSIGNMENT 0 *****\n");
	pid_t fork_pid = fork();
	if(fork_pid == -1) {
		perror("First fork failed!");
		return -1;
	}
	fork_pid = fork();
	if(fork_pid == -1) {
		perror("Second fork failed!");
		return -1;
	}
	fork_pid = fork();
	if(fork_pid == -1) {
		perror("Third fork failed!");
		return -1;
	}
	return 0;

}
