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


# reverse file reader

src_file will store the name of the filed scanned from the unser input.
Scan done with the corresponding check and error handling.

The file is opened with the corresponding check and error handling.

file_size is counted with lseek SEEK_END flag, done with corresponding check and error handling.

If any step is failed the file is closed before return.

A single char buffer declared, in a loop lseek is put -1 byte from the end, decrementing the cursor by one byte on each iteration; each byte is read, then written in the standard output one by one with the corresponding checks and error handling. If the file is empty, the loop will simply not execute and the code will jump to the line where \n is written to the standard output.


# append log.txt

We open log.txt (if there is no such a file, it is created) in write, append mode.
Get the pid of the process, write it in a string character by character.
As the 0 pid is always given to the systemd process, I didn't include that edge case to the pid writing.
taking the mod 10 of the number, we have the last digit of the pid number, write it in the next cell, dividing it by 10, we promote the next digit, to be taken as remainder on the next round.
In the string now we have the pid but in reversed order, in the for loop then I reverse the order of the digits to get the original pid.
I also append to the pid the space character.
pid_buf is written to the file (number of bytes is its length).
Then we take a single char as buffer, in a loop we read from the user byte by byte and write in the log.txt file while the user is typing, up to the new line character.
In the end when the user typed new line, the loop breaks, a single new line character is written to the file.
If the input is empty, the loop will just break and a new line character will be written after the pid.

All the open, write, read operations are done with corresponding checks and error handling.

lseek with SEEK_CUR
When we open a file, the cursor is typically at the beginning of the file (position 0), even if the file was opened in the append mode (to show that I added a small print in the beginning). However, the OS guarantees that the written bytes will be appended to the existing. Each time we call write (after opening with O_APPEND), the kernel under the hood does lseek with SEEK_END then write operation. So each time before writing anything to the file, OS (to ensure append and not allow overwriting), moves the cursor to the end, then writes to the file.
