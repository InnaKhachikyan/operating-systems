#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

int main (void) {

	printf("***** ASSIGNMENT 1 *****\n");

	pid_t fork_pid = fork();

	if(fork_pid == -1) {
		perror("Fork failed");
		return 1;
	}

	else if(fork_pid == 0) {
		printf("In child process, pid: %jd\n", (intmax_t)getpid());
		exit(0);
	}
	else {
		printf("In parent process, pid: %jd\n", (intmax_t)getpid());
	}

	return 0;
}

