#include <stdio.h>
#include <fcntl.h>
#include <inttypes.h>
#include <unistd.h>

int main(void) {

	int fd = open("sparse.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1) {
		perror("open");
		return 1;
	}

	if(write(fd, "START", 5) < 0) {
		perror("write");
		close(fd);
		return 1;
	}

	off_t cursor = lseek(fd, 1024*1024, SEEK_CUR);
	if(cursor < 0) {
		perror("lseek");
		close(fd);
		return 1;
	}

	if(write(fd, "END", 3) < 0) {
		perror("write");
		close(fd);
		return 1;
	}

	close(fd);

	fd = open("sparse.bin", O_RDONLY);
	if(fd == -1) {
		perror("open");
		return 1;
	}

	cursor = lseek(fd, 0, SEEK_END);
	if(cursor < 0) {
		perror("lseek");
		close(fd);
		return 1;
	}

/* 
Sparse files have holes in them. They logically contain zeros, but phisically don't occupy memory. The f
ile system records some big jump in the file offset, but does not store zero bytes. When we later try to read these bytes the kernel returns 0-s on the run. So we make a 1 MiB file by storing only a few bytesthe rest is some kind of virtual space.
When we do lseek with 1 MiB the file system records a hole between the write operations. Reading the "ho
les" returns 0. Only when we write actual data in these wholes memory on disc is allocated.
Although we have moved the cursor 1MiB further, the du sparse.bin returns 8 Kb only.
*/
	printf("Size is %jd bytes\n", (intmax_t)cursor);

	close(fd);
	return 0;
}

