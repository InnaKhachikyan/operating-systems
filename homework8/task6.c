#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int cleanup(char *err, int fd) {
	if(err != NULL) {
		perror(err);
	}
	if(fd >= 0) {
		close(fd);
	}
	return 1;
}

int main(void) {

	int fd = open("numbers.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1) {
		perror("open");
		return 1;
	}


	char *str = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n";
	ssize_t written_bytes = write(fd, str, strlen(str));

	if(written_bytes < 0) {
		return cleanup("write", fd);
	}
	if(written_bytes != strlen(str)) {
		printf("Not enough bytes written");
		return cleanup(NULL, fd);
	}
	
	close(fd);

	fd = open("numbers.txt", O_RDWR);
	if(fd == -1) {
		return cleanup("open", -1);
	}

	ssize_t read_bytes;
	int newl = 0; 
	off_t line_offset = 0; 
	off_t buf_offset = 0;  

	char buffer;
	while(1) {
		read_bytes = read(fd, &buffer, 1);
		if(read_bytes < 0) {
			return cleanup("read", fd);
		}
		
		if(read_bytes == 0) {
			break;
		}

		buf_offset++;
		if(buffer == '\n') {
			newl++;
		
			if(newl == 3) {
				line_offset = buf_offset;
			}
			else if(newl == 4 || read_bytes == 0) {
				break;
			}
		}
	}

	off_t cursor = lseek(fd, buf_offset, SEEK_SET);
	if(cursor == -1) {
		return cleanup("lseek", fd);
	}

	off_t size = lseek(fd, 0, SEEK_END);
	if(size == -1) {
		return cleanup("lseek", fd);
	}
	int buf_size = size - buf_offset;
	char *temp = (char*)malloc(sizeof(char)*buf_size);
	if(!temp) {
		return cleanup("malloc", fd);
	}
	cursor = lseek(fd, buf_offset, SEEK_SET);
	if(cursor == -1) {
		return cleanup("lseek", fd);
	}

	read_bytes = read(fd, temp, buf_size);
	if(read_bytes < 0) {
		return cleanup("read", fd);
	}
	else if(read_bytes != buf_size) {
		printf("Not enough bytes read\n");
		return cleanup(NULL, fd);
	}
	cursor = lseek(fd, line_offset, SEEK_SET);
	if(cursor == -1) {
		return cleanup("lseek", fd);
	}

	char *new_str = "100\n";
	written_bytes = write(fd, new_str, strlen(new_str));
	if(written_bytes < 0 ) {
		return cleanup("write", fd);
	}
	if(written_bytes != strlen(new_str)) {
		printf("Not enough bytes written\n");
		return cleanup(NULL, fd);
	}

	written_bytes = write(fd, temp, buf_size);
	if(written_bytes < 0) {
		return cleanup("write", fd);
	}
	else if(written_bytes != buf_size) {
		printf("Not enough bytes written\n");
		return cleanup(NULL, fd);
	}

	close(fd);
	free(temp);
	temp = NULL;

	fd = open("numbers.txt", O_RDONLY);
	if(fd == -1) {
		return cleanup("open", -1);
	}

	while ((read_bytes = read(fd, &buffer, 1)) > 0) {
    		if (write(1, &buffer, 1) < 0) return cleanup("write", fd);
	}
	if (read_bytes < 0) return cleanup("read", fd);

	close(fd);
	return 0;
}

