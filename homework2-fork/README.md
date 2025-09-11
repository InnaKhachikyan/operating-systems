I added printing before the start of each program to differentiate them. If you type make and then make test, all the programs will compile and run.

# Assignment0

I initialize a fork pid to save the returned value of the fork(). If it is -1, then fork failed so I send perror. This is repeated 2 more times. As a result we have 2^3 processes

		         P
		         |
	       /           \
	      P             C1
	      |             |
	   /     \       /     \
	  P      C2     C1      C3
	  |       |      |       |
	 / \     / \    / \     / \
	P  C4   C2 C5  C1  C6  C3  C7


# Assignment1

First I fork the process and store the return value. If the return value is 0 (i.e. we are in the child process), we call execl to execute ls command. Else (if we are in the parent process), we call wait(NULL), which waits for the child process to finish its job, then print "Parent process done".
In case fork or exec return values are -1, means the call failed, something went wrong, perror is sent and main is returned with -1.


# Assignment2

First fork is done with storage of the return value. If it is -1, then perror is sent and main returned with -1 value.
If the return value is 0, we are in the child process and call exec to execute the ls program. Else if we are in the parent process, we do fork again and store the return value. 
If it is -1, perror sent.
Else if it is 0, we call exec so that the child executes date binary.
Else (if we are in the parent process), we just wait for the children to finish their job in a loop while(wait(NULL) >-1), we call in a loop wait(NULL), which returns -1 when there are no more children to wait for. So the loop is exited when the children already finished their job, then parent prints "Parent process done".
As a result we see in the terminal the ls command result, date command result and in the end "Parent process done". It can also be vice-versa: date command result, ls command result, then "Parent process done". So, date and ls may be mixed in order, but the "Parent process done" print always comes last.


# Assignment3

Fork is done and return value stored.
If -1, perror sent.
Else if 0 (in child process) we call execl to exexcute echo, here we give one more argument which is the text to echo "Hello from the child process". execl has variable arguments, which have to be NULL terminated, so when we are done passing arguments, in the end we give NULL. In this case we have one more argument (the string to be echoed), but the arguments again are NULL terminated in the end.
Else if we are in the parent process, we just wait for the single child, then print "Parent process done".
As a result we see execution of echo with the string then the print by the parent.


# Assignment4

This is very similar to assignment 3, with one change: one more argument is added for the exec. As arguments we give the path of the binary grep, the name of the binary to be executed, the word to search (in our case "Diffie"), and the last argument is the file in which we have to search for the word. The arguments are again terminated with NULL.
The parent waits for the only child and does the print.
As a result we see the line from the text which contains the word we were searching for, and then the print done by the parent.
