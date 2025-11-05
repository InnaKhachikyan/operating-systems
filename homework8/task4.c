/*
lseek with SEEK_CUR
When we open a file, the cursor is typically at the beginning of the file (position 0), even if the file was opened in the append mode (to show that I added a small print in the beginning). However, the OS guarantees that the written bytes will be appended to the existing. Each time we call write (after opening with O_APPEND), the kernel under the hood does lseek with SEEK_END then write operation. So each time before writing anything to the file, OS (to ensure append and not allow overwriting), moves the cursor to the end, then writes to the file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <inttypes.h>

#define LINE_MAX_SIZE 50

int main(void) {

	int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if(fd == -1) {
		perror("open");
		return 1;
	}

	off_t current = lseek(fd, 0, SEEK_CUR);
	printf("*** Current position: %jd ***\n", (intmax_t)current);

	char fixed[] = "PID=";
	if(write(fd, fixed, 4) < 0) {
		perror("write");
		close(fd);
		return 1;
	}
	pid_t pid = getpid();
	char pid_buf[16];
	int idx = 0;
	while(pid > 0) {
		int digit = pid % 10;
		pid_buf[idx++] = '0' + digit;
		pid = pid/10;
	}
	//reverse
	for(int i = 0; i < idx/2; i++) {
		char tmp = pid_buf[i];
		pid_buf[i] = pid_buf[idx-i-1];
		pid_buf[idx-i-1] = tmp;
	}

	pid_buf[idx] = ':';
	pid_buf[idx + 1] = ' ';

	if(write(fd, pid_buf, idx + 2) < 0) {
		perror("write");
		close(fd);
		return 1;
	}

	char buffer;
	ssize_t r_bytes;
	while(1) {
		r_bytes = read(0, &buffer, 1);
		if(r_bytes == 0) {
			break;
		}
		if(r_bytes < 1) {
			perror("read");
			close(fd);
			return 1;
		}
		if(buffer == '\n') {
			break;
		}
		if(write(fd, &buffer, 1) < 0) {
			perror("write");
			close(fd);
			return 1;
		}
	}
	buffer = '\n';
	if(write(fd, &buffer, 1) < 0) {
		perror("write");
		close(fd);
		return 1;
	}

	current = lseek(fd, 0, SEEK_CUR);
	printf("*** Updated current position at %jd ***\n", (intmax_t)current);

	close(fd);
	return 0;
}

