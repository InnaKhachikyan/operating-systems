#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {

	char src_file[50];
	printf("Enter the file name: ");
	if(scanf("%49s", src_file) != 1) {
		perror("scanf");
		return 1;
	}

	int fd = open(src_file, O_RDONLY);
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

	printf("File size %jd \n", file_size);
	char buffer;
	for(off_t i = -1; i >= ((-1)*file_size); i--) {
		if(lseek(fd, i, SEEK_END) < 0) {
			perror("lseek");
			close(fd);
			return 1;
		}
		if(read(fd, &buffer, 1) < 0) {
			perror("read");
			close(fd);
			return 1;
		}
		if(write(1, &buffer, 1) != 1) {
			perror("write");
			close(fd);
			return 1;
		}
	}
	if(write(1, "\n", 1) != 1) {
		perror("write");
		close(fd);
		return 1;
	}

	close(fd);
	return 0;
}

