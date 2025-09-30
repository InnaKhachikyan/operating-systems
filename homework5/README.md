Some tasks handle the user input in one way (like infinitely asking for a valid input), while the others in some other way: I just added some diversity in the solutions, as the problems were similar to each other.

# Task 1

If the user types not numbers, the program will terminate.
I read the input in an infinite loop so the program will not do its work and/or terminate until the user gives us a positive integer.
As my var to store the input is int, the user cannot also give something larger than 2^32-1, but that case is not handled here. 
If the user gives a valid input (>0) the loop breaks and we go on with the main logic, otherwise it says invalid input and prompt message comes again.


After reading the user's provided int, I allocate dynamically with malloc array of that size. Then check if malloc wasn't successful, perror and return 1. Otherwise prompt message again asking the user to input n integers (instead of n the integer they gave us earlier). Then in a loop I scan all the integers (if more integers are given, they are just discarded), and store them in the array. After, with a loop the sum is calculated and printed.
In the end we doo free() to free the dynamically allocated memory, and assign NULL to the dangling pointer.

Edited: I added a check for the maximum value acceptable, SIZE_MAX which belongs to the stdint.h and specifies the maximum size that malloc/calloc/realloc can accept (max value of the size_t). SIZE_MAX/sizeof(int) reassures that memory with the input given by the user can be allocated.


# Task 2

The initial logic is the same as in the task1: if not a number printed, the program terminates, if not a positive integer given, the user is notified and asked again to type a number. 
Dynamic memory allocation with calloc, then check if the memory was successfully allocated, if no - perror and return 1.
Printing the values of the array, all 0-s printed.
Then scanning the values given by the user into the array and calculating the average.
Printing the average with high precision.
And in the end I free() the memory and nullify the dangling pointer.


# Task 3

Dynamic allocation with the corresponding check. 10 values scaned, values written in the array.
arr resized with the help of realloc(). 
The array values printed after realloc.


# Task 4

In task 4 I defined the sizes with macros, just to make it easily changable if necessary.
I declared the double pointer to char as global, in order to use it in the free_mem function later. Also I stored str_allocated to trace how many strings have been allocated to be able to free them at any point, the free_mem function is registered via atexit. In order to be able to use the free_mem at any point, I first assign to null all the strings, so that if at any point of allocation any string malloc fails, I return 1 from main knowing that whatever was already allocated will be freed in free_mem (freeing nullified memory is fine).
I prompt a message and scan 3 strings, limiting the input to 49 chars (as the 50-th one should be \0).
Scan the messages provided by the user in the array, then print them, then realloc the array with the new size.
Again nullify the new cells, so that free_mem can free those at any point when anything goes wrong. 
Then allocate dynamically memory.
Prompt message again asking from the user NEW_SIZE-SIZE messages, scanning them, storing in the array, and printing.
In the end there is no need to free anything manually as after return 0 the registered free_mem function will free all the allocated memory and nullify the dangling pointers.

Edited: Initially I did ptr_str = realloc... That would work but maybe not correct, because if the realloc failed, it would return NULL and the ptr_str would be lost, while my program registered free_mem with atexit. So I changed and assigned the return of the realloc to a new double char pointer, so that if something goes wrong, free_mem is called and frees all the necessary memory.


# Task 5

Prompting message, reading input number from the user. 
Dynamic allocation with check whether it was successful.
Prompting message again, reading inputs and storing in the array of doubles.
With a single loop calculating the highest and the lowest grades, printing out.
We assume that the grades range is [0,100].
In the end freeing the memory and nullifying the pointer.



