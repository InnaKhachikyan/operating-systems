#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {

	char src_file[50];
	char dst_file[50];

	printf("Enter source file name: ");
	if(scanf("%49s", src_file) != 1) {
		perror("scanf");
		return 1;
	}

	printf("Enter destination file name: ");
	if(scanf("%49s", dst_file) != 1) {
		perror("scanf");
		return 1;
	}

	int src_fd = open(src_file, O_RDONLY);
	if(src_fd == -1) {
		perror("open src");
		return 1;
	}

	int dst_fd = open(dst_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(dst_fd == -1) {
		perror("open dst");
		close(src_fd);
		return 1;
	}


	char buffer;
	ssize_t counter = 0;
	ssize_t num_read;
	while(1) {
		num_read = read(src_fd, &buffer, 1);
		if(num_read < 0) {
			perror("read");
			close(dst_fd);
			close(src_fd);
			return 1;
		}
		else if (num_read == 0) {
			break;
		}
		else {
			counter += num_read;
			if(write(dst_fd, &buffer, 1) < 0) {
				perror("write");
				close(dst_fd);
				close(src_fd);
				return 1;
			}
		}
	}

	printf("Number of bytes read/copied %zd\n", counter);

	close(src_fd);
	close(dst_fd);
	return 0;
}

