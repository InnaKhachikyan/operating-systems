#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>

int main(void) {

	int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1) {
		perror("open");
		return 1;
	}

	char buffer[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";	
	if(write(fd, buffer, sizeof(buffer)) != sizeof(buffer)) {
		perror("write");
		close(fd);
		return 1;
	}
	
	close(fd);

	fd = open("data.txt", O_RDWR);
	if(fd == -1) {
		perror("open");
		return 1;
	}

	off_t file_size = lseek(fd, 0, SEEK_END);
	if(file_size < 0) {
		perror("lseek");
		close(fd);
		return 1;
	}

	printf("Size of file is %jd\n", (intmax_t)file_size);

	if(ftruncate(fd, 10) < 0) {
		perror("ftruncate");
		close(fd);
		return 1;
	}

	if(lseek(fd, 0, SEEK_SET) < 0) {
		perror("lseek");
		close(fd);
		return 1;
	}
	off_t new_size = lseek(fd, 0, SEEK_END);
	if(new_size < 0) {
		perror("lseek");
		close(fd);
		return 1;
	}

	printf("File new size is %jd\n", (intmax_t)new_size);

	if(lseek(fd, 0, SEEK_SET) < 0) {
		perror("lseek");
		close(fd);
		return 1;
	}

	char *buf = (char*)malloc(sizeof(char)*((size_t)new_size+1));
	if(!buf) {
		perror("malloc");
		close(fd);
		return 1;
	}

	if(read(fd, buf, new_size) != (ssize_t)new_size) {
		perror("read");
		close(fd);
		free(buf);
		buf = NULL;
		return 1;
	}
	buf[new_size] = '\0';

	printf("%s\n", buf);

	free(buf);
	buf = NULL;
	close(fd);
	return 0;
}

