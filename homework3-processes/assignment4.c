#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

int main(void) {

	printf("***** ASSIGNMENT 4 *****\n");

	pid_t fork_pid, fork_pid2, wait_pid, wait_pid2;
	int estatus_child1, estatus_child2;

	fork_pid = fork();
	if(fork_pid == -1) {
		perror("Fork failed");
		return 1;
	}
	else if(fork_pid == 0) {
		printf("First child exits\n");
		exit(42);
	}
	else {
		fork_pid2 = fork();
		if(fork_pid2 == -1) {
			perror("Second fork failed");
			return 1;
		}
		else if(fork_pid2 == 0) {
			printf("Second child tries to open non-existing file\n");
			FILE *f = fopen("/this/file/does/not/exist.txt", "r");
			if (!f) {
    				perror("Intentional error");
    		//		kill(getpid(), SIGKILL); //process suicide
				exit(23);
			}
			exit(23);
		}
		else {
			wait_pid = waitpid(fork_pid, &estatus_child1, 0);
			if(wait_pid == -1) {
				perror("Waitpid failed");
				return 1;
			}
			wait_pid2 = waitpid(fork_pid2, &estatus_child2, 0);
			if(wait_pid2 == -1) {
				perror("Second waitpid failed");
				return 1;
			}

			if(WIFEXITED(estatus_child1)) {
				printf("Child 1 exited normally with status %d\n", WEXITSTATUS(estatus_child1));
			}
			else {
				printf("Something went wrong, child 1 exit status is %d\n", WEXITSTATUS(estatus_child1));
			}
			if(WIFEXITED(estatus_child2)) {
				printf("Child 2 exited normally with status %d\n", WEXITSTATUS(estatus_child2));
			}
			else {
				printf("Something went wrong, child 2 exit status is %d\n", WEXITSTATUS(estatus_child2));
			}
			printf("parent process done\n");
		}
	}
}

