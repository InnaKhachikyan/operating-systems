# copy file contents

I declare 2 buffers to scan the name of the src and destination files from the user.
Print the prompt message, scan the input of user (max 49 chars), check if not scanned successfully, handle with perror and return 1. Similarly, do for the destination file name.

src_fd is the file descriptor for the open of source file in read only mode. If it is -1, handle with perror.

dst_fd is the file descriptor for the open of destination file in write mode (with CREAT and TRUNC flags0644 is for the permission access: user: 6 (read and write), group: 4 (read only), others: 4 (read only).
If open fails, handle with perror, close the already open file (src), return 1.

The src file is read byte by byte (as the task says to read repeatedly, I didn't find out the size and read in one chunk with a large buffer) in the buffer, the loop continues while number of bytes read is greater than 0. If number of bytes read is greater than 0, the byte is written to the destination file, if writing fails, both files are closed, perror, and return 1.
In the loop the counter keeps the track of the number of total bytes read/copied.


# file truncation

File opening in write mode, with CREAT and TRNC flags, with the same access permissions as above.
If file descriptor is -1, opening failed, handling with perror.

array of chars buffer is initialized, it is written in the file with the sizeof(buffer). This way it writes 27 bytes ('\0' in the end as the 27-th byte), otherwise we could write exactly 26 bytes, but I think including EOF is better.
On each step, if anything fails, the opened file is closed before returning.
The file is closed and reopened again in read and write mode, again with error handling.

with lseek we search for the end of the file, lseek returns the number of bytes the cursor moved until reaching the end. If it is less than 0, then it failed, corresponding steps taken. We print the number of bytes lseek returned (file size).

calling ftruncate with 10 bytes parameter. If the return value is less than 0, it failed, handling with perror and closing the file.
Otherwise (if succeeded) we set the cursor to the start of the file (again with check and error handling) and count the file size with another lssek call with the SEEK_END flag. The return value is stored in the new_size var, if less than 0, handle with perror, close the file, otherwise print the new size.

We set the cursor to the start of the file again with lseek with SEEK_SET flag to be able to print.
A buffer is allocated with the new size, to store the read bytes from the file (corresponding malloc check, error handling, free, dangling pointer nullifying in necessary places).

We read the file contents in the buffer with the new_size of the file, and print the contents of the buffer.

In the end the file is closed, allocted memory freed, dangling pointer nullified.

