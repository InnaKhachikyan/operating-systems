# Assignment 1

the var fork_pid stores the return value of the fork() function. If it is -1, then something went wrong, we handle that with perror, and the program returns immediately. If it is 0, then we are in the child process and print child process pid and exit with status 0. Else, we are in the parent process, we print its pid. Running the program multiple times, I noticed that first parent printing is done, then the child printing.



# Assignment 2

First we declare variables that we will need throughout the program for storing the return value of wait and waitpid, also for storing the exit status of the children.
In fork_pid we store the return value of the function fork(), if it is -1, means something went wrong, we throw a perror and return from main. If it is 0, we are in the child process, so we do printing with pid and exit with status 23. Else, if we are in the parent process, we do wait(&estatus_child1), which actually waits for ANY child, and stores its status in the pointer given as the argument.

Then we do another fork storing its return value. If it is -1, again handle with perror and return. If it is 0, we are in the child process, we do the printing with pid, and exit with status 42 (I gave these two numbers 23 and 42 just to differentiate the exit status of the children). Else, if we are in the parent process, we wait for the specific child, the second one. We specify the child by the first argument of waitpid, which is pid_t type, as fork() returns the pid of the child if we are in the parent process, I just passed the return value of the fork as the first argument to the waitpid. The second argument of the waitpid, is pointer to int, where the status of the child is stored. The last argument specifies whether to block the parent for the child to terminate or not. Which may sound contradictory, as it may seem that the main goal of waitpid should be synchronization, blocking parent until child is done, however the main goal of waitpid is to see the state change fo the child with blocking or non-blocking option, there are cases when we cannot block it until child is done, just want to reap it WHEN it is done. E.g. we have an http protocol, where parent process is polling listening to sockets, and whenever there is a request, forks, and the task of handling the http request is passed to the child. The child might take some time to finish, but the parent cannot wait for it to finish, it should continue polling. So in such cases we use waitpid with WNOHANG in a loop, just to acquire the exit status of the child if finished, not to leave zombie children, to reap them when they are done. However, if we pass 0 as the last argument, it will block the parent until the child with the given pid is done. So, I passed 0 here, to block the parent. In the parents printing I first tried to print the estatus_child directly, it turned out to be greater numbers than 23 and 42. So, it turns out that the integer filled into status by wait or waitpid packs multiple fields (signal that killed the child, core-dump flag, normal exit code etc.). When a child exits normally, the exit code is stored in the high byte of that integer. To obtain the actual status we may first check WIFEXITED(status) which returns true if child exited normally, and print the actual status with WEXITSTATUS(status). 

# Assignment 3

I declared 3 pointers for dynamically allocating arrays in separate processes. 
Then I declared three functions to register with atexit in each process. 
In the main I forked, handled failed fork with perror, in the child process registered the cleanup_for_child1 function with atexit, did malloc for the alloc_child1 array, if malloc failed, handle with perror and return, otherwise print "In child process 1 calling exit" and exited. After the exit the child 1 process calls the function that was registered with atexit, so goes to cleanup code in the function, frees dynamically allocated memory, and sets to NULL the dangling pointer.
In the parent process I forked again, in the child process registered the cleanup_for_child2 function with atexit, dynamically allocated memory with malloc, if malloc failed, throw perror and return, otherwise print "In child process 2 calling exit" and exit with status 0. After the second child exits, the cleanup_for_child2 function is called, and the memory that was dynamically allocated in child process 2 is freed, the dangling pointers is set to NULL.
Finally, in the parent process cleanup_for_parent function is registered with atexit. Memory is dynamically allocated, if it fails, perror is thrown and we return from main. Otherwise, printing "In parent process calling exit", exits the program, and the function cleanup_for_parent is called to free the dynamically allocated memory, and set to NULL the dangling pointer.

# Assignment 3 v2

I was not sure about the flow of the program required (whether different exits shoud be called in different processes or in one, so I created two versions of this assignment).

In this version there is only one process.
After each dynamic allocation one cleanup function is registered via atexit, so that if at any point something goes wrong and the program should exit, the corresponding cleanup functions of the dynamically allocated memories so far are called.
If everything goes successfully, we do fork.
If the fork failes, we exit with status 1 (so all the cleanup functions will be executed).
Otherwise in the child process we do printing and exit with _exit(0) so that the functions registered via atexit are not called in the child process.
In the parent process we do printing and exit(0), after which all the three cleanup functions will be called with the LIFO principle, like in stack, the last registered function will be executed the first, then the pre-last registered and so on.
So if everything goes successfully, we see printings:

a) "Child process exits without atexit"

b) "Parent process exits, expected output: functions registered with atexit"

Alloc 2 cleanup done

Alloc 1 cleanup done

Alloc 0 cleanup done

As there is no wait or waitpid, the processes may finish in any order so printings a) and b) may appear in different order depending from execution to execution.

Handlers would run in case of exiting from main with return 0, however, as we clal exit from both processes, return 0 is an unreachable statement.

How atexit can be useful in real-life applications?
Let's say we have a program which allocated dynamically memory, which has to be freed, dangling pointers handled, OR opens some file to read/write something, if something goes wrong during the execution and the program exits, the memory will not be freed OR file never closed. However, if we register some cleanup functions to do these after-exit necessary job, it will be executed even if the program execution went not as expected.
So, it can be useful for freeing memory, nullifyiing the pointers, closing files (flushing buffers), closing database connections, network sockets etc. both in case of successful and unexpected (something went wrong) termination of the program.


# Assignment 4

Fork is done, with error handling. The child process prints and exits with status0.
The parent process forks again with error handling. 
The second child tries to open non-existing file, so perror is thrown. 
I intentionally wrote opening of non-existent file. 
First, I used kill with self pid, to observe difference of the outputs in the main when checking the children's status (in that case exit(23) was not necessary) and the printing was "Something went wrong and the exit status 0). But then changed to simple exit(23).

Parent process waits for both children (again with error handling).
Afterwards, for each child it checks if WIFEXITED(status) is true, prints exited normally with status number. Else, it prints "Something went wrong" together with the exit status of the child.
So for the first child it should print, exited normally with exit status 42, and for the second child: exited normally with exit status 23, although perror with message intantional error is thrown first.


# Assignment 5

First I wrote a program where the child exited, while the parent was sleeping. So, the child remained in the zombie state: the parent is still alive, however the exit status is not read yet.
Doing htop and looking at the pid of the process (we may see it printing on the terminal and on htop list), we may see Z under the state column.
I commented this part, you may uncomment and check whether it works correctly.
Then I wrote with the second logic given: parent calls wait(&status), if the wait return value is -1, perror, else we try to get the exit status of the child if it exited normally.

wait()/waitpid() prevent zombies because they collect the child’s exit status and tell the kernel it can remove the child’s zombie entry from the process table. Without a wait, the child’s status stays there (state Z) until the parent reaps it or exits.
