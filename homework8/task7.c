#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 50
#define CHUNK_SIZE 10

int main(void) {

	printf("Enter the first file path: ");
	char buffer1[MAX_BUFFER_SIZE];
	char buffer2[MAX_BUFFER_SIZE];
	if(scanf("%49s", buffer1) != 1) {
		perror("scanf");
		return 1;
	}

	printf("Enter the second file path: ");
	if(scanf("%49s", buffer2) != 1) {
		perror("scanf");
		return 1;
	}

	int fd1 = open(buffer1, O_RDONLY);
	if(fd1 == -1) {
		perror("open");
		return 1;
	}

	int fd2 = open(buffer2, O_RDONLY);
	if(fd2 == -1) {
		perror("open");
		close(fd1);
		return 1;
	}
	char buf1[CHUNK_SIZE];
	char buf2[CHUNK_SIZE];

	ssize_t read_bytes1, read_bytes2;

	size_t tracker = 0;
	while(1) {
		read_bytes1 = read(fd1, buf1, CHUNK_SIZE);
		if(read_bytes1 < 0) {
			perror("read");
			close(fd1);
			close(fd2);
			return 1;
		}

		read_bytes2 = read(fd2, buf2, CHUNK_SIZE);
		if(read_bytes2 < 0) {
			perror("read");
			close(fd1);
			close(fd2);
			return 1;
		}
		if(read_bytes1 == 0 && read_bytes2 == 0) {
			printf("Files are identical\n");
			break;
		}
		size_t common_bytes = (read_bytes1 < read_bytes2) ? read_bytes1 : read_bytes2;
		for(size_t i = 0; i < common_bytes; i++) {
			
			if(buf1[i] != buf2[i]) {
				printf("Files differ at byte %zu \n", tracker + i);
				close(fd1);
				close(fd2);
				return 1;
			}
		}

		tracker += (size_t)common_bytes;
		if(read_bytes1 != read_bytes2) {
				printf("Files differ at byte %zu \n", tracker);
				close(fd1);
				close(fd2);
				return 1;
		}

	}

	close(fd1);
	close(fd2);
	return 0;
}

