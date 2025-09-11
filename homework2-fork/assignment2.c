#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {

	printf("***** ASSIGNMENT 2 *****\n");

	pid_t fork_pid = fork();
	if(fork_pid == -1) {
		perror("Fork failed!\n");
		return -1;
	}

	else if(fork_pid == 0) {
		int exec_ret = execl("/usr/bin/ls", "ls", NULL);
		if(exec_ret == -1) {
			perror("exec failed\n");
			return -1;
		}
	}

	else {
		pid_t fork_pid2 = fork();
		if(fork_pid2 == -1) {
			perror("Fork failed\n");
			return -1;
		}
		else if(fork_pid2 == 0) {
			int exec_ret2 = execl("/usr/bin/date", "date", NULL);
                	if(exec_ret2 == -1) {
                        	perror("exec 2 failed\n");
                        	return -1;
                	}
		}
		else {

			while(wait(NULL) > -1) {
			}
			printf("Parent process done\n");
		}
	}
	return 0;
}
