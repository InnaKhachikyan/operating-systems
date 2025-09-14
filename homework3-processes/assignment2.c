#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {

	printf("***** ASSIGNMENT 2 *****\n");

	int estatus_child1, estatus_child2;
	pid_t wait_pid, wait_pid2;

	pid_t fork_pid = fork();


	if(fork_pid == -1) {
		perror("Fork failed");
		return 1;
	}

	else if(fork_pid == 0) {
		printf("In child process, pid %jd\n", (intmax_t)getpid());
		exit(23);
	}
	else {
		wait_pid = wait(&estatus_child1);

	}
		
	pid_t fork_pid2 = fork();

	if(fork_pid2 == -1) {
		perror("Fork failed");
		return 1;
	}

	else if(fork_pid2 == 0) {
		printf("In child process 2, pid %jd\n", (intmax_t)getpid());
		exit(42);
	}
	else {
		printf("Parent waits for the second child\n");
		wait_pid2 = waitpid(fork_pid2, &estatus_child2,0);
		printf("After waitpid\n");
		if(WIFEXITED(estatus_child1)) {
			printf("First child with pid %jd exited normally with status %d\n", (intmax_t)wait_pid, WEXITSTATUS(estatus_child1));
		}
		if(WIFEXITED(estatus_child2)) {
			printf("Second child with pid %jd exited normally with status %d\n", (intmax_t)wait_pid2, WEXITSTATUS(estatus_child2));
		}
	}
	return 0;
}



