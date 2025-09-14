#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {

	printf("***** ASSIGNMENT 5 *****\n");
/*	sleep(5);
	pid_t fork_pid = fork();
	if(fork_pid == -1) {
		perror("Fork failed");
		return 1;
	}

	else if(fork_pid == 0) {
		printf("Child process with pid %jd done\n", (intmax_t)getpid());
		exit(0);
	}
	else {
		printf("Parent process sleeps\n");
		sleep(30);
		printf("Parent process done\n");
	}
*/
	pid_t wait_pid;
	int status;
	pid_t fork_pid = fork();
        if(fork_pid == -1) {
                perror("Fork failed");
                return 1;
        }

	else if(fork_pid == 0) {
		printf("Child process with pid %jd done\n", (intmax_t)getpid());
		exit(0);
	}
	else {
		printf("Parent waits for the child\n");
		wait_pid = wait(&status);
		if(wait_pid == -1) {
			perror("Wait failed");
			return 1;
		}
		if(WIFEXITED(status)) {
			printf("Reaped child with pid %jd exit status %d\n", (intmax_t)fork_pid, WEXITSTATUS(status));
		}
		else {
			printf("Something went wrong\n");
			return 1;
		}

		printf("Parent process done\n");
	}
	return 0;
}
