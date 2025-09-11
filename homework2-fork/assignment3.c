#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {

	printf("***** ASSIGNMENT 3 *****\n");

	pid_t fork_pid = fork();

	if(fork_pid == -1) {
		perror("Fork failed\n");
		return -1;
	}

	else if(fork_pid == 0) {
		int exec_ret = execl("/usr/bin/echo", "echo", "Hello from the child process", NULL);
		if(exec_ret == -1) {
			perror("Exec failed\n");
			return -1;
		}
	}

	else {
		wait(NULL);
		printf("Parent process done\n");
	}
	return 0;
}
